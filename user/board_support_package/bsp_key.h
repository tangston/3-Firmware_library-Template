
#ifndef __BSP_SEG_H
#define __BSP_SEG_H

#include "stm32f10x.h"
#define   true 1
#define   false 0
#define KEY_GPIO_Port   GPIOC
#define KEY_GPIO_CLK    RCC_APB2Periph_GPIOC

#define KEY1_GPIO_Pin       GPIO_Pin_0
#define KEY2_GPIO_Pin       GPIO_Pin_1
#define KEY3_GPIO_Pin       GPIO_Pin_2

/** 按键按下标置宏
* 按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
* 若按键按下为低电平，把宏设置成 KEY_ON=0 ，KEY_OFF=1 即可
*/
#define KEY_UP             1
#define KEY_DOWN           0


void KEY_GPIO_Config(void);
uint32_t  KEY_SCAN(GPIO_TypeDef*   GPIOx   , uint16_t  GPIO_Pin);
#endif /*__BSP_LED_H*/

