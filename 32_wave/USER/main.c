#include "stm32f10x.h"
#include "sys.h"
#include "UltrasonicWave.h"
#include "delay.h"
#include "usart.h"	  
#include "motor.h"
#include "mbotLinuxUsart.h"//���ø�ͷ�ļ���ʹ�ã�ͨ��Э���ǰ��

/************************************************
 ALIENTEK ��ӢSTM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

//���Խ��ձ���
int testRece1     =0;
int testRece2     =0;
unsigned char testRece3 = 0x00;
//���Է��ͱ���
short testSend1   =5000;
short testSend2   =2000;
short testSend3   =1000;
unsigned char testSend4 = 0x05;


 void Delay(u32 count)
 {
   u32 i=0;
	 
   for(;i<count;i++);
 }
 int main(void)
 {	
		
		float distance;
		motor_init();
		UltrasonicWave_Init();//???
		delay_init();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ�����2

		uart_init(115200);
//		printf("Hello");
		Delay(6000000);
  while(1)
	{
		distance = 0;
		distance = UltrasonicWave_Measure(); //????
		delay_ms(600);//??????? 60ms??, ????????????????
//		printf("distance:%5.2f ",distance);//?????
		if(distance<20)
		{
			turn_back(180);
			testSend1 = 180;
			testSend2 = -180;
			usartSendData(testSend1,testSend2,distance,testSend3,testSend4);
		//�������ʱ
		delay_ms(13);
			Delay(120000);
			turn_right(200);
			testSend1 = 200;
			testSend2 = -180;
			usartSendData(testSend1,testSend2,distance,testSend3,testSend4);
		//�������ʱ
		delay_ms(13);
			Delay(120000);
//			turn_left();
//			Delay(120000);
		}
		else
			turn_front(200);
			testSend1 = 200;
			testSend2 = 200;
		
		//����Ҫ���͵�ROS�����ݣ��Ӹú���������ǰ�������ݷ�Χ��-32768 - +32767�������ĸ����ݵķ�Χ(0 - 255)
		usartSendData(testSend1,testSend2,distance,testSend3,testSend4);
		//�������ʱ
		delay_ms(13);
		
		
	
//		Delay(12000000);
//		IN1(0);
//		IN2(0);
//		IN3(0);
//		IN4(0);
//		Delay(100000);

//		IN1(0);
//		IN2(1);
//		IN3(1);
//		IN4(0);
//		Delay(6000000);
	}
 }
 
 void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
 	 {
		 USART_ClearITPendingBit(USART1,USART_IT_RXNE);//��������жϱ�־λ
		 //��ROS���յ������ݣ���ŵ���������������
		 usartReceiveOneData(&testRece1,&testRece2,&testRece3);
	 }
}
