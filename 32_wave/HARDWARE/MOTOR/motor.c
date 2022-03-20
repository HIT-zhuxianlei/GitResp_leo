#include "motor.h"
void turn_front(u8 v)
{
		IN1(v);
		IN2(0);
		IN3(0);
		IN4(v);
	
}
void turn_left(u8 v)
{
		IN1(0);
		IN2(v);
		IN3(0);
		IN4(v);
	
}

void turn_right(u8 v)
{
		IN1(v);
		IN2(0);
		IN3(v-20);
		IN4(0);
	
}
void turn_back(u8 v)
{
		IN1(0);
		IN2(v);
		IN3(v);
		IN4(0);
	
}
void motor_init()
{
//	GPIO_InitTypeDef  GPIO_InitStructure;
//	 
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	    //ʹ��PA�˿�ʱ��
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;			    //IN 1234 
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //�������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz
// 
//  GPIO_Init(GPIOA, &GPIO_InitStructure);	  	       //��ʼ��GPIO
//	GPIO_ResetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
	/*-------=------����Ƚ�ͨ��1��2��3��4��GPIO��ʼ��-------------*/
	GPIO_InitTypeDef GPIO_InitStructure;														//����GPIO��ʼ���ṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;									//������ʱ��ʱ���ṹ��
	TIM_OCInitTypeDef TIM_OCInitStructure;	 												//������ʱ������ȽϽṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);						//ʹ����ӳ��IOʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;			//����GPIO�ܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;									//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//�������Ƶ��
	GPIO_Init(GPIOA, &GPIO_InitStructure);													//��ʼ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);													//TIM3 A67 B01
	
	/*----------------------ʱ���ṹ���ʼ��-----------------------*/
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;									//������ʱ��ʱ���ṹ��
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 					//ʹ����ӳ�䶨ʱ��ʱ��

	/* �������ڣ���������Ϊ0.0005s����ʾ��Tout= ((arr+1)*(psc+1))/Tclk */
	TIM_TimeBaseStructure.TIM_Period = 500-1;												//��ʱ������arr�����Զ���װ�ؼĴ�����ֵ																																	//�ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Prescaler = 71;	 											//��ʱ��Ԥ��Ƶ������psc��ʱ��Դ����Ԥ��Ƶ�����Ƕ�ʱ��ʱ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;					//ʱ�ӷ�Ƶ���ӣ��������������������ʱ����Ҫ�õ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;			//����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;								//�����ظ���������ֵΪ0���������ظ�����
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  								//��ʼ����ʱ��

	/*--------------------����ȽϽṹ���ʼ��---------------------*/
//	TIM_OCInitTypeDef TIM_OCInitStructure;	 												//������ʱ������ȽϽṹ��
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;  							//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  	//ʹ������Ƚ�
	TIM_OCInitStructure.TIM_Pulse = 0;   														//���ó�ʼռ�ձ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  			//�������:TIM����Ƚϼ��Ը�(�ߵ�ƽ��Ч)
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  											//��ʼ������Ƚ�ͨ��1
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  											//��ʼ������Ƚ�ͨ��2
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  											//��ʼ������Ƚ�ͨ��3
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  											//��ʼ������Ƚ�ͨ��4
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  							//ʹ��ͨ��1��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  							//ʹ��ͨ��2��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  							//ʹ��ͨ��3��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  							//ʹ��ͨ��4��CCR4�ϵ�Ԥװ�ؼĴ���
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);						//ʹ��AFIO����ʱ��
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);								//������ӳ��
	
	TIM_Cmd(TIM3, ENABLE);  
//	TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE �����ʹ��		//ʹ��TIM
	TIM_ARRPreloadConfig(TIM3, ENABLE); 														//ʹ��TIM1��ARR�ϵ�Ԥװ�ؼĴ���
//	TIM_CtrlPWMOutputs(TIM1, ENABLE);   														//�����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��������Ҫ�����ʹ��
  	  
}



