#include"DBG.h"
#include"I2C.h"

void write24c02()
{
		I2Cstr i2cstr;
		i2cstr.GPio_x = GPIOB;
		i2cstr.GPiostatus = 1;
		i2cstr.RCc = RCC_AHB1Periph_GPIOB;
		i2cstr.SCl = GPIO_Pin_8;
		i2cstr.SDa = GPIO_Pin_9;
		I2CHANDLE i2chw = Creat_i2c(i2cstr);
		if(i2chw!=NULL)
		{
			printf("i2c�����ɹ�\n");
		}
		Start_i2c(i2chw);//��ʼ�ź�
		Send_i2c_byte(i2chw,0xA0);//����Ӳ����ַ
		if(wike_i2c_ack(i2chw)==0)
		{
			printf("24c02������Ӧ\n");
		}else{
			printf("24c02��������Ӧ\n");
		}	
		Send_i2c_byte(i2chw,0x00);//����д��ĵ�ַ
		if(wike_i2c_ack(i2chw)==0)
		{
			printf("24c02������Ӧ\n");
		}else{
			printf("24c02��������Ӧ\n");
		}	
}

int main(void)
{ 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();		
	printf_Init();
	write24c02();
  while(1)
	{
		delay_ms(1000);
		
	}
}
