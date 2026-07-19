#include "cmsis_os.h"

void StartGetPIDTask(void *argument)
{
    for (;;)
    {
        osDelay(1);
    }
}