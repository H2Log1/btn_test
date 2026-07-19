#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

extern void Motor_Init(void);
extern void Motor_Stop(void);
extern void Motor_Set_Vel(int16_t motor_vel);

#endif // MOTOR_H