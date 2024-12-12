
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
uint8_t number = 0;
uint8_t KeyNum1 = 0;
uint8_t KeyNum2 = 35;
uint8_t KeyNum3 = 37;
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_Mod(void)//����1��ģʽѡ��
{
	
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
	{
		Delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			TIM_Cmd(TIM2,ENABLE);
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 1)
			{
				TIM_Cmd(TIM2,DISABLE);
				if(number<80)
				{
					number=0 ;
					return 0 ; //ģʽ0������ʱ��С��100���룩
				}
				else
				{
					number=0;
					return 1; //ģʽ1������100���룩
				}
			}
			
		}
	else
	{
		return 0;
	}
		
}
void Mod(void)


}
	

uint8_t Key_GetNum2(void)//�¶ȷ�Χ����������ֵ����2����1����4�ٰ�2����1����ʼΪ35
{
	
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0);
		Delay_ms(20);
		KeyNum2 = KeyNum2 + 1;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0 && GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0 )
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0);
		Delay_ms(20);
		KeyNum2 = KeyNum2 - 1;	
	}
	
	return KeyNum2;
}
uint8_t Key_GetNum3(void)//�¶ȷ�Χ����������ֵ����3��1����4ͬʱ��3��1����ʼֵΪ38
{
	
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 0);
		Delay_ms(20);
		KeyNum3 = KeyNum3 + 1;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 0 && GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0 )
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0);
		Delay_ms(20);
		KeyNum3 = KeyNum3 - 1;	
	}	
	return KeyNum3;
}
uint8_t Key_GetNum4(void)//�������ĺż�����ʾ�¶�
{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0)
	{
		uint8_t KeyNum4 = 0;
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0);
		Delay_ms(20);
		KeyNum4 = KeyNum4 - 1;
	}
	return KeyNum4;
}
