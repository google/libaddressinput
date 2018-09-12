# ![](https://github.com/googlei18n/libaddressinput/wiki/libaddressinput-icon-70x55.png) libaddressinput

[![Build Status](https://travis-ci.org/googlei18n/libaddressinput.svg?branch=master)](https://travis-ci.org/googlei18n/libaddressinput)

The _libaddressinput_ project consists of two different libraries (one
implemented in C++, one implemented in Java for Android) that use
[address metadata](https://github.com/googlei18n/libaddressinput/wiki/AddressValidationMetadata)
from
[Google](https://developers.google.com/)'s
[Address Data Service](https://chromium-i18n.appspot.com/ssl-address/data)
to assist application developers in collecting and handling _postal addresses_
from all over the world.

These libraries can provide information about what input fields are required for
a correct address input form for any country in the world and can validate an
address to highlight input errors like missing required fields or invalid
values.

## C++

The C++ library (in very portable C++11) of _libaddressinput_ is used in address-related
projects in [Chromium](http://www.chromium.org/Home).

https://chromium.googlesource.com/chromium/src/+/master/third_party/libaddressinput/

## Java

The Java library of _libaddressinput_ is written for use in
[Android](https://developer.android.com/) and includes an Android UI address
input widget ready for use, but only the UI parts are tied to Android.

Non-UI code and tests can be run in Java SE, and the rest of the library could
easily be adapted to run in any Java environment.

### Address validation in general JAVA project.

If you are developing a pure JAVA project, this lib can still be very useful when you want to validate addresses. In this case, the only part we need is the common module. Please following steps below to get started.

* 1. Follow the readme.md inside common module to build the common project. After build succeed, you would find a common.jar within folder: common/build/libs
* 2. Import this common.jar into your project. Now, you should be able to start to code.
* 3. For valiating address, the key class we need is **StandardAddressVerifier.java**
```
// Build address data need to be verified.
final AddressData addressData =
                AddressData.builder().
                        setCountry("US").
                        setAdminArea("CA").
                        setPostalCode("94088").
                        setLocality(Sunnyvale).
                        setAddress("Dream Ave").
                        build();
// address problems, which will be filled by standardAddressVerifier if some data is invalid.
AddressProblems addressProblems = new AddressProblems();

// Verify the address.
standardAddressVerifier.verify(addressData, addressProblems);

// Now, you can see the address problems reside inside addressProblems.
addressProblems.getProblems();
```
## Mailing List

Using and developing libaddressinput is discussed on this mailing list:

https://groups.google.com/forum/#!forum/libaddressinput-discuss
