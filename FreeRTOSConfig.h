#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION 1
#define configCPU_CLOCK_HZ 1000000
#define configTICK_RATE_HZ 1000
#define configMAX_PRIORITIES 5
#define configMINIMAL_STACK_SIZE 128
#define configTOTAL_HEAP_SIZE (10 * 1024)
#define configUSE_MUTEXES 1

#endif
