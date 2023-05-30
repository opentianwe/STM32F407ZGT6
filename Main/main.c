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
			printf("i2c创建成功\n");
		}
		Start_i2c(i2chw);//起始信号
		Send_i2c_byte(i2chw,0xA0);//发送硬件地址
		if(wike_i2c_ack(i2chw)==0)
		{
			printf("24c02正常响应\n");
		}else{
			printf("24c02不正常响应\n");
		}	
		Send_i2c_byte(i2chw,0x00);//发送写入的地址
		if(wike_i2c_ack(i2chw)==0)
		{
			printf("24c02正常响应\n");
		}else{
			printf("24c02不正常响应\n");
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
