//#include "stm32f10x.h"

// void My_USART1_Init(void)  
//{  
//    GPIO_InitTypeDef GPIO_InitStrue;  
//    USART_InitTypeDef USART_InitStrue;  
//    NVIC_InitTypeDef NVIC_InitStrue;  
//      
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//GPIO�˿�ʹ��  
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//���ڶ˿�ʹ��  
//      
//    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP; //���츴��������ֲ�Ҫ��
//    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;  
//    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;  
//    GPIO_Init(GPIOA,&GPIO_InitStrue);  
//      
//    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;//�������루�ֲ�Ҫ��
//    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;  
//    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;  
//    GPIO_Init(GPIOA,&GPIO_InitStrue);  
//      
//    USART_InitStrue.USART_BaudRate=115200;  //������                                                 /*Ҫ����һ̨�豸
//    USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //��ʹ��Ӳ������          ��������������
//    USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;  //���ͽ���ʹ��                            ��һ��
//    USART_InitStrue.USART_Parity=USART_Parity_No;  //��ʹ����żУ��
//    USART_InitStrue.USART_StopBits=USART_StopBits_1;  //ֹͣλΪ1
//    USART_InitStrue.USART_WordLength=USART_WordLength_8b; //�ֳ�8λ                                           */
//      
//    USART_Init(USART1,&USART_InitStrue);
//      
//    USART_Cmd(USART1,ENABLE);//ʹ�ܴ���1  
//      
//    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//���ջ������ǿտ����жϣ����������ݾʹ����жϣ�
//      
//    NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;  
//    NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;  //�����ж�ͨ��
//    NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;  //������ռ���ȼ�
//    NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;  
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�ж����ȼ����飬��λ��ռ����λ����Ӧ 
//    NVIC_Init(&NVIC_InitStrue);  
//      
//}  
//  
//void USART1_IRQHandler(void)  //����1�жϷ�����
//{  
//     char res;
//     if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  //�ж��жϱ�־λ
// {  
//     res= USART_ReceiveData(USART1); 	 //��ȡ����һ���ܵ�����
//     USART_SendData(USART1,res);         //�򴮿�һ��������
//  }  
//}  



#include "stm32f10x.h"
 
 void My_USART1_Init(void)  
{  
    GPIO_InitTypeDef GPIO_InitStrue;  
    USART_InitTypeDef USART_InitStrue;  
    NVIC_InitTypeDef NVIC_InitStrue;  
      
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//GPIO????  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//??????  
      
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;  
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;  
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;  
    GPIO_Init(GPIOA,&GPIO_InitStrue);  
      
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;  
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;  
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;  
    GPIO_Init(GPIOA,&GPIO_InitStrue);  
      
    USART_InitStrue.USART_BaudRate=115200;  
    USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
    USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;  
    USART_InitStrue.USART_Parity=USART_Parity_No;  
    USART_InitStrue.USART_StopBits=USART_StopBits_1;  
    USART_InitStrue.USART_WordLength=USART_WordLength_8b;  
      
    USART_Init(USART1,&USART_InitStrue);
      
    USART_Cmd(USART1,ENABLE); 
      
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
      
    NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;  
    NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;  
    NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;  
    NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    NVIC_Init(&NVIC_InitStrue);  
      
}  
  
//void USART1_IRQHandler(void)  
//{  
//    u8 res;  
//     if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  
// {  
//     res= USART_ReceiveData(USART1); 	 
//     USART_SendData(USART1,res);     
//  }  
//}  
//   
 
   