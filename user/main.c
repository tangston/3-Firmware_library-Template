#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"

/*�Ѱ˸���ˮ�Ƹ����������������*/
uint32_t LED_x[]={  LED_0_GPIO_Pin, LED_1_GPIO_Pin, LED_2_GPIO_Pin, LED_3_GPIO_Pin,
                      LED_4_GPIO_Pin, LED_5_GPIO_Pin, LED_6_GPIO_Pin, LED_7_GPIO_Pin  };

void led_mode1_left(int *the_first_light,uint32_t GPIO_Pin_x[]);
void led_mode1_right(int *the_first_light,uint32_t GPIO_Pin_x[]);

void led_mode2_right(int *the_first_dark,uint32_t GPIO_Pin_x[]);
void led_mode2_left(int *the_first_dark,uint32_t GPIO_Pin_x[]);
void delay(void);
                      
void  delay(void){
  int count =0x1f000;
  while(count--);
}  

int main(void){
    
    int  count=0;

    LED_SEG_CLK_Init( );
    // stm32��λ��JTAG��SWĬ��ͬʱ�����ģ������е�JTAG�˿ھ���ϵͳ�������������GPIO�ǲ������õ�
   // AFIO->MAPR |= 0x02000000;//�ر�JTAG-DP������SW-DP����ǰ��Ҫ���� LED��SEGʱ�ӡ�SELʱ�ӡ�AFIOʱ�ӣ����رյĻ�����ռ��һЩ����������޷�������
    AFIO_Init();
    LED_SEG_GPIO_Config(  );
    SEL_GPIO_Config(  );
    LED_SEG_Select_CMD(Select_LED);
  //LED_SEG_Select_CMD(Select_SEG);
    KEY_GPIO_Config();
  /*  �Ĵ�����̰汾��Ч�������������ͬ
    RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��
    GPIOC->CRL&=0XFFFFF000;//PC0-2���ó�����	  
    GPIOC->CRL|=0X00000888;   
*/
  
    while(1){
      
         if(KEY_SCAN(KEY_GPIO_Port, KEY1_GPIO_Pin)==1){ 
            count =0;
           while(count<=0x20){
             led_mode1_left(&count,LED_x);
           }
         }else if(KEY_SCAN(KEY_GPIO_Port,KEY2_GPIO_Pin)==1){
            count =0;
           while(count<=0x20){
             led_mode1_right(&count,LED_x);
            }
           }else if(KEY_SCAN(KEY_GPIO_Port,KEY3_GPIO_Pin)==1){
            count =0;
           while(count<=0x20){
             led_mode2_left(&count,LED_x);
           }
         }
  }
}

/**
* @brief ��һ�����������������
* @param *the_first_light:��������������������a=3������ʱ &a ���ɣ����и���֮����Զ���*the_first_lightָ���ڴ��ֵ+1
* @param uint32_t GPIO_Pin_x[]���ﻹû���úã�Ӧ��������������ֱ�ӵ�����ã���ΪLEDһ����7��
* 
*/
void led_mode1_left(int *the_first_light,uint32_t GPIO_Pin_x[]){
    //��ʼ��һ�������Ϊȫ�� 
    GPIO_ResetBits(GPIOE,GPIO_Pin_All);
    
    
    int led_number=*the_first_light;//����һ�£���Ҫ��������
    (* the_first_light)++;

    led_number %=8;

    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
     
}
/**
* @brief ��һ��������right�ҷ��������
* @param *the_first_light:��������������������a=3������ʱ &a ���ɣ����и���֮����Զ���*the_first_lightָ���ڴ��ֵ+1
* @param uint32_t GPIO_Pin_x[]���ﻹû���úã�Ӧ��������������ֱ�ӵ�����ã���ΪLEDһ����7��
* 
*/
void led_mode1_right(int *the_first_light,uint32_t GPIO_Pin_x[]){
     //��ʼ��һ�������Ϊȫ��
      GPIO_ResetBits(GPIOE,GPIO_Pin_All);
    
    int led_number=-(*the_first_light);//����һ�£���Ҫ��������
    (* the_first_light)++;
    
    //led��GPIOE��pin8��15
    led_number %=8;
    if(led_number==0){led_number --;}//led_number=0�������ᱻ��λ��ȫ�������︴��ճ����ʱ��㷴�ˣ����øĴ��룬�ɴ�Ĳ���
    
    led_number  +=  8;
    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    
     
}


/**
* @brief ��һ���������������ƣ�����������Ĭ��ȫ��
* @param *the_first_light:��������������������a=3������ʱ &a ���ɣ����и���֮����Զ���*the_first_lightָ���ڴ��ֵ+1
* @param uint32_t GPIO_Pin_x[]���ﻹû���úã�Ӧ��������������ֱ�ӵ�����ã���ΪLEDһ����7��
* 
*/
void led_mode2_left(int *the_first_dark,uint32_t GPIO_Pin_x[]){
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//��ʼ��Ϊȫ��
   
    int led_number=*the_first_dark;//����һ�£���Ҫ��������
    
    (* the_first_dark)++;
    
 
    led_number %=8;
  
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//��ʼ��Ϊȫ��
   
     
}
/**
* @brief ��һ��������ҷ�������ƣ�����������Ĭ��ȫ��
* @param *the_first_light:��������������������a=3������ʱ &a ���ɣ����и���֮����Զ���*the_first_lightָ���ڴ��ֵ+1
* @param uint32_t GPIO_Pin_x[]���ﻹû���úã�Ӧ��������������ֱ�ӵ�����ã���ΪLEDһ����7��
* 
*/
void led_mode2_right(int *the_first_dark,uint32_t GPIO_Pin_x[]){
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//��ʼ��Ϊȫ��
    
    int led_number=-(*the_first_dark);//����һ�£���Ҫ��������
    
    (* the_first_dark)++;
    
    //led��GPIOE��pin8��15
    led_number %=8;  
    if(led_number==0){led_number --;}//led_number=16�������ᱻ��λ��ȫ��
    
    led_number+=8;
    
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//��ʼ��Ϊȫ��

}

