# Building and running tests

The common (non-UI) parts of libaddressinput are built and run using the Gradle
project automation tool:

https://developer.android.com/build http://www.gradle.org/

## Prerequisite dependencies for using Gradle

Use Android Studio to build packages and run tests. Alternatively, make use of
the Gradle Wrapper Scripts: `gradlew` or `gradlew.bat`.

## Building and Running

After installing all the prerequisites, check that everything is working by
running:

##### On Linux / Unix / Mac

-   `gradlew build`
-   `gradlew test`

##### On Windows

-   `gradlew.bat build`
-   `gradlew.bat test`
