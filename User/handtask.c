#include "handtask.h"
#include "servo.h"
float handtimes=0;


void handtask(void)
{
  catchit();
  raiseup();
  handtimes++;
}