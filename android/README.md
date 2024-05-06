# Building and running tests with Android


The easiest way to build libaddressinput for Android and run all the tests is
to use Gradle:

https://developer.android.com/build
http://www.gradle.org/


## Prerequisite dependencies for using Gradle with Android

Android Studio: https://developer.android.com/sdk/index.html (recommended)
 - Check Tools > SDK Manager.

Android SDK Tools: https://developer.android.com/sdk/index.html#Other
- Set the ANDROID_HOME environment variable to the root of the SDK.

Ensure the following packages are installed:
 - Tools/Android SDK Platform-tools (Rev. 35.0.1)
 - Android 14 (API 34)
 - Extras/Android Support Library


## Building and Running

After installing all the prerequisites, check that everything is working by
building the package and running the tests in Android Studio. Alternatively, the
following can be run by command line:

`gradlew build`

With an Android emulator running or an Android device connected, the following
command line then builds the library and runs the tests:

`gradlew connectedAndroidTest`

The test runner logs to the system log, which can be viewed using logcat:

`adb logcat`

# Integrating with Android Apps


1. Clone libaddressinput from Github or download and unzip to a folder called 'libaddressinput'.


2. From a terminal window, change into the folder: `cd libaddressinput/`

3. Build the widget and library via gradle:

    `gradlew build`

4. Copy the widget and the common libraries:

    `cp android/build/outputs/aar/android-release.aar path/to/project/app/libs/`

    `cp common/build/libs/common.jar path/to/project/app/libs/`

    Note: Be sure top replace 'path/to/project' with the name of your project.

5. Import both modules into your app.

    Note: If you use Android Studio, check out the [user guide](https://developer.android.com/studio/projects/android-library.html#AddDependency) and follow the instructions under 'Add your library as a dependency'. Be sure to add *both* modules as dependencies of the app.

6. Add the widget to your app. Note: This Assumes a default empty project configuration:

    i. In activity_main.xml add:

    ```xml
    <LinearLayout
        android:id="@+id/addresswidget"
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:orientation="vertical"/>
     ```

    ii. In MainActivity.java add the following import statements:

    ```java
    import android.view.ViewGroup;

    import com.android.i18n.addressinput.AddressWidget;
    import com.google.i18n.addressinput.common.FormOptions;
    import com.google.i18n.addressinput.common.ClientCacheManager;
    import com.google.i18n.addressinput.common.SimpleClientCacheManager;
    ```

    iii. Define the widget on the object scope

    ```java
    private AddressWidget addressWidget;
    ```

    iv. Add the widget to the ViewGroup
    ```java
    ViewGroup viewGroup = (ViewGroup) findViewById(R.id.addresswidget);
    FormOptions defaultFormOptions = new FormOptions();
    ClientCacheManager cacheManager = new SimpleClientCacheManager();
    this.addressWidget = new AddressWidget(this, viewGroup, defaultFormOptions, cacheManager);
    ```

Example:

```java
package com.example.google.widgetdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ViewGroup;

import com.android.i18n.addressinput.AddressWidget;
import com.google.i18n.addressinput.common.FormOptions;
import com.google.i18n.addressinput.common.ClientCacheManager;
import com.google.i18n.addressinput.common.SimpleClientCacheManager;

public class MainActivity extends AppCompatActivity {
    private AddressWidget addressWidget;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ViewGroup viewGroup = (ViewGroup) findViewById(R.id.addresswidget);
        FormOptions defaultFormOptions = new FormOptions();
        ClientCacheManager cacheManager = new SimpleClientCacheManager();
        this.addressWidget = new AddressWidget(this, viewGroup, defaultFormOptions, cacheManager);
    }
}
```
