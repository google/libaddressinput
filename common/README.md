# Building and running tests


The common (non-UI) parts of libaddressinput are built and run using the Gradle
project automation tool:

http://tools.android.com/tech-docs/new-build-system
http://www.gradle.org/


## Prerequisite dependencies for using Gradle

The only prerequisite is a compatible Java Development Kit correctly installed,
with java, javac, and related commands available in your PATH environment.

This project makes use of the [Gradle Wrapper Scripts] to ensure repeatable builds and use of the
same Gradle version across contributors. Depending on your operating system, Gradle can be invoked
from the root project directory by using either the `gradlew` or `gradlew.bat` command from your
preferred shell environment.

Note: It is recommended to always use the included wrapper scripts to invoke Gradle to
avoid issues which may be caused by having multiple versions of Gradle on your PATH.


## Building and Running

After installing all the prerequisites, check that everything is working by
running:

##### On Linux / Unix / Mac
`$ gradlew build`
`$ gradlew test`

##### On Windows
`$ gradlew.bat build`
`$ gradlew.bat test`

[Gradle Wrapper Scripts]: https://docs.gradle.org/current/userguide/gradle_wrapper.html#sec:using_wrapper