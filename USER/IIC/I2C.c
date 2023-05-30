#include "I2C.h"
#include "DBG.h"
#include <stdlib.h>
GPIO_InitTypeDef GPIO_InitStr;
/*********************************************************************************
**********************************************************************************
* 文件名称: I2C.c                                                                *
* 文件简述：I2C总线操作                                                            *
* 创建日期：2023.05.29                                                           *
* 版    本：V1.0                                                                 *
* 作    者：Tian                                                               *
* 说    明：封装I2C通讯协议                                                   *
**********************************************************************************
*********************************************************************************/

void Set_SCL(I2CHANDLE i2c,uint8_t status)
{
    if(status == 1) {
        GPIO_SetBits(i2c->GPio_x, i2c->SCl);
    }else{
        GPIO_ResetBits(i2c->GPio_x, i2c->SCl);
    }
}

void Set_SDA(I2CHANDLE i2c,uint8_t status)
{
    if(status == 1) {
        GPIO_SetBits(i2c->GPio_x, i2c->SDa);
    }else{
        GPIO_ResetBits(i2c->GPio_x, i2c->SDa);
    }
}


/*
*   函数名称:SDa_Pin_mode
*   函数功能:配置SDA引脚输入输出模式   mode = 1 为输入 mode = 0 为输出
*/
void SDa_Pin_mode(I2CHANDLE i2ch,uint8_t mode)
{
    if(mode == 1)
    {
        GPIO_InitStr.GPIO_OType = GPIO_OType_PP;//推��输出
        GPIO_InitStr.GPIO_Pin = i2ch->SDa;
        GPIO_InitStr.GPIO_Mode = GPIO_Mode_OUT;//引脚配置为输出模式
        GPIO_Init(i2ch->GPio_x, &GPIO_InitStr);//初始化GPIO口
    }else{
        GPIO_InitStr.GPIO_Pin = i2ch->SDa;
        GPIO_InitStr.GPIO_Mode = GPIO_Mode_IN;//引脚配置为输入模式
        GPIO_Init(i2ch->GPio_x, &GPIO_InitStr);//初始化GPIO口
    }
        
}
uint16_t Get_SDA(I2CHANDLE i2c)
{
    SDa_Pin_mode(i2c,1);//配置SDA为输入模式
    uint8_t ret = GPIO_ReadInputDataBit(i2c->GPio_x, i2c->SDa);
    SDa_Pin_mode(i2c,0);//配置SDA为输出模式
    return ret;
}

        
/*
 * 函数名称:I2C_Init
 * 函数功能:初始化IIC相关的GPIO口
 */
void GPIO_i2c_init(I2CHANDLE i2ch)
{
        // 使能硬件时钟
        RCC_AHB1PeriphClockCmd(i2ch->RCc, ENABLE);
        GPIO_InitStr.GPIO_Pin = i2ch->SCl | i2ch->SDa;
        GPIO_InitStr.GPIO_Mode = GPIO_Mode_OUT;//引脚配置为输出模式
        GPIO_InitStr.GPIO_OType = GPIO_OType_PP;//推挽输出
        GPIO_InitStr.GPIO_Speed = GPIO_High_Speed;//高速输出
        GPIO_InitStr.GPIO_PuPd = GPIO_PuPd_NOPULL;//不使能上下拉电阻
        GPIO_Init(i2ch->GPio_x, &GPIO_InitStr);//初始化GPIO口
        if(i2ch->GPiostatus == 0) {
            GPIO_ResetBits(i2ch->GPio_x, i2ch->SCl | i2ch->SDa);
        }else {
            GPIO_SetBits(i2ch->GPio_x, i2ch->SCl | i2ch->SDa);
        }
}

/*
 * 函数名称:Creat_i2c
 * 函数功能:初始化I2C相关接口 返回i2c句柄
 */
I2CHANDLE Creat_i2c(I2Cstr i2cstr){
    
    if(i2cstr.GPio_x !=0 && i2cstr.RCc!= 0&& i2cstr.SCl !=0 && i2cstr.SDa!=0){
        I2CHANDLE i2cstr_handle = (I2CHANDLE)malloc(sizeof(I2Cstr)+1);
        i2cstr_handle->GPio_x = i2cstr.GPio_x;
        i2cstr_handle->RCc = i2cstr.RCc;
        i2cstr_handle->SCl = i2cstr.SCl;
        i2cstr_handle->SDa = i2cstr.SDa;
        i2cstr_handle->GPiostatus = i2cstr.GPiostatus;
        GPIO_i2c_init(i2cstr_handle);
        return i2cstr_handle;
    }else{
        return NULL;
    }
}

/*
 * 函数名称:Start_i2c
 * 函数功能:I2C发送总线开始信号
 */
void Start_i2c(I2CHANDLE i2c){
    Set_SCL(i2c, 1);
    Set_SDA(i2c, 1);
    delay_us(5);

    Set_SDA(i2c,0);
    delay_us(5);
    Set_SCL(i2c,0);//钳住I2C总线，告诉当前总线是非空闲状态
}


/*
*   函数名称:Send_i2c_byte
*   函数功能:发送一个字节的I2C总线数据
*/
void Send_i2c_byte(I2CHANDLE i2c,uint8_t data){
    int32_t i;
    Set_SDA(i2c, 0);
    Set_SCL(i2c, 0);
    delay_us(5);
    for (i = 7; i >= 0; i--)
    {
        if(data&(1<<i))
        {
            Set_SDA(i2c, 1);
        }
        else{
            Set_SDA(i2c, 0);
        }
         printf("%d",Get_SDA(i2c));
        delay_us(5);
       
        Set_SCL(i2c, 1);
        delay_us(5);

        Set_SCL(i2c, 0);
        delay_us(5);
    }
    

}

/*
*   函数名称:wike_i2c_ack
*   函数功能:等待ack应答信号
*/
uint8_t wike_i2c_ack(I2CHANDLE i2c)
{
    Set_SCL(i2c, 1);
    delay_us(5);
    uint8_t ack = Get_SDA(i2c); //1无应答信号 0有应答信号
    Set_SCL(i2c, 0); //设置总线为非空闲状态
    delay_us(5);
    return ack;
}



/*
 * 函数名称:Stop_i2c
 * 函数功能:I2C发送总线停止信号
 */
void Stop_i2c(I2CHANDLE i2c)
{
    SDa_Pin_mode(i2c,0);
    Set_SCL(i2c, 1);
    Set_SDA(i2c, 0);
    delay_us(5);
    Set_SDA(i2c, 1);
    delay_us(5);
}


