#include "delay.h"
#include "UltrasonicWave.h"
void UltrasonicWave_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//??GPIOB??
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //??TIM2??	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	 // ??trig??
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_ResetBits(GPIOB,GPIO_Pin_11);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	 // ??echo??
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 	//????
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  
 	

	TIM_TimeBaseStructure.TIM_Period = 65535; 
	TIM_TimeBaseStructure.TIM_Prescaler = 71; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //	
}
/***** ????? *****/
void UltrasonicWave_StartMeasure(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_11);   //??PB1??
	delay_us(40);            //??20us
	GPIO_ResetBits(GPIOB, GPIO_Pin_11); //??PB1??
}
/***** ?? *****/
float UltrasonicWave_Measure(void)   //
{
	float record = 0;
  while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==1);//echo?????,???????,??????
	UltrasonicWave_StartMeasure(); //?????			
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == 0);//??echo??????	
	TIM_SetCounter(TIM2,0); //?????
	TIM_Cmd(TIM2, ENABLE);  //?????2,????
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == 1);//??echo??????
	record = TIM_GetCounter(TIM2);
  TIM_Cmd(TIM2, DISABLE);	//?????2,????	
	return (record)/1000000*340/2 *100;	//???????cm
}





