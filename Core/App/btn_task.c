#include "cmsis_os.h"
#include "main.h"
#include "multi_button.h"

#define BUTTON1_GPIO_Port GPIOD
#define BUTTON1_Pin GPIO_PIN_3

uint16_t click = 0;

uint8_t read_button_gpio(uint8_t button_id)
{
    switch (button_id) {
        case 1:
            return HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
        default:
            return 0;
    }
}

void LED_Toggle(Button* btn, void* user_data)
{
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_4);
}

void Btn_Msg_Send(Button* btn, void* user_data)
{
    if (btn->event == BTN_DOUBLE_CLICK) {
        click = 2;
    }
    else if (btn->event == BTN_SINGLE_CLICK) {
        click = 1;
    }
    osMessageQueuePut(BtnQueueHandle, &click, 0, osWaitForever);
}

void StartBtnTask(void *argument){
    static Button btn1;
    button_init(&btn1, read_button_gpio, 0, 1);
    button_attach(&btn1, BTN_SINGLE_CLICK, Btn_Msg_Send, NULL);
    button_attach(&btn1, BTN_DOUBLE_CLICK, Btn_Msg_Send, NULL);
    button_start(&btn1);

    for(;;){
        button_ticks();
        osDelay(5);
    }
}