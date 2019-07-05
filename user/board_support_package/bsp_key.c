#include  "bsp_key.h"
void delay1(){
  int count=0x5f000;
  while(count--);
}

/**
* @brief 初始化按键端口及其时钟
* @param void
* @retval void
* 
*/
void KEY_GPIO_Config(void){
  
  GPIO_InitTypeDef  GPIO_InitStruct;
  uint32_t  KEY_GPIO_Pin[]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2};
  uint32_t  x=0;
  
  RCC_APB2PeriphClockCmd(KEY_GPIO_CLK,ENABLE);//启动Key按键外设时钟
 
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
  
  for( ;x<=2;++x){
    
    GPIO_InitStruct.GPIO_Pin=KEY_GPIO_Pin[x];
    GPIO_Init(KEY_GPIO_Port,&GPIO_InitStruct);
    
  }
  
}

/**
* @brief 检测是否有按键按下
* @param GPIOx:具体的端口, x 可以是（C）
* @param GPIO_Pin:具体的端口位， 可以是 GPIO_PIN_x（x 可以是 0...2）
* @retval 按键的状态
* @arg KEY_UP:按键没按下
* @arg KEY_DOWN:按键按下
*/
uint32_t  KEY_SCAN(GPIO_TypeDef*   GPIOx   , uint16_t  GPIO_Pin){
  
 if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==0){
      delay1();
      return 1;
 }
 return 0;
  
}

