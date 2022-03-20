#ifndef __MOTOR__
#define __MOTOR__



#define High    1
#define Low     0
 
#define IN1(speed)	TIM_SetCompare1(TIM3,speed);

#define IN2(speed)	TIM_SetCompare2(TIM3,speed);

#define IN3(speed)	TIM_SetCompare3(TIM3,speed);

#define IN4(speed)	TIM_SetCompare4(TIM3,speed);
 




#include "sys.h"  

#define IN1GPIO_SetBits(GPIOA,GPIO_Pin_5)
void motor_init(void);
void turn_front(u8 v);
void turn_left(u8 v);
void turn_right(u8 v);
void turn_back(u8 v);


#endif
