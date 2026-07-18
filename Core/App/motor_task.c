#include "cmsis_os.h"
#include "main.h"
#include "Emm_V5.h"
#include "stdbool.h"

typedef struct MOTOR{
    uint8_t addr;
    uint8_t dir[2]; //正转，反转
    double vel;
    double acc;
    double round;
    bool snF;
    bool svF;
} MOTOR;

MOTOR motor[2] = {
    // {0x01, {0x01, 0x00}, 2000.0, 200.0, 1, true, true}, 
    // {0x02, {0x00, 0x01}, 2000.0, 200.0, 1, true, true} 
    {0x01, {0x01, 0x00}, 2000.0, 200.0, 0.05, false, true}, 
    {0x02, {0x00, 0x01}, 200.0, 200.0, 1.0, false, true}  
};

void Step_Motor_Vel_Set(float x_rpm, float y_rpm) {
    
    osDelay(10);
}



void StartMotorTask(void *argument){
    Emm_V5_En_Control(motor[0].addr, true, motor[0].snF);
    osDelay(10);
    Emm_V5_En_Control(motor[1].addr, true, motor[1].snF);
    osDelay(10);

    // Emm_V5_Origin_Set_O(motor[0].addr, motor[0].svF);
    // osDelay(10);
    // Emm_V5_Origin_Set_O(motor[1].addr, motor[1].svF);
    // osDelay(10);

    for(;;){
        osMessageQueueGet(BtnQueueHandle, &click, 0, osWaitForever);
        if (click == 1) {
            // Emm_V5_Pos_Control(motor[0].addr, motor[0].dir[0], motor[0].vel, motor[0].acc, 3200*motor[0].round, 0x00, motor[0].snF);
            // osDelay(10);
            // Emm_V5_Pos_Control(motor[1].addr, motor[1].dir[1], motor[1].vel, motor[1].acc, 3200*motor[1].round, 0x00, motor[1].snF);
            // osDelay(10);
            // Emm_V5_Synchronous_motion(0x00);

            // Emm_V5_Pos_Control(motor[0].addr, motor[0].dir[0], motor[0].vel, motor[0].acc, 3200*motor[0].round, 0x00, motor[0].snF);
            // osDelay(1000);
            // Emm_V5_Pos_Control(motor[1].addr, motor[1].dir[1], motor[1].vel, motor[1].acc, 3200*motor[1].round, 0x00, motor[1].snF);
            // osDelay(1000);
            // Emm_V5_Pos_Control(motor[0].addr, motor[0].dir[1], motor[0].vel, motor[0].acc, 3200*motor[0].round, 0x00, motor[0].snF);
            // osDelay(1000);
            // Emm_V5_Pos_Control(motor[1].addr, motor[1].dir[0], motor[1].vel, motor[1].acc, 3200*motor[1].round, 0x00, motor[1].snF);
            // osDelay(1000);

            // Emm_V5_Synchronous_motion(0x00);





        }
        else if(click == 2)
        {
            // Emm_V5_Pos_Control(motor[0].addr, motor[0].dir[1], motor[0].vel, motor[0].acc, 3200*motor[0].round, 0x00, motor[0].snF); 
            // osDelay(10);
            // Emm_V5_Pos_Control(motor[1].addr, motor[1].dir[0], motor[1].vel, motor[1].acc, 3200*motor[1].round, 0x00, motor[1].snF); 
            // osDelay(10);
            // Emm_V5_Synchronous_motion(0x00);

            // Emm_V5_Origin_Trigger_Return(motor[0].addr, 0x00, motor[0].snF);
            // osDelay(10);
            // Emm_V5_Origin_Trigger_Return(motor[1].addr, 0x00, motor[1].snF);
            // osDelay(10);
            // Emm_V5_Synchronous_motion(0x00);

            osDelay(10);
        }
    }
}