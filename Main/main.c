#define _DEBUG_
#include "DBG.h"
#include "I2C.h"

void write_24c02(uint8_t address, uint8_t *buff, uint8_t len)
{
    I2Cstr i2cstr;
    i2cstr.GPio_x     = GPIOB;
    i2cstr.GPiostatus = 1;
    i2cstr.RCc        = RCC_AHB1Periph_GPIOB;
    i2cstr.SCl        = GPIO_Pin_8;
    i2cstr.SDa        = GPIO_Pin_9;
    I2CHANDLE i2chw   = Creat_i2c(i2cstr);
    if (i2chw != NULL) {
        DbgPrint("i2c Creat success!!\n");
    } else {
        DbgPrint("i2c Creat fail!!\n");
        return;
    }

    Start_i2c(i2chw); // 起始信号

    Send_i2c_byte(i2chw, 0xA0); // 发送硬件写入地址
    if (wike_i2c_ack(i2chw) == 0) {
        DbgPrint("AT24C02 Link successful\n");
    } else {
        DbgPrint("AT24C02 Link failed\n");
        return;
    }
    Send_i2c_byte(i2chw, address); // 发送写入的地址
    if (wike_i2c_ack(i2chw) == 0) {
        DbgPrint("AT24C02 Write address success\n");
    } else {
        DbgPrint("At24C02 Write address failed\n");
        return;
    }

    while (len) {
		uint8_t data = buff[len - 1];
        Send_i2c_byte(i2chw, data);
        if (wike_i2c_ack(i2chw) == 0) {
            DbgPrint("AT24C02 Write data success\n");
        } else {
            DbgPrint("At24C02 Write data failed\n");
            return;
        }
		len--;
    }

    Stop_i2c(i2chw);
    if (wike_i2c_ack(i2chw) == 0) {
        DbgPrint("i2c Stop success!!\n");
    } else {
        DbgPrint("i2c Stop fail!!\n");
        return;
    }
}

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_init();
    printf_Init();
	uint8_t data[5]={0x00,0x01,0x02,0x03,0x04};
    write_24c02(0x00, data, sizeof(data));
    while (1) {
        delay_ms(1000);
    }
}
