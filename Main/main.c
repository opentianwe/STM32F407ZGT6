#include "led.h"

/*******************���������ͨ��λ������ʵ��IO�ڿ���***************************/
//int main(void)
//{ 
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
//	delay_init();		  //��ʼ����ʱ����
//	LED_Init();		    //��ʼ��LED�˿�
//	
//  while(1)
//	{
//    LED0=0;     //LED0��
//    LED1=1;     //LED1��
//    LED2=1;     //LED2��
//		
//    delay_ms(500);
//		LED0=1;     //LED0��
//    LED1=0;     //LED1��
//    LED2=1;     //LED2��
//		 
//		delay_ms(500);
//		LED0=1;     //LED0��
//    LED1=1;     //LED1��
//    LED2=0;     //LED2��
//    delay_ms(500);
//	}
//}
/*********************************************************************************/

/*******************���������ͨ��λ�β���ʵ��IO�ڿ���***************************/
	
int main(void)
{ 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
	delay_init();		  //��ʼ����ʱ����
	LED_Init();		    //��ʼ��LED�˿�
	
  while(1)
	{
    GPIO_bits_OUT(GPIOE,3,2,0x0002);
	  delay_ms(500);
	  GPIO_bits_OUT(GPIOE,3,2,0x0001);
		delay_ms(500);
		GPIO_bits_OUT(GPIOE,3,2,0x0003);  //�ر�LED0 LED1
	  GPIO_bits_OUT(GPIOG,9,1,0x0000);
		delay_ms(500);
		GPIO_bits_OUT(GPIOG,9,1,0x0001);  //�ر�LED2 
	}
}
/***********************************************************************************/


/*******************���������ͨ���⺯��ֱ�Ӳ���ʵ��IO�ڿ���************************/

//int main(void)
//{ 
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
//	delay_init();		  //��ʼ����ʱ����
//	LED_Init();		    //��ʼ��LED�˿�
//	
//	
//	while(1)
//	{
//	GPIO_ResetBits(GPIOE,GPIO_Pin_3);   //��  ��ͬLED0=0;
//	GPIO_SetBits(GPIOE,GPIO_Pin_4);     //��  ��ͬLED1=1;
//	GPIO_SetBits(GPIOG,GPIO_Pin_9);     //��  ��ͬLED2=1;
//	delay_ms(500);  		                //��ʱ500ms
//	GPIO_SetBits(GPIOE,GPIO_Pin_3);     //��  ��ͬLED0=1;
//	GPIO_ResetBits(GPIOE,GPIO_Pin_4);   //��  ��ͬLED1=0;
//	GPIO_SetBits(GPIOG,GPIO_Pin_9);     //��  ��ͬLED2=1;
//	delay_ms(500);                      //��ʱ500ms
//	GPIO_SetBits(GPIOE,GPIO_Pin_3);     //��  ��ͬLED0=1;
//	GPIO_SetBits(GPIOE,GPIO_Pin_4);     //��  ��ͬLED1=1;
//	GPIO_ResetBits(GPIOG,GPIO_Pin_9);   //��  ��ͬLED2=0;
//	delay_ms(500);
//	}
//}





