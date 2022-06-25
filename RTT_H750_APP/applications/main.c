#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

int main(void)
{
    LOG_D("Hello RT-Thread!");
    while (1)
    {
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}
