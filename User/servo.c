#include "servo.h"
#include "tim.h"

int catchit_cnt=700;//�պ�700��1800
int throwit_cnt=1800;
int raiseup_cnt=750;//���750�����1390
int raisedown_cnt=1390;
void servo_init()
{
  HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);
}

void catchit(void) 
{
__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,catchit_cnt);
}
void throwit(void) 
{
__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,throwit_cnt);
}
void raiseup(void) 
{
__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,raiseup_cnt);
}
void raisedown(void) 
{
__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,raisedown_cnt);
}