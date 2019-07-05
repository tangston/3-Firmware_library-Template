
#ifndef __BSP_LED_H
#define __BSP_LED_H
#define State  uint32_t
#include "stm32f10x.h"

/*管脚是这个LED片上外设上面的管脚,这里定义的就是LED的管脚和GPIO引出的管脚的联系*/
#define LED_0_GPIO_Pin   GPIO_Pin_8     //板子上L0连的是GPIO的第八个管脚
#define LED_1_GPIO_Pin   GPIO_Pin_9 
#define LED_2_GPIO_Pin   GPIO_Pin_10  
#define LED_3_GPIO_Pin   GPIO_Pin_11  
#define LED_4_GPIO_Pin   GPIO_Pin_12  
#define LED_5_GPIO_Pin   GPIO_Pin_13  
#define LED_6_GPIO_Pin   GPIO_Pin_14  
#define LED_7_GPIO_Pin   GPIO_Pin_15  

#define LED_GPIO_Port  GPIOE          // LED/SEG 用的是GPIOE
#define LED_GPIO_CLK  RCC_APB2Periph_GPIOE  //这里点开stm32f10x_rcc.c，搜索一下关键字，参数都给你制定好了
#define LED_AFIO_CLK  RCC_APB2Periph_AFIO //复用端口的时钟

/*  seg:segment,数码管是一段一段显示的，故取名SEG
**  SEL：取select前三个字母
**  因为SEG和LED复用了，所以写在了一起
*/
#define SEL_GPIO_0_Pin      GPIO_Pin_0//0到2是三个位，作为8个数码管只有谁亮的状态
#define SEL_GPIO_1_Pin      GPIO_Pin_1
#define SEL_GPIO_2_Pin     GPIO_Pin_2
#define SEL_GPIO_3_Pin     GPIO_Pin_3//他设置推挽输出之后，对应数据位输出1是LED有效，数据位输出0是数码管有效
#define SEL_GPIO_Port   GPIOB     //SELECT 用的是GPIOB
#define SEL_GPIO_CLK    RCC_APB2Periph_GPIOB//段选与LED/SEG选择的GPIOB时钟

#define Select_LED        0
#define Select_SEG        1


void LED_SEG_CLK_Init(void);
void LED_SEG_GPIO_Config(void);
void SEL_GPIO_Config(void);
void LED_SEG_Select_CMD(State NewState);

 
void AFIO_Init(void);
#endif /*__BSP_LED_H*/

