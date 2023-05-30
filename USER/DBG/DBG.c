#include"DBG.h"
void printf_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef  USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/*  打开端口时钟  */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//使能USART6时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOC,&GPIO_InitStructure);


    //配置端口引脚复用
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);//复用为USART6
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);//复用为USART6

  


	/*  USART串口初始化  */
	//波特率设置为9600	
	USART_InitStructure.USART_BaudRate=9600;   
	//数据长8位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	//1位停止位	
	USART_InitStructure.USART_StopBits=USART_StopBits_1;		
	//无效验	
	USART_InitStructure.USART_Parity=USART_Parity_No;				
	//失能硬件流
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; 
	//开启发送和接受模式
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	 
	USART_Init(USART6,&USART_InitStructure);	
	
	/* 使能USART6 */
	USART_Cmd(USART6, ENABLE);		   
	//使能或者失能指定的USART中断 接收中断
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
	//清除USARTx的待处理标志位	
	USART_ClearFlag(USART6,USART_FLAG_TC);

    //中断优先级配置
     NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//串口6中断通道
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//抢占优先级
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//子优先级
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能IRQ    
     NVIC_Init(&NVIC_InitStructure);
}


//串口6发送一个字符
void uart6SendChar(u8 ch)
{      
	while((USART6->SR&0x40)==0);  
    USART6->DR = (u8) ch;      
}

/****************************************************************************
* 名    称: int fputc(int ch, FILE *f)
* 功    能：重定向，让printf输出到串口  
* 入口参数：
* 返回参数：
* 说    明：因printf()之类的函数，使用了半主机模式。使用标准库会导致程序无法
            运行,以下是解决方法:使用微库,因为使用微库的话,不会使用半主机模式. 
            请在工程属性的“Target“-》”Code Generation“中勾选”Use MicroLIB“这
            样以后就可以使用printf，sprintf函数了  
****************************************************************************/
int fputc(int ch, FILE *f)   //重定向，让printf输出到串口  
{
    uart6SendChar(ch);
    while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
    return ch;
}

/****************************************************************************
* 名    称: void uart1SendChars(u8 *str, u16 strlen)
* 功    能：串口1发送一字符串
* 入口参数：*str：发送的字符串
            strlen：字符串长度
* 返回参数：无
* 说    明： 
****************************************************************************/
void uart6SendChars(u8 *str, u16 strlen)
{ 
	  u16 k= 0 ; 
   do { uart6SendChar(*(str + k)); k++; }   //循环发送,直到发送完毕   
    while (k < strlen); 
} 


void USART6_IRQHandler()
{
    return;
}