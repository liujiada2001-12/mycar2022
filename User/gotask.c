#include "gotask.h"
#include "pid.h"	//pid control
#include "motor.h"	//motor control
float gotimes=0;
int16_t set_speed1=0;//正为后退，负为前进，左1右2
int16_t set_speed2=0;
PidTypeDef motor_pid;
motor_measure_t* motor_data1; //PID_motor param
motor_measure_t* motor_data2; //PID_motor param
/* motor control */
motor_measure_t* get_chassis_motor_measure_point(uint8_t i);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
void CAN_cmd_chassis(int16_t M1, int16_t M2, int16_t M3, int16_t M4);
extern int data1,data2,data3,data4;
int go_flag=0;
extern int line_num;
int speed_base=1800;
void gotask(void)
{
	motor(0,0);
//  if (line_num>=8) 
//  {
//    stop();
//    go_flag=0;
//  }
//    else
//    {
//       go();
//    go_flag=1;
//    }
  gotimes++;
}
void motor(int speed1,int speed2)
{
  set_speed1=(speed1+speed_base);
  set_speed2=-(speed2+speed_base);
  motor_data1 = get_chassis_motor_measure_point(0);
  PID_Calc1(&CM1_speed_pid,motor_data1->speed_rpm,set_speed1  ,Positional);
  motor_data2 = get_chassis_motor_measure_point(1);
  PID_Calc1(&CM2_speed_pid,motor_data2->speed_rpm,set_speed2  ,Positional);
	CAN_cmd_chassis(CM1_speed_pid.output,CM2_speed_pid.output,0,0);
}
int light[4]={0};
int light_last[4]={0};
int light_now[4]={0};
int judge;
void go()
{
  light_last[0]=light_now[0];
  light_last[1]=light_now[1];
  light_last[2]=light_now[2];
  light_now[0]=light[0];
  light_now[1]=light[1];
  light_now[2]=light[2];
  	if(light_now[0]==0&&light_now[1]==1&&light_now[2]==0)//未脱线
    {
      motor(0,0);
    }
    else if(light_now[0]==0&&light_now[1]==0&&light_now[2]==0)//全脱线
	{
		if(light_last[0]==1) left();//左转
		else if(light_last[2]==1) right();//右转
	}
    else if(light_now[0]==1&&light_now[1]==0&&light_now[2]==0)//偏右半脱
	{
		motor(-200,0);//左转
  }
  else if(light_now[0]==0&&light_now[1]==0&&light_now[2]==1)//偏左半脱
	{
    motor(0,-200);//右转
	}
	else if(light_now[1]==1&&light_now[0]==1&&light_now[2]==0) motor(-50,0);//左转
	else if(light_now[1]==1&&light_now[2]==1&&light_now[0]==0) motor(0,-50);//右转
		else if(light_now[1]==1&&light_now[2]==1&&light_now[0]==1) motor(0,0);//直
  
}


void left()
{
  set_speed1=-500;
  set_speed2=-500;
  motor_data1 = get_chassis_motor_measure_point(0);
  PID_Calc1(&CM1_speed_pid,motor_data1->speed_rpm,set_speed1  ,Positional);
  motor_data2 = get_chassis_motor_measure_point(1);
  PID_Calc1(&CM2_speed_pid,motor_data2->speed_rpm,set_speed2  ,Positional);
	CAN_cmd_chassis(CM1_speed_pid.output,CM2_speed_pid.output,0,0);
}

void right()
{
  set_speed1=500;
  set_speed2=500;
  motor_data1 = get_chassis_motor_measure_point(0);
  PID_Calc1(&CM1_speed_pid,motor_data1->speed_rpm,set_speed1  ,Positional);
  motor_data2 = get_chassis_motor_measure_point(1);
  PID_Calc1(&CM2_speed_pid,motor_data2->speed_rpm,set_speed2  ,Positional);
	CAN_cmd_chassis(CM1_speed_pid.output,CM2_speed_pid.output,0,0);
}
void stop()
{
  set_speed1=0;
  set_speed2=0;
  motor_data1 = get_chassis_motor_measure_point(0);
  PID_Calc1(&CM1_speed_pid,motor_data1->speed_rpm,set_speed1  ,Positional);
  motor_data2 = get_chassis_motor_measure_point(1);
  PID_Calc1(&CM2_speed_pid,motor_data2->speed_rpm,set_speed2  ,Positional);
	CAN_cmd_chassis(CM1_speed_pid.output,CM2_speed_pid.output,0,0);
}
