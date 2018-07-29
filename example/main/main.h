/*
 * main.h
 */

#ifndef MAIN_H_
#define MAIN_H_

////// Includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "sdkconfig.h"

#include "esp_log.h"

/////// Defines

// Version

#define VERSION "1.0.0"

// FreeRTOS Task

// Dual or single core ?

#if !CONFIG_FREERTOS_UNICORE
	#define TASK_CPU 1
#else
	#define TASK_CPU 0
#endif

// Priority

#define TASK_PRIO 5

// Stack Depth

#define TASK_STACK 5120


// Logs

#define logV(fmt, ...) if (mLogAtivo) ESP_LOGV(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
#define logD(fmt, ...) if (mLogAtivo) ESP_LOGD(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
#define logI(fmt, ...) if (mLogAtivo) ESP_LOGI(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
#define logW(fmt, ...) if (mLogAtivo) ESP_LOGW(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
#define logE(fmt, ...) if (mLogAtivo) ESP_LOGE(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)

#define logEarlyV(fmt, ...) if (mLogAtivo) ESP_EARLY_LOGV(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
#define logEarlyD(fmt, ...) if (mLogAtivo) ESP_EARLY_LOGD(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
#define logEarlyI(fmt, ...) if (mLogAtivo) ESP_EARLY_LOGI(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
#define logEarlyW(fmt, ...) if (mLogAtivo) ESP_EARLY_LOGW(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)
#define logEarlyE(fmt, ...) if (mLogAtivo) ESP_EARLY_LOGE(TAG, "(%s)(C%d) " fmt, __func__, xPortGetCoreID(), ##__VA_ARGS__)


#endif // MAIN_H_

