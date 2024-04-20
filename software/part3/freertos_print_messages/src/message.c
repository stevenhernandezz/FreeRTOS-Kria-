/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* Xilinx includes. */
#include "xgpio.h"
#include "xstatus.h"
#include "xparameters.h"
#include <stdio.h>

// Define delay constants
#define x1second 1000
#define x2second 2000
#define x3second 3000
#define x4second 4000

// Function 
static void osPriorityLow(void *arguments);
static void osPriorityBelowNormal(void *arguments);
static void osPriorityNormal(void *arguments);
static void osPriorityHigh(void *arguments);

//tasks
char string1[15] = "Hello World from Task1\n";
char string2[15] = "Hello World from Task2\n";
char string3[15] = "Hello World from Task3\n";
char string4[15] = "Hello World from Task4\n";

// Task
TaskHandle_t task1Handle, task2Handle, task3Handle, task4Handle;

// Tasks 1-4
static void osPriorityLow(void *arguments) {
    //infinite loop/condition to terminate loop
    for (;;) 
    {
        printf(string1);
        vTaskDelay(x1second);

    }
} 

static void osPriorityBelowNormal(void *arguments) {

    for (;;) 
    {
        printf(string2);
        vTaskDelay(x2second);

    }
}

static void osPriorityNormal(void *arguments) {

    for (;;) 
    {
        printf(string3);
        vTaskDelay(x3second);

    }
}

static void osPriorityHigh(void *arguments) {

    for (;;) 
    {
        printf(string4);
        vTaskDelay(x4second);

        for (int i = 0; i < 3; i++) {
            vTaskDelay(x1second);
        }
    }
}

int main(void) {
    // Tasks 1-4
    // Task 1
xTaskCreate(
    // The function that implements the task
    osPriorityLow,              
    // Task name 
    "Task1",                    
     // The stack allocated to the task
    configMINIMAL_STACK_SIZE,
    // The task parameter (not used)  
    NULL,                       
    // The task priority
    tskIDLE_PRIORITY + 1,        
    // Pointer to the task 
    &task1Handle                
);

// Task 2
xTaskCreate(
      // The function that implements the task
    osPriorityBelowNormal,    
    // Task name
    "Task2",                    
    // The stack allocated to the task
    configMINIMAL_STACK_SIZE,   
    // The task parameter (not used)
    NULL,                       
    // The task priority
    tskIDLE_PRIORITY + 2,       
    // Pointer to the task
    &task2Handle                 
);

// Task 3
xTaskCreate(
    // The function that implements the task
    osPriorityNormal,           
    // Text name
    "Task3",                     
    // The stack allocated to the task
    configMINIMAL_STACK_SIZE,   
    // The task parameter (not used)
    NULL,                       
    // The task priority 
    tskIDLE_PRIORITY + 3,       
    // Pointer to the task 
    &task3Handle                
);

// Task 4
xTaskCreate(
    // The function that implements the task
    osPriorityHigh,      
    // Text name        
    "Task4",                
     // The stack allocated to the task    
    configMINIMAL_STACK_SIZE,  
    // The task parameter (not used)
    NULL,                       
    // The task priority
    tskIDLE_PRIORITY + 4,    
    // Pointer to the task    
    &task4Handle                
);

    // Scheduler
    vTaskStartScheduler();
    return 0;
}
