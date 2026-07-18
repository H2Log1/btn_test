#include "cmsis_os.h"
#include "main.h"
#include "multi_button.h"

#define BUTTON1_GPIO_Port GPIOD
#define BUTTON1_Pin GPIO_PIN_3
#define BUTTON2_GPIO_Port GPIOD
#define BUTTON2_Pin GPIO_PIN_5

uint16_t click = 0;

uint8_t read_button_gpio(uint8_t button_id)
{
    switch (button_id)
    {
    case 1:
        return HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
    case 2:
        return HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
    default:
        return 0;
    }
}

void LED_Toggle(Button *btn, void *user_data)
{
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
}

void Btn1_Msg_Send(Button *btn, void *user_data)
{
    if (btn->event == BTN_DOUBLE_CLICK)
    {
        click = 2;
    }
    else if (btn->event == BTN_SINGLE_CLICK)
    {
        click = 1;
    }
    osMessageQueuePut(BtnQueueHandle, &click, 0, osWaitForever);
}

void Btn2_Msg_Send(Button *btn, void *user_data)
{

    if (btn->event == BTN_DOUBLE_CLICK)
    {
        click = 4;
    }
    else if (btn->event == BTN_SINGLE_CLICK)
    {
        click = 3;
    }
    osMessageQueuePut(BtnQueueHandle, &click, 0, osWaitForever);
}

void StartBtnTask(void *argument)
{
    static Button btn1;
    static Button btn2;

    button_init(&btn1, read_button_gpio, 0, 1);
    button_init(&btn2, read_button_gpio, 0, 2);

    button_attach(&btn1, BTN_SINGLE_CLICK, Btn1_Msg_Send, NULL);
    button_attach(&btn1, BTN_DOUBLE_CLICK, Btn1_Msg_Send, NULL);
    button_start(&btn1);

    button_attach(&btn2, BTN_SINGLE_CLICK, Btn2_Msg_Send, NULL);
    button_attach(&btn2, BTN_DOUBLE_CLICK, Btn2_Msg_Send, NULL);
    button_start(&btn2);

    for (;;)
    {
        button_ticks();
        osDelay(5);
    }
}