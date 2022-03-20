#include "stm32f10x.h"
#include "sys.h"
#include "UltrasonicWave.h"
#include "delay.h"
#include "usart.h"	  
#include "motor.h"
#include "mbotLinuxUsart.h"//引用该头文件是使用，通信协议的前提

/************************************************
 ALIENTEK 精英STM32F103开发板实验0
 工程模板
 注意，这是手册中的新建工程章节使用的main文件 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

//测试接收变量
int testRece1     =0;
int testRece2     =0;
unsigned char testRece3 = 0x00;
//测试发送变量
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
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组2

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
		//必须的延时
		delay_ms(13);
			Delay(120000);
			turn_right(200);
			testSend1 = 200;
			testSend2 = -180;
			usartSendData(testSend1,testSend2,distance,testSend3,testSend4);
		//必须的延时
		delay_ms(13);
			Delay(120000);
//			turn_left();
//			Delay(120000);
		}
		else
			turn_front(200);
			testSend1 = 200;
			testSend2 = 200;
		
		//将需要发送到ROS的数据，从该函数发出，前三个数据范围（-32768 - +32767），第四个数据的范围(0 - 255)
		usartSendData(testSend1,testSend2,distance,testSend3,testSend4);
		//必须的延时
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
		 USART_ClearITPendingBit(USART1,USART_IT_RXNE);//首先清除中断标志位
		 //从ROS接收到的数据，存放到下面三个变量中
		 usartReceiveOneData(&testRece1,&testRece2,&testRece3);
	 }
}
