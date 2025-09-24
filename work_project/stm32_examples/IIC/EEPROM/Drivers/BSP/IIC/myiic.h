#ifndef _MYIIC_H
#define _MYIIC_H
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ���� ���� */

#define IIC_SDA_GPIO_PORT                  GPIOA
#define IIC_SDA_GPIO_PIN                   GPIO_PIN_3
#define IIC_SDA_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)             /* PA��ʱ��ʹ�� */

#define IIC_SCL_GPIO_PORT                  GPIOA
#define IIC_SCL_GPIO_PIN                   GPIO_PIN_2
#define IIC_SCL_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)             /* PA��ʱ��ʹ�� */

/******************************************************************************************/
#define IIC_SDA(x)   do{ x ? \
                      HAL_GPIO_WritePin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)  

#define IIC_SCL(x)   do{ x ? \
                      HAL_GPIO_WritePin(IIC_SCL_GPIO_PORT, IIC_SCL_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(IIC_SCL_GPIO_PORT, IIC_SCL_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)  

#define IIC_READ_SDA       HAL_GPIO_ReadPin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN)   

/******************************************************************************************/
/* �ⲿ�ӿں���*/
void iic_init(void);
void iic_start(void);
void iic_stop(void);
void iic_ack(void);
void iic_nack(void);
uint8_t iic_wait_ack(void);
void iic_send_byte(uint8_t data);
uint8_t iic_read_byte(uint8_t ack);
                  
#endif
