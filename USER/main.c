//#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "key.h"
#include "sys.h"	 
#include "mlx90614.h" 
#include "oled.h"
//#include "HC05.h"
#include "CountSensor.h"
#include "string.h"

#include "stm32f10x.h"                // Device header
//#include "Delay.h"
//#include "OLED.h"
#include "usart.h"
#include "max30102.h"
#include "algorithm.h"
#include "xiic.h"
#include "blood.h"
#include "usart3.h"

uint16_t ADValue;			//定义AD值变量
float Voltage;				//定义电压变量

u8 dakai;
u8 Flag_dakai;

uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);					//软件触发AD转换一次
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);	//等待EOC标志位，即等待AD转换结束
	return ADC_GetConversionValue(ADC1);					//读数据寄存器，得到AD转换的结果
}

void AD_init(void)
{
	
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//开启ADC1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
	
	/*设置ADC时钟*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);						//选择时钟6分频，ADCCLK = 72MHz / 6 = 12MHz
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA0引脚初始化为模拟输入
	
	/*规则组通道配置*/
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);		//规则组序列1的位置，配置为通道0
	
	/*ADC初始化*/
	ADC_InitTypeDef ADC_InitStructure;						//定义结构体变量
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//模式，选择独立模式，即单独使用ADC1
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//数据对齐，选择右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//外部触发，使用软件触发，不需要外部触发
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		//连续转换，失能，每转换一次规则组序列后停止
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			//扫描模式，失能，只转换规则组的序列1这一个位置
	ADC_InitStructure.ADC_NbrOfChannel = 1;					//通道数，为1，仅在扫描模式下，才需要指定大于1的数，在非扫描模式下，只能是1
	ADC_Init(ADC1, &ADC_InitStructure);						//将结构体变量交给ADC_Init，配置ADC1
	
	/*ADC使能*/
	ADC_Cmd(ADC1, ENABLE);									//使能ADC1，ADC开始运行
	
	/*ADC校准*/
	ADC_ResetCalibration(ADC1);								//固定流程，内部有电路会自动执行校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
}
	

int main(void)
{	
	int i=0;
	char A[]="Tem : ";
	uint8_t KeyNumber2,BaoJing;
    float KeyNumber1=0;
    float Temperature = 0;    //�¶����ݱ����������ͣ�
    char TempValue[80] = {0};
    char BuChang[80] = {0};	//����ֵ
	uart_init(115200);
	USART3_Config();
	delay_init();	  //��ʱ������ʼ��
	Key_Init();//������ʼ��	
	OLED_Init()	;
	OLED_Clear() ;
	CountSensor_Init();
	SMBus_Init();
	AD_init();
	display();
	Buzzer(); 

	IIC_GPIO_INIT();		
	MAX30102_GPIO();
	Max30102_reset();
  MAX30102_Config();
	
	char buffer[50]; 
	uint8_t spo2 = 97; // 血氧值 
	float temp = 36.5; // 温度值 
	uint8_t battery = 100; // 电量百分比 
	uint8_t alarm = 1; // 报警提醒
	
	for(i = 0;i < 128;i++) 
	{
		while(MAX30102_INTPin_Read()==0)
		{
			//读取FIFO
			max30102_read_fifo();
		}
	}
	printf("Neeko");
	OLED_ShowString(40,2,"----",16);//����4������ʾ�¶�
	//My_USART1_Init();
	while(1)
	{			
		printf("123");
		//+++++++++++++++++++++ 血氧 ++++++++++++++++++++++++
		blood_Loop();				//获取血氧和心率
		//+++++++++++++++++++++ 温度 ++++++++++++++++++++++++++++++++
		if(
				1 //GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0
		)
		{
			delay_ms(200);
			Temperature = SMBus_ReadTemp()+KeyNumber1;
			sprintf(TempValue,"%.1f", Temperature); //������ת�����ַ���			
			OLED_ShowString(40,2,(uint8_t *)TempValue,16);//����OLED����ʾʵ�ʲ������¶�

			 if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1)
			{
				for(char a=0;a<6;a++)
				{
					USART_SendData(USART1, A[a]);
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
				}
				int i = 0;
				for(;i < strlen(TempValue);++i){
					USART_SendData(USART1, *(uint8_t*)(TempValue+i));
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);				
				}
			}	
		
		}
//		KeyNumber1=Key_Num1()*0.1;
//		sprintf(BuChang,"%.1f", KeyNumber1);
//		OLED_ShowString(40,4,(uint8_t *)BuChang,16);
		//++++++++++++++++++++ 电量 +++++++++++++++++++++++++
		ADValue = AD_GetValue();					//获取AD转换的值
		Voltage = (float)ADValue / 4095 * 3.3 * 2;		//将AD值线性变换到0~3.3的范围，表示电压
		printf("Voltage = %f",Voltage);
		OLED_ShowNumber(60, 0, Voltage,1,16);				//显示电压值的整数部分
		OLED_ShowNumber(70, 0, (uint16_t)(Voltage * 100) % 100, 2,16);	//显示电压值的小数部分
		
		//++++++++++++++++++++ KEY +++++++++++++++++++++++++
		KeyNumber2=Key_Num2();
		OLED_ShowNumber(40,6,KeyNumber2,2,16);
		if(Temperature>KeyNumber2)
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			Warning();			
		}
		else
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			Safe();
		}		 
		//+++++++++++++++++++ 语音 ++++++++++++++++++++++
		//+++++++++++++++++++ 蓝牙 +++++++++++++++++++++++
		
		// 发送血氧值 
		sprintf(buffer, "SPO2:%d\n", spo2); 
		USART3_SendString(buffer); 
		
		// 发送温度值 
		sprintf(buffer, "TEMP:%.1f\n", temp); 
		USART3_SendString(buffer); 
		
		// 发送电量 
		sprintf(buffer, "BAT:%d%%\n", battery); 
		USART3_SendString(buffer); 
		
		// 发送报警提醒 
		sprintf(buffer, "ALARM:%d\n", alarm); 
		USART3_SendString(buffer);
		
		if(dakai==1&&Flag_dakai==0)
		{
			//LED_On();
			Flag_dakai=1;
			printf("1 \n");
			OLED_ShowNumber(80, 4, 1,1,16);				//显示电压值的整数部分
		}
		if(dakai==0&&Flag_dakai==1)
		{
			//LED_Off();
			Flag_dakai=0;
			printf("0 \n");
			OLED_ShowNumber(80, 4, 0,1,16);				//显示电压值的整数部分
		}
	}
			
	
}

