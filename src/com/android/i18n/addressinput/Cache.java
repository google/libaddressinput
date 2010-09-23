/*
 * Copyright (C) 2010 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.i18n.addressinput;

// TODO(AAW): Figure out if we want to log, and how if the answer is yes.
// import com.android.vending.util.Log;

import android.content.Context;
import android.os.Looper;

// TODO(AAW): If this is to run on Android 2.1, we can use Base64. This is used to sanitize the
// filename if necessary. If we have to make this run on 1.6, we have to change this to use a
// different method.
// import android.util.Base64;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FilenameFilter;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedHashMap;

/**
 * An implementation of {@link com.android.vending.cache.CacheManager} that caches entities in
 * memory and uses the filesystem as a backing store (the implementation uses a simple write-through
 * mechanism).
 */
public class Cache {

    /** Prefix string for all cache files created in the filesystem. */
    static final String DISK_CACHE_FILENAME_PREFIX = "AVMC_";

    /** Prefix string for sanitized filenames in disk cache. */
    private static final String SANITIZED_PREFIX = "S";

    /** Prefix string for unsanitized filenames in disk cache. */
    private static final String UNSANITIZED_PREFIX = "U";

    /** Current version of the on-disk cache. Written as the first four bytes of every cache
     * file. */
    static final int DISK_CACHE_VERSION = 7;

    /** Debug flag to turn off cache logging. */
    private static final boolean LOG_CACHE = false;

    /** Debug flag to turn off caching completely. */
    private static final boolean CACHE_ENABLED = true;

    /** Number of cached results allowed on-disk before enabling garbage collection. */
    private static final int DISK_CACHE_CAPACITY = 400;

    /** Number of on-disk results garbage collection will leave behind. */
    private static final int DISK_CACHE_TARGET_SIZE = 300;

    /** Maximum number of entries in in-memory cache. */
    private static final int MAIN_CACHE_SIZE = 50;

    /** Maximum number of entries in the high-priority cache. */
    private static final int PRIORITY_CACHE_SIZE = 30;

    /** Size of buffer, in bytes, for reading or writing cache files from disk. */
    private static final int DISK_IO_BUFFER_SIZE = 1024;

    private static final int MAX_AGE = Integer.MAX_VALUE;
    private static final int MAX_AGE_CONSUMABLE = Integer.MAX_VALUE;

    /** Filter used to return disk cache files. */
    private static final FilenameFilter sCacheFilenameFilter = new CacheFilenameFilter();

    /** Comparator used to sort files from most eligible to least eligible for disk cache GC. */
    private static final Comparator<File> sCacheCleanComparator = new CacheCleanComparator();

    /**
     * A String -> CacheEntry Map that will not grow beyond a specified size
     * and evicts entries based on least recent access.
     */
    private class BoundedCache extends LinkedHashMap<String, CacheEntry> {
        private int mMaxSize;
        public BoundedCache(int maxSize) {
            super(maxSize, 1.0f, true);
            mMaxSize = maxSize;
        }
        // Override
        protected boolean removeEldestEntry(Entry<String, CacheEntry> eldest) {
            return size() > mMaxSize;
        }
    }

    /** In-memory LRU cache, holding at maximum MEM_CACHE_SIZE items. */
    private final BoundedCache mCache = new BoundedCache(MAIN_CACHE_SIZE);

    /** Special in-memory cache for items marked high priority. */
    // private final BoundedCache mPriorityCache = new BoundedCache(PRIORITY_CACHE_SIZE);

    private final Context mContext;

    private int mApproximateDiskCacheSize;

    /**
     * Define a lock for reading and writing the disk file cache.
     * If both the disk and memory locks are needed, take the disk lock first
     * to avoid deadlock and to minimize the lock contention for the UI thread.
     */
    private Object mDiskLock = new Object();

    /**
     * Define a lock for reading and writing the memory cache.
     * If both the disk and memory locks are needed, take the disk lock first
     * to avoid deadlock and to minimize the lock contention for the UI thread.
     */
    private Object mMemoryLock = new Object();

    private long mMemoryCacheReads;
    private long mDiskCacheReads;
    private long mCacheWrites;
    private long mCacheDeletes;
    private long mCacheInvalidates;
    private long mMemoryCacheMisses;
    private long mDiskCacheMisses;

    public Cache(Context context) {
        this.mContext = context;
        mApproximateDiskCacheSize = -1;  // Uninitialized
    }

    /**
     * Returns an object that encapsulates the result of the cache lookup.
     *
     * @param id the lookup key on the form "data/country/.." ie. "data/US/CA"
     * @return an object that encapsulates the result of the cache lookup.
     *         <code>null</code> will be returned if the entity is not cached.
     */
    public String get(String id) {
        CacheResult result = get(id, true);
        if (result == null) {
            return null;
        }
        return result.jsonString;                   
    }

    /**
     * Returns an object that encapsulates the result of the cache lookup.
     *
     * @param id the lookup key on the form "data/country/.."
     *        ie. "data/US/CA"
     * @param checkDiskToo if false, then only the memory cache is checked;
     *        if true, then both the memory and disk cache are checked. UI
     *        threads should always set this to false to avoid ANRs.
     * @return an object that encapsulates the result of the cache lookup.
     *         <code>null</code> will be returned if the entity is not cached.
     */
    private CacheResult get(String id, boolean checkDiskToo) {
        if (!CACHE_ENABLED) {
            return null;
        }

        CacheEntry entry = null;
        boolean triedDisk = false;
        entry = readFromMemory(id);
        //TODO(AAW): Need to investigate how this works in our code. See TODO in original text.
        if (entry == null) {
            if (checkDiskToo) {
                entry = readFromDisk(id);
                triedDisk = true;
            }
        }

        CacheResult result = null;
        if (entry != null) {
            result = new CacheResult();
            long now = System.currentTimeMillis();
            result.jsonString = entry.jsonString;
            //TODO(AAW): Look at how to set expiry time
            result.isExpired = (entry.expiryTime < now);
            result.id = entry.id;
            result.canPostponeRefresh = ((entry.postponeRefreshExpiryTime >= now) &&
                    (entry.postponeRefreshExpiryTime > entry.expiryTime));
        }

        if (LOG_CACHE) {
            boolean isUI = (Looper.getMainLooper() == Looper.myLooper());
            double memoryMissRate = 100.0f * mMemoryCacheMisses / mMemoryCacheReads;
            double diskMissRate = 100.0f * mDiskCacheMisses / mDiskCacheReads;
            String resultStr = "MISS";
            if (result != null) {
                resultStr = result.isExpired ? "EXP" : "HIT";
                resultStr += (triedDisk ? "d" : "m");
            }
            /*Log.d("%s[%s] %s | mem miss: %d/%d %.2f disk miss: %d/%d %.2f puts: %d size: %d",
                    isUI ? "*" : " ", resultStr, id,
                    mMemoryCacheMisses, mMemoryCacheReads, memoryMissRate, mDiskCacheMisses,
                    mDiskCacheReads, diskMissRate, mCacheWrites, mCache.size());    */
        }

        return result;
    }

     /**
     * Adds the provided object(s) into the cache with the provided parameters. Currently very long
     * life.
     *
     * NOTE: Though either <code>protoBuf</code> or <code>serializable</code> can be null, both
     * objects cannot be null.
     *
     * @param id the lookup key on the form "data/country/.." ie. "data/US/CA"
     * @param jsonString to be cached
     * // TODO(AAW): Need to implement a much longer life
     */
    public void put(String id, String jsonString) {
        put(id, jsonString, MAX_AGE, MAX_AGE_CONSUMABLE);
     }


    /**
     * Adds the provided object(s) into the cache with the provided parameters.
     *
     * NOTE: Though either <code>protoBuf</code> or <code>serializable</code> can be null, both
     * objects cannot be null.
     *
     * @param id the lookup key on the form "data/country/.." ie. "data/US/CA"
     * @param jsonString to be cached
     * @param maxAge the maximum age in seconds for which this object should be cached
     * @param maxAgeConsumable the maximum age in seconds for which the data can be cached and used
     */
    private void put(String id, String jsonString, int maxAge, int maxAgeConsumable) {
        if (LOG_CACHE) {
            boolean isUI = (Looper.getMainLooper() == Looper.myLooper());
            String name = id;
            /*if (cacheable instanceof AssetService.SingleAssetKey) {
                Asset asset = new Asset(protoBuf);
                name += " " + asset.getTitle();
            } */
            // TODO(AAW): Fix this comment and re-enable
            /*Log.d("%s[PUT] %s%s %s %s/%s | puts: %d mCache size: %d (+%d)",
                    isUI ? "*" : " ",
                    cacheable.isHighPriority() ? "<PRIORITY> " : "",
                    name, etag, maxAge, maxAgeConsumable, mCacheWrites, mCache.size(),
                    mPriorityCache.size()); */
        }

        if (!CACHE_ENABLED) {
            return;
        }

        // Do not cache if invalid maxAge.
        if (maxAge <= 0) {
            return;
        }

        CacheEntry entry = new CacheEntry();
        entry.jsonString = jsonString;
        entry.id = id;
        // TODO(AAW): Fix expiry time
        long now = System.currentTimeMillis();
        entry.expiryTime = now + (maxAge * 1000L);
        entry.postponeRefreshExpiryTime = now + (maxAgeConsumable * 1000L);

        writeToDisk(id, entry);
    }

    /**
     * Invalidate the data stored under the given key so that subsequent requests to
     * {@link #get(String, boolean)} will return expired values.
     * @param id the lookup key on the form "data/country/.." ie. "data/US/CA"
     * @return true if an entry was invalidated, false if no entry was found
     */
    public boolean invalidate(String id) {
        if (LOG_CACHE) {
            boolean isUI = (Looper.getMainLooper() == Looper.myLooper());
            /*Log.d("%s%s invalidates: %d mCache size: %d",
                    isUI ? "UI " : "   ",
                    id, mCacheInvalidates, mCache.size()); */
        }

        return invalidateFromDisk(id);
    }

    /**
     * If the entity represented by the provided <code>cacheable</code> exists,
     * it will be deleted from the cache.
     * @param id the lookup key on the form "data/country/.." ie. "data/US/CA"
     */
    public void delete(String id) {
        if (LOG_CACHE) {
            boolean isUI = (Looper.getMainLooper() == Looper.myLooper());
            /*Log.d("%s%s deletes: %d mCache size: %d",
                    isUI ? "UI " : "   ",
                    id, mCacheDeletes, mCache.size());*/
        }

        deleteFromDisk(id);
    }

    /**
     * Clears the entire cache.  Potentially a blocking call.
     */
    public void clear() {
        synchronized (mDiskLock) {
            synchronized (mMemoryLock) {
                File[] cacheFiles = mContext.getCacheDir().listFiles(sCacheFilenameFilter);
                for (File file : cacheFiles) {
                    file.delete();
                }
                mCache.clear();
            }
        }
    }

    /**
     * Checks the in-memory cache for the given cacheable.
     * @param id the lookup key on the form "data/country/.."
     *        ie. "data/US/CA"
     * @return the cached object or null if not found.
     */
    CacheEntry readFromMemory(String id) {
        synchronized (mMemoryLock) {
            mMemoryCacheReads += 1;

            CacheEntry entry;
            // Try the priority cache first, falling back to the normal churning one.
            entry = mCache.get(id);
            if (entry == null) {
                mMemoryCacheMisses += 1;
                deleteFromMemory(id);
                return null;
            }
            return entry;
        }
    }

    /**
     * @param id the lookup key on the form "data/country/.."
     *        ie. "data/US/CA"
     * @return the respective on-disk file for the entity represented by <code>cacheable</code>.
     */
    File getDiskCacheFile(String id) {
        String sanitizedFilename =
            DISK_CACHE_FILENAME_PREFIX +
            sanitizeFilename(id);
        return new File(mContext.getCacheDir(), sanitizedFilename);
    }

    /**
     * Returns true if the provided character is a valid filename character. This check
     * white-lists filename characters and errs on the side of safety (i.e. there are some filename
     * characters that may actually be a valid character on this OS that will be reported as
     * invalid).
     */
    private static boolean isValidFilenameChar(char c) {
        if (!Character.isLetterOrDigit(c)) {
            switch (c) {
            case '.':
            case ',':
            case '@':
            case '#':
            case '%':
            case '(':
            case ')':
            case '=':
            case '_':
            case '-':
            case '+':
            case '{':
            case '}':
            case '[':
            case ']':
                break;
            default:
                return false;
          }
        }
        return true;
    }

    /**
     * Returns a sanitized version of the given filename. The "/" are subsituted with "-" (to keep
     * the filename readable). If there are any characters that aren't valid as determined by the
     * {@link #isValidFilenameChar(char)} function, the entire filename will be Base64 encoded.
     */
    static String sanitizeFilename(String filename) {
         char [] charName = new char[filename.length()];
        // File names are prefixed to ensure that there aren't any collisions for the different
        // encoding schemes.
        for (int i = 0; i < filename.length(); i++) {
            charName[i] = filename.charAt(i);
            if (!isValidFilenameChar(charName[i])) {
                charName[i] = "-".charAt(0);
            }

            /*if (!isValidFilenameChar(charName[i])) {
                return SANITIZED_PREFIX + Base64.encodeToString(filename.getBytes(),
                    Base64.URL_SAFE | Base64.NO_PADDING | Base64.NO_WRAP);
            } */
        }
        return UNSANITIZED_PREFIX + new String(charName);
    }

    /**
     * @param id the lookup key on the form "data/country/.." ie. "data/US/CA"
     * Check the filesystem for the cached item.
     */
    CacheEntry readFromDisk(String id) {
        synchronized (mDiskLock) {
            mDiskCacheReads += 1;
            File cacheFile = getDiskCacheFile(id);
            if (!cacheFile.exists()) {
                mDiskCacheMisses += 1;
                return null;
            }

            try {
                InputStream in = new BufferedInputStream(
                        new FileInputStream(cacheFile), DISK_IO_BUFFER_SIZE);
                ObjectInputStream ois = new ObjectInputStream(in);
                int version = ois.readInt();
                if (version != DISK_CACHE_VERSION) {
                    /*Log.i("Invalid cache version: " + version);*/
                    ois.close();
                    cacheFile.delete();
                    mDiskCacheMisses += 1;
                    return null;
                }

                CacheEntry entry = new CacheEntry();
                entry.expiryTime = ois.readLong();
                entry.id = ois.readUTF();
                entry.postponeRefreshExpiryTime = ois.readLong();
                entry.jsonString = ois.readUTF();
                ois.close();

                // Touch the file on each read to simulate LRU.
                cacheFile.setLastModified(System.currentTimeMillis());
                writeToMemory(id, entry);
                return entry;

            } catch (FileNotFoundException e) {
                /*Log.e("Couldn't open cache file for read: " + id, e);*/

            } catch (IOException e) {
                /*Log.e("Reading cache file: " + id, e);*/
                cacheFile.delete();
            }

            mDiskCacheMisses += 1;
            return null;
        }
    }

    /**
     * Writes the given cache entry to disk for the given cacheable entity.
     * @param id the lookup key on the form "data/country/.."  ie. "data/US/CA"
     * @param entry
     */
    void writeToDisk(String id, CacheEntry entry) {
        synchronized (mDiskLock) {
            mCacheWrites += 1;
            ensureDiskCapacity();

            File cacheFile = getDiskCacheFile(id);
            try {
                OutputStream out = new BufferedOutputStream(
                        new FileOutputStream(cacheFile), DISK_IO_BUFFER_SIZE);
                ObjectOutputStream oos = new ObjectOutputStream(out);
                oos.writeInt(DISK_CACHE_VERSION);
                oos.writeLong(entry.expiryTime);
                oos.writeUTF(entry.id);
                oos.writeLong(entry.postponeRefreshExpiryTime);
                oos.writeUTF(entry.jsonString);
                oos.close();
                mApproximateDiskCacheSize++;
                writeToMemory(id, entry);

            } catch (FileNotFoundException e) {
                /*Log.e("Couldn't open cache file to write: " + id, e);*/

            } catch (IOException e) {
                /*Log.e("Writing cache file: " + id, e);*/
                cacheFile.delete();
            }
        }
    }

    /**
     * Writes the given cache entry to the in-memory cache for the given cacheable entity.
     *
     * @param id the lookup key on the form "data/country/.."  ie. "data/US/CA"
     * @param entry
     */
    void writeToMemory(String id, CacheEntry entry) {
        synchronized (mMemoryLock) {
            mCache.put(id, entry);
        }
    }

    /**
     * Expires the provided entry if present in the in-memory cache.
     *
     * @param id the lookup key on the form "data/country/.." ie. "data/US/CA"
     * @returns true if an entry was invalidated, false if no entry was found
     */
    boolean invalidateFromMemory(String id) {
        synchronized (mMemoryLock) {
            CacheEntry entry = readFromMemory(id);

            if (entry != null) {
                entry.expiryTime = 0;
                writeToMemory(id, entry);
                return true;
            }

            return false;
        }
    }

    /**
     * Expires the provided entry if present in the on-disk cache.
     *
     * @param id the lookup key on the form "data/country/.." ie. "data/US/CA"
     * @returns true if an entry was invalidated, false if no entry was found
     */
    boolean invalidateFromDisk(String id) {
        synchronized (mDiskLock) {
            mCacheInvalidates += 1;
            // Ensure memory is consistent.
            boolean invalidated = invalidateFromMemory(id);
            CacheEntry entry = readFromDisk(id);

            if (entry != null) {
                entry.expiryTime = 0;
                writeToDisk(id, entry);
                return true;
            }

            return invalidated;
        }
    }

    /**
     * Deletes the given cacheable entity from disk.
     * @param id the lookup key on the form "data/country/.."
     *        ie. "data/US/CA"
     */
    void deleteFromDisk(String id) {
        synchronized (mDiskLock) {
            mCacheDeletes += 1;
            File cacheFile = getDiskCacheFile(id);
            cacheFile.delete();
            mApproximateDiskCacheSize--;
            deleteFromMemory(id);
        }
    }

    /**
     * Deletes the given cacheable entity from the in-memory cache.
     *
     * @param id the lookup key on the form "data/country/.."
     *        ie. "data/US/CA"
     */
    void deleteFromMemory(String id) {
        synchronized (mMemoryLock) {
            mCache.remove(id);
        }
    }

    void ensureDiskCapacity() {
        if (mApproximateDiskCacheSize < 0 ||  // Still uninitialized
            mApproximateDiskCacheSize > DISK_CACHE_CAPACITY) {
            File[] cacheFiles = mContext.getCacheDir().listFiles(sCacheFilenameFilter);
            int cacheSize = cacheFiles.length;
            mApproximateDiskCacheSize = cacheSize;  // Update cache size
            if (cacheSize < DISK_CACHE_CAPACITY) {
                // Cache size within capacity
                return;
            }
            Arrays.sort(cacheFiles, sCacheCleanComparator);
            for (int i = 0;
                 i < cacheSize && mApproximateDiskCacheSize > DISK_CACHE_TARGET_SIZE;
                 i++) {
                if (cacheFiles[i].delete()) {
                    mApproximateDiskCacheSize--;
                }
            }
        }
    }

    /**
     * General representation of entry stored in in-memory or on-disk cache.
     */
    static class CacheEntry {

        /** The cached json string */
        public String jsonString;

        /** Time when this entry expires. */
        public long expiryTime;

        /**The lookup key on the form "data/country/.." ie. "data/US/CA" */
        public String id;

        /** Time when the possibility to postpone the refresh expires. */
        public long postponeRefreshExpiryTime;
    }

    public class CacheResult {
        /** The cached json string */
        public String jsonString;

        /** True if the returned object has expired. */
        public boolean isExpired;

        /**The lookup key on the form "data/country/.." ie. "data/US/CA" */
        public String id;

        /** If true, the result can be refreshed at convenience. */
        public boolean canPostponeRefresh;
    }

    /**
     * FilenameFilter that filters for disk cache files.
     */
    private static class CacheFilenameFilter implements FilenameFilter {
        public boolean accept(File dir, String name) {
            return name.startsWith(DISK_CACHE_FILENAME_PREFIX);
        }
    }

    /**
     * Comparator used to sort files from most eligible to least eligible for disk cache GC.
     * Primary sort is from normal to high priority; secondary sort is from least recently
     * modified to most recently modified.
     */
    private static class CacheCleanComparator implements Comparator<File> {
        private int comparePriority(File file1, File file2) {
            return 0;
        }

        private int compareLastMod(File file1, File file2) {
            long lastMod1 = file1.lastModified();
            long lastMod2 = file2.lastModified();
            return lastMod1 < lastMod2 ? -1 : lastMod1 == lastMod2 ? 0 : 1;
        }

        public int compare(File file1, File file2) {
            int result = comparePriority(file1, file2);
            if (result == 0) {
                result = compareLastMod(file1, file2);
            }
            return result;
        }
    }
}
