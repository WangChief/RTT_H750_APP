/**
    1、输出：
        1）使用正点原子开发板北极星的按钮LED0(PB1)和LED1(PB0)作为输出IO测试。
        2）按钮按下后，LED0亮
        3）按钮松开后，LED0灭
    2、输入：
        1）使用正点原子开发板北极星的按钮KEY0(PH3)作为输入进行检测
        2）按钮按下后，LED0亮
        3）按钮松开后，LED0灭
    3、中断：
        1）使用正点原子开发板北极星的按钮KEY1(PH2)作为中断输入
        2）按钮按下后，LED1亮
        3）按钮松开后，LED1灭
**/

#include "rtthread.h"
#include "board.h"

//宏定义进行管脚编号的获取。
#define LED0            GET_PIN(B,1)
#define LED1            GET_PIN(B,0)

static  rt_uint32_t     KEY0 = 0;
static  rt_uint32_t     KEY2 = 0;



void exti_callback()
{
    if(rt_pin_read(KEY2) == PIN_LOW)
    {
        rt_pin_write(LED1, PIN_LOW);
    }
    else
    {
        rt_pin_write(LED1, PIN_HIGH);
    }
}

void example_gpio()
{
    //通过API获取管脚编号
    KEY0 = rt_pin_get("PH.3");
    KEY2 = rt_pin_get("PC.13");

    //设置管脚模式
    rt_pin_mode(LED0, PIN_MODE_OUTPUT);
    rt_pin_mode(LED1, PIN_MODE_OUTPUT);
    rt_pin_mode(KEY0, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY2, PIN_MODE_INPUT_PULLUP);

    //测试LED灯输出
    for(rt_int8_t i = 0; i<5 ; i++)
    {
        rt_pin_write(LED0, PIN_LOW);
        rt_pin_write(LED1, PIN_LOW);
        rt_thread_delay(500);
        rt_pin_write(LED0, PIN_HIGH);
        rt_pin_write(LED1, PIN_HIGH);
        rt_thread_delay(500);
    }

    //中断回调函数绑定
    rt_pin_attach_irq(KEY2, PIN_IRQ_MODE_RISING_FALLING, exti_callback, RT_NULL);
    //中断使能
    rt_pin_irq_enable(KEY2, PIN_IRQ_ENABLE);

    while(1)
    {
        if(rt_pin_read(KEY0) == PIN_LOW)
        {
            rt_pin_write(LED0, PIN_LOW);
        }
        else
        {
            rt_pin_write(LED0, PIN_HIGH);
        }
        rt_thread_delay(200);
    }
}
MSH_CMD_EXPORT(example_gpio, example_gpio)
