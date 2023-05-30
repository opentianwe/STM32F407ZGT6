#ifndef __DBG_H__
#define __DBG_H__
#include <stdio.h>
#include"common.h"
#include"DBG.h"
void printf_Init();

//串口1发送一个字符
void uart6SendChar(u8 ch);

int fputc(int ch, FILE *f);  //重定向，让printf输出到串口  

void uart6SendChars(u8 *str, u16 strlen);
#endif // DEBUG