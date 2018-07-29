/*****************************************
 * log.h   : Improved logging for Esp-Idf
 * Author  : Joao Lopes 
 * Comments: Learn about Esp-Idf logs in http://esp-idf.readthedocs.io/en/latest/api-reference/system/log.html
 *           Tips on gcc logging seen at http://www.valvers.com/programming/c/logging-with-gcc/
 * Versions:
 * ------ 	-------- 	-------------------------
 * 1.0.0  	27/07/18	First version
 *****************************************/

#pragma once

#include <stdbool.h>

// Logs disabled ? (uncomment this to disable all logs)

//#define LOG_DISABLED true

#ifdef LOG_DISABLED

    // Logs disabled
    
    #define LOG_LOCAL_LEVEL ESP_LOG_NONE

#else 

    // Log level (must be first than esp_log include) (choose one and comment anothers)

    #define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
    // #define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
    // #define LOG_LOCAL_LEVEL ESP_LOG_INFO
    // #define LOG_LOCAL_LEVEL ESP_LOG_WARN
    // #define LOG_LOCAL_LEVEL ESP_LOG_ERROR

#endif

// Esp-Idf logging

#include "esp_log.h"

// FreeRTOS 
// Dual or single core ?

#if !CONFIG_FREERTOS_UNICORE
	#define LOG_CORE true   // Log show core ? (comment to disable it)
#endif

// Use a variable to activate logging 
// (usefull to turn on the logs only if need - for example if have a connection, if usb is connected, etc.)
// Comment this for log always active
// If have more modules, please define this variable as external in h file

//#define LOG_ACTIVE_VAR mLogActive

#ifdef LOG_ACTIVE_VAR // Verify variable to show the log

    extern bool LOG_ACTIVE_VAR; // Need to use in another module

    #define LOG_ACTIVE if (LOG_ACTIVE_VAR)

#else // Not use this - always active

    #define LOG_ACTIVE 

#endif

// Macros for logs 

#ifdef LOG_DISABLED

    // No logs

    #define logV(fmt, ...)
    #define logD(fmt, ...)
    #define logI(fmt, ...)
    #define logW(fmt, ...)
    #define logE(fmt, ...)

    #define logIsrV(fmt, ...)
    #define logIsrD(fmt, ...)
    #define logIsrI(fmt, ...)
    #define logIsrW(fmt, ...)
    #define logIsrE(fmt, ...)

#else 

    #ifdef LOG_CORE // Show core in logs ?

        // Normal logs

        #define logV(fmt, ...) LOG_ACTIVE ESP_LOGV(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
        #define logD(fmt, ...) LOG_ACTIVE ESP_LOGD(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
        #define logI(fmt, ...) LOG_ACTIVE ESP_LOGI(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
        #define logW(fmt, ...) LOG_ACTIVE ESP_LOGW(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
        #define logE(fmt, ...) LOG_ACTIVE ESP_LOGE(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)

        // ISR logs (use with caution)

        #define logIsrV(fmt, ...) LOG_ACTIVE ESP_EARLY_LOGV(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
        #define logIsrD(fmt, ...) LOG_ACTIVE ESP_EARLY_LOGD(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
        #define logIsrI(fmt, ...) LOG_ACTIVE ESP_EARLY_LOGI(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
        #define logIsrW(fmt, ...) LOG_ACTIVE ESP_EARLY_LOGW(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
        #define logIsrE(fmt, ...) LOG_ACTIVE ESP_EARLY_LOGE(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)

    #else // Witout core information

        // Normal logs

        #define logV(fmt, ...) LOG_ACTIVE_VAR ESP_LOGV(TAG, "(%s) " fmt, __func__, ##__VA_ARGS__)
        #define logD(fmt, ...) LOG_ACTIVE_VAR ESP_LOGD(TAG, "(%s) " fmt, __func__, ##__VA_ARGS__)
        #define logI(fmt, ...) LOG_ACTIVE_VAR ESP_LOGI(TAG, "(%s) " fmt, __func__, ##__VA_ARGS__)
        #define logW(fmt, ...) LOG_ACTIVE_VAR ESP_LOGW(TAG, "(%s) " fmt, __func__, ##__VA_ARGS__)
        #define logE(fmt, ...) LOG_ACTIVE_VAR ESP_LOGE(TAG, "(%s) " fmt, __func__, ##__VA_ARGS__)

        // ISR logs (use with caution)
        
        #define logIsrV(fmt, ...) LOG_ACTIVE_VAR ESP_EARLY_LOGV(TAG, "(%s) " fmt, __func__, ##__VA_ARGS__)
        #define logIsrD(fmt, ...) LOG_ACTIVE_VAR ESP_EARLY_LOGD(TAG, "(%s) " fmt, __func__, ##__VA_ARGS__)
        #define logIsrI(fmt, ...) LOG_ACTIVE_VAR ESP_EARLY_LOGI(TAG, "(%s) " fmt, __func__, ##__VA_ARGS__)
        #define logIsrW(fmt, ...) LOG_ACTIVE_VAR ESP_EARLY_LOGW(TAG, "(%s) " fmt, __func__, ##__VA_ARGS__)
        #define logIsrE(fmt, ...) LOG_ACTIVE_VAR ESP_EARLY_LOGE(TAG, "(%s) " fmt, __func__, ##__VA_ARGS__)

    #endif

#endif
