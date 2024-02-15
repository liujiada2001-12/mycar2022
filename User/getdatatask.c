#include "getdatatask.h"
#include "gpio.h"
float getdatatimes=0;
int data1=0;//PI2
int data2=0;//PI7
int data3=0;//PI6
int data4=0;//PI5
int temp1,temp2,temp3,temp4,tempgx,tempgy,tempgz,tempax,tempay,tempaz,tempmx,tempmy,tempmz;
static int count=0;
static int line_count=0;

void getdatatask(void)
{
  
  readdata();
  dealdata();
  deallinedata();
  getdatatimes++;
}

void readdata()
{
  data1=HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_2);
  data2=HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_7);
  data3=HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_6);
  data4=HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_5);
}

extern int light[4];
extern int light_last[4];
extern int light_now[4];
void dealdata()//滤波
{
  
  if(count==0)//巡线数据
  {
  temp1=data1;
  temp2=data2;
  temp3=data3;

  }
  else
  {
  temp1+=data1;
  temp2+=data2;
  temp3+=data3;
 
  }
  count++;
  if(count==4)
  {
    light[0]=temp1/4;
    light[1]=temp2/4;
    light[2]=temp3/4;

    count=0;
  }
  if(line_count==0)temp4=data4;//数线数据
  else temp4+=data4;
  line_count++;
   if(line_count==100)
  {
    light[3]=temp4/100;
    line_count=0;
  }
}

int line_num=0;//过线数
extern int go_flag;
void deallinedata()//数线
{
    light_last[3]=light_now[3];
    light_now[3]=light[3];
    if(light_now[3]==0&&light_last[3]==1)
    {
      if(go_flag==1) line_num++;
      if(go_flag==0) line_num--;
    }
}