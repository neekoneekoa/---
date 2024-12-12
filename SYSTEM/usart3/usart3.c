/*
 * @Author: 译枢-章俊-zhangjun
 * @Date: 2024-10-02 22:38:28
 * @LastEditors: 
 * @LastEditTime: 2024-11-05 10:43:25
 * @Description: 请填写简介
 */
#include "usart3.h"	

/*****************辰哥单片机设计******************
											STM32
 * 项目			:	蓝牙模块通信实验                     
 * 版本			: V1.0
 * 日期			: 2024.10.2
 * MCU			:	STM32F103C8T6
 * 接口			:	串口3						
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 

**********************BEGIN***********************/

//串口1中断服务程序
	//初始化 IO 串口 3
	//pclk1:PCLK1 时钟频率(Mhz)
	//bound:波特率  
void USART3_Config()
{ 
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//GPIOB 时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //串口 3 时钟使 USART_DeInit(USART3); //复位串口 3
		
		//USART3_TX PB10
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10; //PB10
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
		GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化 PB10
		
		//USART3_RX PB11
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; //浮空输入
		GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化 PB11
	
		USART_InitStructure.USART_BaudRate= 9600; //波特率设
		USART_InitStructure.USART_WordLength=USART_WordLength_8b; //8 位数据格
		USART_InitStructure.USART_StopBits = USART_StopBits_1; //一个停止
		USART_InitStructure.USART_Parity = USART_Parity_No; //无奇偶校验
		USART_InitStructure.USART_HardwareFlowControl=
		USART_HardwareFlowControl_None;
		//无硬件数据流
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  //收发模式
	  USART_Init(USART3, &USART_InitStructure); //初始化串口 3
	  USART_Cmd(USART3, ENABLE);//使能串口
	  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//使能接收中断 
	  //设置中断优先级
	  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级 2
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority =0; //子优先级 3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道使能
	  NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化 NVIC 寄存器
}
extern u8 Flag_dakai,dakai;

void USART3_IRQHandler(void)
{ u8 Res; 
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收到数据
  { 
		Res =USART_ReceiveData(USART3);
		if(Res=='1')
		{
			dakai=1;
			Res='5';
		}			
		if(Res=='2')
		{
			dakai=0;
			Res='5';
		}						
  } 
} 

void USART3_SendString(char* str)
{
    while (*str)
    {
        USART_SendData(USART3, (uint8_t)(*str));
        while (USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET);
        str++;
    }
}

