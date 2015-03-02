# ![](https://github.com/googlei18n/libaddressinput/wiki/libaddressinput-icon-70x55.png) libaddressinput

[![Build Status](https://drone.io/github.com/googlei18n/libaddressinput/status.png)](https://drone.io/github.com/googlei18n/libaddressinput/latest)

The _libaddressinput_ project consists of two different libraries (one
implemented in C++, one implemented in Java for Android) that use
[address metadata](https://github.com/googlei18n/libaddressinput/wiki/AddressValidationMetadata)
from
[Google](https://developers.google.com/)'s
[I18n Services](https://i18napis.appspot.com/)
[Address Data Service](https://i18napis.appspot.com/address)
to assist application developers in collecting and handling _postal addresses_
from all over the world.

These libraries can provide information about what input fields are required for
a correct address input form for any country in the world and can validate an
address to highlight input errors like missing required fields or invalid
values.

## C++

The C++ library (in very portable C++03) of _libaddressinput_ is the backend for
[requestAutocomplete()](http://www.html5rocks.com/en/tutorials/forms/requestautocomplete/)
in [Chromium](http://www.chromium.org/Home). The source code for that is a good
example of how to use this library to implement a complex feature in a real
application:

https://src.chromium.org/viewvc/chrome/trunk/src/third_party/libaddressinput/
https://chromium.googlesource.com/chromium/src/+/master/third_party/libaddressinput/

Video: [Easy International Checkout with Chrome](https://www.youtube.com/watch?v=ljYeHwGgzQk)

## Java

The Java library of _libaddressinput_ is written for use in
[Android](https://developer.android.com/) and includes an Android UI address
input widget ready for use, but only the UI parts are tied to Android.

Non-UI code and tests can be run in Java SE, and the rest of the library could
easily be adapted to run in any Java environment.

## Mailing List

Using and developing libaddressinput is discussed on this mailing list:

https://groups.google.com/forum/#!forum/libaddressinput-discuss
