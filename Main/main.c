#include "led.h"

/*******************下面代码是通过位带操作实现IO口控制***************************/
//int main(void)
//{ 
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
//	delay_init();		  //初始化延时函数
//	LED_Init();		    //初始化LED端口
//	
//  while(1)
//	{
//    LED0=0;     //LED0亮
//    LED1=1;     //LED1灭
//    LED2=1;     //LED2灭
//		
//    delay_ms(500);
//		LED0=1;     //LED0灭
//    LED1=0;     //LED1亮
//    LED2=1;     //LED2灭
//		 
//		delay_ms(500);
//		LED0=1;     //LED0灭
//    LED1=1;     //LED1灭
//    LED2=0;     //LED2亮
//    delay_ms(500);
//	}
//}
/*********************************************************************************/

/*******************下面代码是通过位段操作实现IO口控制***************************/
	
int main(void)
{ 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
	delay_init();		  //初始化延时函数
	LED_Init();		    //初始化LED端口
	
  while(1)
	{
    GPIO_bits_OUT(GPIOE,3,2,0x0002);
	  delay_ms(500);
	  GPIO_bits_OUT(GPIOE,3,2,0x0001);
		delay_ms(500);
		GPIO_bits_OUT(GPIOE,3,2,0x0003);  //关闭LED0 LED1
	  GPIO_bits_OUT(GPIOG,9,1,0x0000);
		delay_ms(500);
		GPIO_bits_OUT(GPIOG,9,1,0x0001);  //关闭LED2 
	}
}
/***********************************************************************************/


/*******************下面代码是通过库函数直接操作实现IO口控制************************/

//int main(void)
//{ 
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
//	delay_init();		  //初始化延时函数
//	LED_Init();		    //初始化LED端口
//	
//	
//	while(1)
//	{
//	GPIO_ResetBits(GPIOE,GPIO_Pin_3);   //亮  等同LED0=0;
//	GPIO_SetBits(GPIOE,GPIO_Pin_4);     //灭  等同LED1=1;
//	GPIO_SetBits(GPIOG,GPIO_Pin_9);     //灭  等同LED2=1;
//	delay_ms(500);  		                //延时500ms
//	GPIO_SetBits(GPIOE,GPIO_Pin_3);     //灭  等同LED0=1;
//	GPIO_ResetBits(GPIOE,GPIO_Pin_4);   //亮  等同LED1=0;
//	GPIO_SetBits(GPIOG,GPIO_Pin_9);     //灭  等同LED2=1;
//	delay_ms(500);                      //延时500ms
//	GPIO_SetBits(GPIOE,GPIO_Pin_3);     //灭  等同LED0=1;
//	GPIO_SetBits(GPIOE,GPIO_Pin_4);     //灭  等同LED1=1;
//	GPIO_ResetBits(GPIOG,GPIO_Pin_9);   //亮  等同LED2=0;
//	delay_ms(500);
//	}
//}





