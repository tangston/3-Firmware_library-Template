/*bsp   板级支持包的意思*/

#include "bsp_led.h"

/*  @brief:这里开启数码管/LED的外设时钟+负责选择的GPIOB的时钟+AFIO复用端口的时钟
*
*
*/
void LED_SEG_CLK_Init(void){
  /*首先启动时钟，为什么是启动这个时钟，可以参考ST中文手册，2.1系统架构，RCC的APB2连接的外设*/
  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);//使能数码管和LED的外设时钟
  RCC_APB2PeriphClockCmd(SEL_GPIO_CLK, ENABLE);//使能select的 GPIOB clock
  RCC_APB2PeriphClockCmd(LED_AFIO_CLK, ENABLE);//使能复用端口时钟
}

/*  @brief  这里把 LED/SEG+负责选择 的输出寄存器全部配置为推挽输出
*
*
*/
void LED_SEG_GPIO_Config(void){
    uint32_t x=0;
    uint32_t LED_x_GPIO_Pin[]={
    LED_0_GPIO_Pin,LED_1_GPIO_Pin,LED_2_GPIO_Pin,LED_3_GPIO_Pin
  , LED_4_GPIO_Pin,LED_5_GPIO_Pin,LED_6_GPIO_Pin,LED_7_GPIO_Pin };
   
  /*  LED/SEG 统一设置成通用推挽输出和50MHZ的最大速度*/
    GPIO_InitTypeDef  GPIO_InitStruct;//这里是要初始化封装好的 GPIO配置初始化 结构体
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
  
  for(;x<=7;++x){
       
    GPIO_InitStruct.GPIO_Pin=LED_x_GPIO_Pin[x];
    GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);
     
  }
}
/*  @brief 这里是用来 配置 专门用来做选择的IO  如 LED or SEGMENT。SEL from SEGs。JTAG-DP or SW-DP
**  @param  void
**  
*/
void SEL_GPIO_Config(void){
    uint32_t x=0;
    uint32_t SEL_GPIO_Pin[]={SEL_GPIO_0_Pin,SEL_GPIO_1_Pin,SEL_GPIO_2_Pin,SEL_GPIO_3_Pin};
   
  /*  LED 统一设置成通用推挽输出和50MHZ的最大速度*/
    GPIO_InitTypeDef  GPIO_InitStruct;//这里是要初始化封装好的 GPIO配置初始化 结构体
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
  
  for(;x<=3;++x){
       
    GPIO_InitStruct.GPIO_Pin=SEL_GPIO_Pin[x];
    GPIO_Init(SEL_GPIO_Port, &GPIO_InitStruct);     
  }
}
/*  @brief:  select LED or SEGMENT.   LED的选择是高电平有效，SEG是低电平有效
*       @argument:  Select_LED    ,   Select_SEG 
*   
*/
void LED_SEG_Select_CMD(State NewState){
  
  if(NewState == Select_LED){    
    GPIO_SetBits(SEL_GPIO_Port,SEL_GPIO_3_Pin);
  }else{
    GPIO_ResetBits(SEL_GPIO_Port,SEL_GPIO_3_Pin);
  }
}

/*
*
* 这里等以后学了重映射和复用配置再写
*/

    void AFIO_Init(void){
      AFIO->MAPR |= 0x02000000;//关闭JTAG-DP，启用SW-DP
    }



