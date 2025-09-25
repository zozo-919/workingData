
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"


static uint32_t g_fac_us = 0;       /* us��ʱ������ */

/* ���SYS_SUPPORT_OS������,˵��Ҫ֧��OS��(������UCOS) */
#if SYS_SUPPORT_OS

#include "FreeRTOS.h"
#include "task.h"

extern void xPortSysTickHandler(void);
/**
 * @brief     systick�жϷ�����,ʹ��OSʱ�õ�
 * @param     ticks : ��ʱ�Ľ�����  
 * @retval    ��
 */  
void SysTick_Handler(void)
{
    HAL_IncTick();
    /* os开始跑了 才执行正常的调度处理 */
    if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
        xPortSysTickHandler();
    }
}
#endif

/**
 * @brief     ��ʼ���ӳٺ���
 * @param     sysclk: ϵͳʱ��Ƶ��, ��CPUƵ��(rcc_c_ck), 180MHz
 * @retval    ��
 */  
void delay_init(uint16_t sysclk)
{
#if SYS_SUPPORT_OS                                      /* �����Ҫ֧��OS */
    uint32_t reload;
#endif
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);/* SYSTICKʹ���ⲿʱ��Դ,Ƶ��ΪHCLK */
    g_fac_us = sysclk;                                  /* �����Ƿ�ʹ��OS,g_fac_us����Ҫʹ�� */
#if SYS_SUPPORT_OS                                      /* �����Ҫ֧��OS. */
    reload = sysclk;                                    /* ÿ���ӵļ������� ��λΪM */
    reload *= 1000000 / configTICK_RATE_HZ;            /* ����delay_ostickspersec�趨���ʱ��?,reloadΪ24λ
                                                         * �Ĵ���,����?:16777216,��180M��,Լ��0.0932s����
                                                         */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;          /* ����SYSTICK�ж� */
    SysTick->LOAD = reload;                             /* ÿ1/delay_ostickspersec���ж�һ�� */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;           /* ����SYSTICK */
#endif 
}

#if SYS_SUPPORT_OS                                      /* �����Ҫ֧��OS, �����´��� */

/**
 * @brief     ��ʱnus
 * @param     nus: Ҫ��ʱ��us��
 * @note      ע��: nus��ֵ,��Ҫ����93206us(���ֵ��?2^24 / g_fac_us @g_fac_us = 180)
 * @retval    ��
 */ 
void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;        /* LOAD��ֵ */
    ticks = nus * g_fac_us;                 /* ��Ҫ�Ľ����� */
    told = SysTick->VAL;                    /* �ս���ʱ�ļ�����ֵ */
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;        /* ����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ����� */
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks) 
            {
                break;                      /* ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳� */
            }
        }
    }
} 

/**
 * @brief     ��ʱnms
 * @param     nms: Ҫ��ʱ��ms�� (0< nms <= 65535) 
 * @retval    ��
 */
void delay_ms(uint16_t nms)
{
   uint32_t i;
   for ( i = 0; i < nms; i++)
   {
        delay_us(1000);
   }
   
}

#else  /* ��ʹ��OSʱ, �����´��� */

/**
 * @brief       ��ʱnus
 * @param       nus: Ҫ��ʱ��us��.
 * @note        ע��: nus��ֵ,��Ҫ����93206us(���ֵ��?2^24 / g_fac_us @g_fac_us = 180)
 * @retval      ��
 */
void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;        /* LOAD��ֵ */
    ticks = nus * g_fac_us;                 /* ��Ҫ�Ľ����� */
    told = SysTick->VAL;                    /* �ս���ʱ�ļ�����ֵ */
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;        /* ����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ����� */
            }
            else 
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;                      /* ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳� */
            }
        }
    }
}

/**
 * @brief       ��ʱnms
 * @param       nms: Ҫ��ʱ��ms�� (0< nms <= 65535)
 * @retval      ��
 */
void delay_ms(uint16_t nms)
{
    uint32_t repeat = nms / 65;     /*  ������60,�ǿ��ǵ������г�ƵӦ�ã�����180M��ʱ��delay_us���ֻ�����?93206us������ */
    uint32_t remain = nms % 65;

    while (repeat)
    {
        delay_us(65 * 1000);        /* ����delay_us ʵ�� 65ms ��ʱ */
        repeat--;
    }

    if (remain)
    {
        delay_us(remain * 1000);    /* ����delay_us, ��β����ʱ(remain ms)������ */
    }
}

/**
 * @brief       HAL���ڲ������õ�����ʱ
 * @note        HAL�����ʱĬ����Systick���������û�п�Systick���жϻᵼ�µ��������ʱ���޷��˳�?
 * @param       Delay : Ҫ��ʱ�ĺ�����
 * @retval      None
 */
void HAL_Delay(uint32_t Delay)
{
     delay_ms(Delay);
}
#endif









