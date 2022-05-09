#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "filter.h"
#include "constants.h"
#define PI 3.141592654

void filterTask(void *pvParameters) {
    struct FilterParams *params =
        (struct FilterParams*)pvParameters;

    // we keep local copies of the global state + semaphores
    double gyro_data[3];
    double acc_data[3];

    // copy the semaphore handles for convenience
    SemaphoreHandle_t sensors_sem = params->sensors_sem;
    SemaphoreHandle_t estimate_sem = params->estimate_sem;

    // local internal state.
    double estimate[3] = {0.0};
    double gphi; double gtheta; double phi; double theta;

    portTickType xLastWakeTimeFilter;
    const portTickType xFrequencyFilter = 8;

    while(1) {
        xLastWakeTimeFilter = xTaskGetTickCount();

        // read sensor data
        xSemaphoreTake(sensors_sem, 1 / portTICK_PERIOD_MS);
        memcpy(gyro_data, params->gyro_data, sizeof(gyro_data));
        xSemaphoreGive(sensors_sem);
        xSemaphoreTake(sensors_sem, 1 / portTICK_PERIOD_MS);
        memcpy(acc_data, params->acc_data, sizeof(acc_data));
        xSemaphoreGive(sensors_sem);

        // apply filter
        xSemaphoreTake(estimate_sem, 1 / portTICK_PERIOD_MS);

        // estimate of the yaw angle provided as an example
        phi = atan2(acc_data[1],acc_data[2])*180.0/PI;
        theta = atan2(-acc_data[0],sqrt(pow(acc_data[1],2)+pow(acc_data[2],2)))*180.0/PI;
        double Ts = 0.01;
        gphi = gyro_data[0]*Ts;
        gtheta = gyro_data[1]*Ts;


        //estimate[2] += 0.01 * gyro_data[2];
        estimate[0] = phi*0.02 + (estimate[0]+gphi)*0.98;
        estimate[1] = theta*0.02 + (estimate[1]+gtheta)*0.98;

        // example of how to log some intermediate calculation
        params->log_data[1] = 0.01 * gyro_data[2];

        // write estimates output
        memcpy(params->estimate, estimate, sizeof(estimate));
        xSemaphoreGive(estimate_sem);

        // sleep 10ms to make this task run at 100Hz
        //vTaskDelay(10 / portTICK_PERIOD_MS);
        vTaskDelayUntil(&xLastWakeTimeFilter, xFrequencyFilter) ;
    }
}
