/*
 * ===========
 * Project    : Demo EspLog - ESP-IDF
 * Author     : Joao Lopes
 * Modulo     : Main 
 * Comments   : Only a demo to show how to use the log
 */

////// Defines

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

/////// Includes

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
// #include "esp_log.h"

#include "sdkconfig.h"

#include "log.h"

////// Defines

// Version

#define VERSION "1.0.0"

// FreeRTOS Task

#define TEST1_TASK_CPU PRO_CPU_NUM

// Dual or single core ?

#if !CONFIG_FREERTOS_UNICORE
	#define TEST2_TASK_CPU 1
#else
	#define TEST2_TASK_CPU 0
#endif

// Priority

#define TEST_TASK_PRIO 5

// Stack Depth

#define TEST_TASK_STACK 5120

///// Variables

// Log

static const char* TAG = "demo_log";  // Tag for logs

#ifdef LOG_ACTIVE_VAR
bool LOG_ACTIVE_VAR = false; // Log active ? (used in log macros) 
#endif

// Tasks

static TaskHandle_t xTaskTest1Handler = NULL;
static TaskHandle_t xTaskTest2Handler = NULL;

////// Prototypes

static void test1_Task(void *pvParameters);
void createTask2 ();
static void test2_Task(void *pvParameters);

////// App Main

void app_main(void)
{

#ifdef LOG_ACTIVE_VAR
    // Activating the log
    // For example it can be place in events (for example: connections, only if usb is plugged. etc. ), to only show log if need

    mLogActive = true;
#endif

    // First log (empty to only show the name of this function)

    logV("");

    // Create task 1

    logD("creating task 1");
    xTaskCreatePinnedToCore(&test1_Task,
                            "test1_Task", TEST_TASK_STACK, NULL, TEST_TASK_PRIO, &xTaskTest1Handler, TEST1_TASK_CPU);
    
    // Create task 2

    logD("creating task 2");
    createTask2();
    
    return;
}

////// Routines

static void test1_Task(void *pvParameters) {

	// Test1 Task 

	logI("Init task");

	/////// Variables

	// Count

	int16_t count = 0;

	////// FreeRTOS

	// Timeout - time delay to task

	const TickType_t xTicks = (2000u / portTICK_RATE_MS);

	////// Loop

	for (;;) {

        // Wait 

        vTaskDelay (xTicks);

        // Count

        count++;

        // Debug (tip => if log level is debug, only show it each 5 secs)

        if (count % 5 == 0) {
            logD("count=%u", count);
        } else {
            logV("count=%u", count);
        }

        // Delete task 1 ?

        if (count == 10 && xTaskTest2Handler != NULL) { // 

            logD("deleting task 2");
            vTaskDelete (xTaskTest2Handler);
            xTaskTest2Handler = NULL;

        } else if (count == 15) { 
            
            // Reset the counter

            logV("task 1 counter reset");

            count = 0;

            // Create task 2 again 

            logV("creating task 2 again");

            createTask2();
        }
	}

	////// Fim

	logI("task end");

	// Delete this task

	vTaskDelete(NULL);
    xTaskTest1Handler = NULL;
}

void createTask2 () {

    // Create a task 2 @ core 1 (if have it)

    logD("creating task 2");
    xTaskCreatePinnedToCore(&test2_Task,
                            "test2_Task", TEST_TASK_STACK, NULL, TEST_TASK_PRIO, &xTaskTest2Handler, TEST2_TASK_CPU);

}

static void test2_Task(void *pvParameters) {

	// Test1 Task 

	logI("Init task");

	/////// Variables

	// Count

	int16_t count = 0;

	////// FreeRTOS

	// Timeout - time delay to task

	const TickType_t xTicks = (1000u / portTICK_RATE_MS);

	////// Loop

	for (;;) {

        // Wait 

        vTaskDelay (xTicks);

        // Count

        count++;

        // Debug (tip => if log level is debug, only show it each 5 secs)

        if (count % 5 == 0) {
            logD("count=%u", count);
        } else {
            logV("count=%u", count);
        }

	}

	////// Fim

	logI("task end");

	// Delete this task

	vTaskDelete(NULL);
    xTaskTest2Handler = NULL;
}
