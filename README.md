# LibTesting-HTTP

- [Overview](#overview)
- [Required Libraries](#required-libraries)
- Usage:
  - [With PlatformIO](#platformio)
  - [With Arduino IDE](#arduino-ide)
- [The Functions](#the-functions)
- [An Example](#an-example)

## Overview
This is (well... will be...) a collection of wrappers & stuff for creating a consistant web server on an ESP.

Primarily, it's for building an AP & OTA interface.  But it should come in handy for a lot more.

## Required Libraries:

This library uses [my DEBUG library](https://github.com/cdntinker/TinkerLibs-DEBUGhttps://github.com/cdntinker/TinkerLibs-DEBUG).

* ESP Async WebServer
    * https://github.com/me-no-dev/ESPAsyncWebServer

### ESP8266

* foo
    * https://github.com/foo/bar

### ESP32

* Update
    * https://github.com/espressif/arduino-esp32/tree/master/libraries
* FS
    * https://github.com/espressif/arduino-esp32/tree/master/libraries

## Usage

### PlatformIO

In `platformio.ini`, add https://github.com/cdntinker/TinkerLibs-HTTP to your `lib-deps` for the project.

```
lib_deps =
   Some Library
   https://github.com/cdntinker/TinkerLibs-DEBUG
   https://github.com/cdntinker/TinkerLibs-HTTP
   Some Other Library
```

Then add `#include "Tinker_HTTP.h"` to any source file you want to reference these functions in.

### Arduino IDE

No idea...  Don't use it...

Anybody wanna work this out for me?

## The Functions

These are all declared in **Tinker_HTTP.h**

### `void setup_HTTP()`
Fill me in

## An Example
Sorry...  Not yet.
