# ESP-IDF-Improved-Logging

### Improved logging to esp-idf projects

#### Works with the ESP32 - esp-idf v3.0 or higher. Refer to https://github.com/espressif/esp-idf

## Contents
 - [About](#about)
 - [Example of use](#example)
 - [Using _log.h_ macros](#macros)
 - [Profiler](#profiler)
 - [Releases](#releases)
 - [Releases](#releases)
 - [Thanks](#thanks)

## About

This include file _log.h_ extends the powerfull ESP_LOGx with:

    - Show the function name thats the log origins
        This is usefull to debug, without need 
        put function names in each log

    - Show the core (C0 or C1)
         That indicates the core that is executing 
         the function that contains the log call
         Usefull to optimize and balance Esp32 multi-core 

This is done with pre-compiler macros

## Example of use

How about this:

```
void createTask2 () {

    // Create a task 2 @ core 1 (if have it)

    logD("creating task 2");

    ....
}
```

And log output of esp-idf monitor will show it:

```
D (1650)P(02) demo_log: (createTask2)(C0) creating task 2
```

Where:

    D               -> level of this ESP_LOG
    (1650)          -> ESP_LOG time
    P(02)           -> Profile (if my [ESP-IDF-Monitor-Simple-Profiler](https://github.com/JoaoLopesF/ESP-IDF-Monitor-Simple-Profiler) is installed)
    demo_log        -> ESP_LOG Tag
    (createTask2)   -> Name of running function - added by log.h macros
    (C0)            -> Core number of running function - added by log.h macros
    creating task 2 -> Messagem passed to log.h macros

Please download and flash the example application to learn about _log.h_

Example output to esp-idf monitor:
    [Imgur](https://i.imgur.com/ZVCQENq.png)

## Using

In _log.h_ have this macros for normal logging:

    logV(fmt, ...)  - Verbose level
    logD(fmt, ...)  - Debug level
    logI(fmt, ...)  - Info level
    logW(fmt, ...)  - Warning level
    logE(fmt, ...)  - Error level

And to use in ISR routines (call the ESP_EARLY_LOGV (ets_printf) to not crash Esp32)

    logIsrV(fmt, ...)  - Verbose level
    logIsrD(fmt, ...)  - Debug level
    logIsrI(fmt, ...)  - Info level
    logIsrW(fmt, ...)  - Warning level
    logIsrE(fmt, ...)  - Error level

Attention: Use this with caution !!! Simple use of ESP_EARLY_LOG can be delay the critical ISR code

Please open the code to learn more how use this.  

Please see _log.h_ file about configurations, as:

    - Log level
    - Log cpu core id
    - Log activation by global variable 

## Profiler

You can improve more Esp32 logging, installing my simple profiler to esp-idf

    [ESP-IDF-Monitor-Simple-Profiler](https://github.com/JoaoLopesF/ESP-IDF-Monitor-Simple-Profiler)

## Disclamer:

    This logging is for use in development, please disable the _log.h_ logging before put your project in prodution.

    Simple uncomment it in _log.h_:

        ``` 
        //#define LOG_DISABLED true
        ```

## Releases

    1.0.0 - First version

## Resources

Resources:

- Learn more about Esp-Idf logs in http://esp-idf.readthedocs.io/en/latest/api-reference/system/log.html
- Tips on gcc logging seen at http://www.valvers.com/programming/c/logging-with-gcc/

