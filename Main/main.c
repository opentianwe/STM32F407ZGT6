#define _DEBUG_
#include "DBG.h"
#include "I2C.h"
#include <stdlib.h>
#include<string.h>


/*
 *	��������:write_eeprom_i2c
 *	��������:ʹ��i2cдEEPROM����
 *   �������: i2c ���ڴ洢i2c������ʹ�õ�GPIO�����Ϣ
 *   �������: hardaddr i2cӲ����ַ
 *   �������: writeaddr д�뵽EEPROM��Ӧ���ڴ��ַ
 *   �������: buff д�������
 *   �������: len д�����ݳ���
 */
void write_eeprom_i2c(I2Cstr i2c, uint8_t hardaddr, uint8_t writeaddr, uint8_t *buff, uint8_t len)
{
    I2CHANDLE i2chw = Creat_i2c(i2c);
    if (i2chw != NULL) {
        DbgPrint("i2c Creat success!!\n");
    } else {
        DbgPrint("i2c Creat fail!!\n");
        return;
    }

    Start_i2c(i2chw); // ��ʼ�ź�

    Send_i2c_byte(i2chw, hardaddr); // ����Ӳ��д���ַ
    if (wike_i2c_ack(i2chw) == 0) {
        DbgPrint("eeprom Link successful\n");
    } else {
		Stop_i2c(i2chw);
        DbgPrint("eeprom Link failed\n");
		DbgPrint("i2c Stop\n");
        return;
    }
    Send_i2c_byte(i2chw, writeaddr); // ����д��ĵ�ַ
    if (wike_i2c_ack(i2chw) == 0) {
        DbgPrint("eeprom Write address success\n");
    } else {
		Stop_i2c(i2chw);
        DbgPrint("eeprom Write address failed\n");
		DbgPrint("i2c Stop\n");
        return;
    }

    while (len) {
        uint8_t data = buff[len - 1];
        Send_i2c_byte(i2chw, data);

        if (wike_i2c_ack(i2chw) == 0) {
            DbgPrint("eeprom Write data success\n");
        } else {
			Stop_i2c(i2chw);
            DbgPrint("eeprom Write data failed\n");
			DbgPrint("i2c Stop\n");
            return;
        }
        len--;
    }

    Stop_i2c(i2chw);
	DbgPrint("i2c Stop\n");
    return;
}


/*
*	��������:write_24c02
*   ��������:д24c02����
*   �������: i2c ���ڴ洢i2c������ʹ�õ�GPIO�����Ϣ
 *   �������: hardaddr i2cӲ����ַ
 *  �������: writeaddr д�뵽EEPROM��Ӧ���ڴ��ַ  ע��д��shi
*/
void write_24c02(I2Cstr i2c, uint8_t hardaddr, uint8_t writeaddr, uint8_t *buff, uint8_t len)
{
    if (len > 8) {
        uint8_t p   = len % 8;
        uint8_t tmp = 0;
        uint8_t add = 0;
        uint8_t data = 0;
        if (p != 0) {
            tmp = (len - p) / 8;
            tmp += 1;
            for (; tmp > 0; tmp--) {
                if (add == 0) {
                    data = len - p;
                    write_eeprom_i2c(i2c, hardaddr, writeaddr + add, &buff[data], p);
                } else {
                    data = data - 8;
                    write_eeprom_i2c(i2c, hardaddr, writeaddr + add, &buff[data], 8);
                }
                add = add + 2;
            }
        } else {
            tmp = len / 8;
            for (; tmp > 0; tmp--) {
                data = data - 8;
                write_eeprom_i2c(i2c, hardaddr, writeaddr + add, &buff[data], 8);
                add = add + 2;
            }
        }

    } else {
        write_eeprom_i2c(i2c, hardaddr, writeaddr, buff,len);
    }
}
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_init();
    printf_Init();
	I2Cstr i2cstr;
	i2cstr.GPio_x     = GPIOB;
	i2cstr.GPiostatus = 1;
	i2cstr.RCc        = RCC_AHB1Periph_GPIOB;
	i2cstr.SCl        = GPIO_Pin_8;
	i2cstr.SDa        = GPIO_Pin_9;
    uint8_t data[55];
    memset(data, 0x88, sizeof(data));
    write_24c02(i2cstr, 0xA0, 0x00,data, sizeof(data));
    while (1) {
        delay_ms(1000);
    }
}
