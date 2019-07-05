#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"

/*把八个流水灯给捆起来，方便操作*/
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
    // stm32复位后，JTAG与SW默认同时开启的，即所有的JTAG端口均被系统保留，软件设置GPIO是不起作用的
   // AFIO->MAPR |= 0x02000000;//关闭JTAG-DP，启用SW-DP。在前面要启动 LED与SEG时钟、SEL时钟、AFIO时钟，不关闭的话它会占用一些引脚让软件无法设置它
    AFIO_Init();
    LED_SEG_GPIO_Config(  );
    SEL_GPIO_Config(  );
    LED_SEG_Select_CMD(Select_LED);
  //LED_SEG_Select_CMD(Select_SEG);
    KEY_GPIO_Config();
  /*  寄存器编程版本。效果和上面语句相同
    RCC->APB2ENR|=1<<4;     //使能PORTC时钟
    GPIOC->CRL&=0XFFFFF000;//PC0-2设置成输入	  
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
* @brief 仅一个灯亮的左方向跑马灯
* @param *the_first_light:可以是任意变量，如变量a=3，输入时 &a 即可，运行个灯之后会自动将*the_first_light指针内存的值+1
* @param uint32_t GPIO_Pin_x[]这里还没配置好，应该做到主函数能直接调用最好，因为LED一共就7个
* 
*/
void led_mode1_left(int *the_first_light,uint32_t GPIO_Pin_x[]){
    //初始化一下跑马灯为全灭 
    GPIO_ResetBits(GPIOE,GPIO_Pin_All);
    
    
    int led_number=*the_first_light;//备份一下，主要操作备份
    (* the_first_light)++;

    led_number %=8;

    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
     
}
/**
* @brief 仅一个灯亮的right右方向跑马灯
* @param *the_first_light:可以是任意变量，如变量a=3，输入时 &a 即可，运行个灯之后会自动将*the_first_light指针内存的值+1
* @param uint32_t GPIO_Pin_x[]这里还没配置好，应该做到主函数能直接调用最好，因为LED一共就7个
* 
*/
void led_mode1_right(int *the_first_light,uint32_t GPIO_Pin_x[]){
     //初始化一下跑马灯为全灭
      GPIO_ResetBits(GPIOE,GPIO_Pin_All);
    
    int led_number=-(*the_first_light);//备份一下，主要操作备份
    (* the_first_light)++;
    
    //led是GPIOE的pin8到15
    led_number %=8;
    if(led_number==0){led_number --;}//led_number=0呃话，会被置位成全亮，这里复制粘贴的时候搞反了，懒得改代码，干脆改参数
    
    led_number  +=  8;
    GPIO_SetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    
     
}


/**
* @brief 仅一个灯灭的左方向跑马灯，函数结束后默认全亮
* @param *the_first_light:可以是任意变量，如变量a=3，输入时 &a 即可，运行个灯之后会自动将*the_first_light指针内存的值+1
* @param uint32_t GPIO_Pin_x[]这里还没配置好，应该做到主函数能直接调用最好，因为LED一共就7个
* 
*/
void led_mode2_left(int *the_first_dark,uint32_t GPIO_Pin_x[]){
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//初始化为全亮
   
    int led_number=*the_first_dark;//备份一下，主要操作备份
    
    (* the_first_dark)++;
    
 
    led_number %=8;
  
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//初始化为全亮
   
     
}
/**
* @brief 仅一个灯灭的右方向跑马灯，函数结束后默认全亮
* @param *the_first_light:可以是任意变量，如变量a=3，输入时 &a 即可，运行个灯之后会自动将*the_first_light指针内存的值+1
* @param uint32_t GPIO_Pin_x[]这里还没配置好，应该做到主函数能直接调用最好，因为LED一共就7个
* 
*/
void led_mode2_right(int *the_first_dark,uint32_t GPIO_Pin_x[]){
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//初始化为全亮
    
    int led_number=-(*the_first_dark);//备份一下，主要操作备份
    
    (* the_first_dark)++;
    
    //led是GPIOE的pin8到15
    led_number %=8;  
    if(led_number==0){led_number --;}//led_number=16呃话，会被置位成全灭
    
    led_number+=8;
    
    GPIO_ResetBits(GPIOE,GPIO_Pin_x[(led_number)]);
    delay();
    GPIO_SetBits(GPIOE,GPIO_Pin_All);//初始化为全亮

}

