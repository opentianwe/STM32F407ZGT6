#ifndef __I2C_H__
#define __I2C_H__
#include "common.h"

typedef struct {
    uint32_t RCc; //硬件时钟位置
    GPIO_TypeDef* GPio_x;
    uint32_t SCl;//SCL位置
    uint32_t SDa;//SDA位置
    uint8_t GPiostatus;//初始化iic GPIO后 scl和sda的初始状态 根据时序图设置
} I2Cstr,*PI2Cstr;

typedef PI2Cstr I2CHANDLE;



I2CHANDLE Creat_i2c(I2Cstr i2cstr);//初始化IIC相关的GPIO口

uint16_t Get_SDA(I2CHANDLE i2c);
void Start_i2c(I2CHANDLE i2c);//I2C发送总线开始信号

void Stop_i2c(I2CHANDLE i2c);//I2C发送总线停止信号

uint8_t wike_i2c_ack(I2CHANDLE i2c);//等待ack应答信号

void Send_i2c_byte(I2CHANDLE i2c,uint8_t data);//发送一个字节的I2C总线数据

#endif // !__I2C_H#