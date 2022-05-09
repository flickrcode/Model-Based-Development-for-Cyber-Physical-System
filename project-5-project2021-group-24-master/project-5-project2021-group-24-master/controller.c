#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "controller.h"
#include "constants.h"


void controlSystemTask(void *pvParameters) {
    struct ControlSystemParams *params =
        (struct ControlSystemParams*)pvParameters;

    // we keep local copies of the global state + semaphores
    unsigned short motors[4];
    double gyro_data[3];
    double acc_data[3];
    double r_rpdy[3];
    double estimate[3] = {0.0};
    /* K gain multiplied with thrust to motor constant*/
    double K[4][5] =  {{-329.61,   -431.16,   -81.10,   -111.79,   -237.07},
                       {-329.61,    431.16,   -81.10,    111.79,    237.07},
                       {329.61,     431.16,    81.10,    111.79,   -237.07},
                       {329.61,    -431.16,    81.10,   -111.79,    237.07}};

    double BaseMs = 30000;
    double state[5];
    double err[2] = {0.0};
    // copy the semaphore handles for convenience
    SemaphoreHandle_t motors_sem = params->motors_sem;
    SemaphoreHandle_t references_sem = params->references_sem;
    SemaphoreHandle_t sensors_sem = params->sensors_sem;
    SemaphoreHandle_t estimate_sem = params->estimate_sem;

    while(1) {
        // read sensor data (gyro)
        xSemaphoreTake(sensors_sem,portMAX_DELAY);
        memcpy(gyro_data, params->gyro_data, sizeof(gyro_data));
        xSemaphoreGive(sensors_sem);

        // read filter data (angle estimates)
         xSemaphoreTake(estimate_sem,portMAX_DELAY);
        memcpy(estimate, params->estimate, sizeof(estimate));
        xSemaphoreGive(estimate_sem);

        // read latest references
        xSemaphoreTake(references_sem,portMAX_DELAY);
        memcpy(r_rpdy, params->r_rpdy, sizeof(r_rpdy));
        xSemaphoreGive(references_sem);

         // compute error
        state[0] = (estimate[0] - r_rpdy[0]);
        state[1] = (estimate[1] - r_rpdy[1]);
 	state[2] = gyro_data[0];
 	state[3] = gyro_data[1];
	state[4] = gyro_data[2];
        // example of how to log some intermediate calculation
        // and use the provided constants
        params->log_data[0] = crazyflie_constants.m * crazyflie_constants.g;
        params->log_data[2] = r_rpdy[0];


        // compute motor outputs
        for (int i = 0; i<4 ;i++)
        {
            xSemaphoreTake(motors_sem,portMAX_DELAY);
            motors[i] = -(state[0]*K[i][0] +state[1]*K[i][1]+ state[2]*K[i][2] + state[3]*K[i][3] + state[4]*K[i][4]) + BaseMs;
            xSemaphoreGive(motors_sem); 
        }       
        
        
    	/*double max_Ms = 65536;
    for (int i = 0; i < 4; i++) {
            if (motors[i] > max_Ms) {
              motors[i] = max_Ms;
            } else if (motors[i] < 0.0) {
              motors[i] = 0.0;
            }
          }*/
        // write motor output
        xSemaphoreTake(motors_sem,portMAX_DELAY);  
        memcpy(params->motors, motors, sizeof(motors));
        xSemaphoreGive(motors_sem);
        
        // sleep 10ms to make this task run at 100Hz
        vTaskDelay(10 / portTICK_PERIOD_MS);
        //vTaskDelayUntil(&xLastWakeTimeControl, xFrequencyControl) ;
    }
}
