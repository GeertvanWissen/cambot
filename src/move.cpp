#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "GPIOClass.h"

using namespace std;

bool Move::init()
{

  GPIOClass* motor1A = new GPIOClass("23");
  GPIOClass* motor1B = new GPIOClass("24");
  GPIOClass* motor1E = new GPIOClass("25");

  GPIOClass* motor2A = new GPIOClass("10");
  GPIOClass* motor2B = new GPIOClass("9");
  GPIOClass* motor2E = new GPIOClass("11");

  motor1A->export_gpio();
  motor1B->export_gpio();
  motor1E->export_gpio();

  motor2A->export_gpio();
  motor2B->export_gpio();
  motor2E->export_gpio();

  motor1A->setdir_gpio("out");
  motor1B->setdir_gpio("out");
  motor1E->setdir_gpio("out");

  motor2A->setdir_gpio("out");
  motor2B->setdir_gpio("out");
  motor2E->setdir_gpio("out");

  return true;
}

bool Move::direction(int dir)
{
  // first set the direction for both motors
  if (dir<=3) {
    motor1A->setval_gpio("0");
    motor1B->setval_gpio("1");
    motor2A->setval_gpio("1");
    motor2B->setval_gpio("0");
  }
  if (dir>=7) {
    motor1A->setval_gpio("1");
    motor1B->setval_gpio("0");
    motor2A->setval_gpio("0");
    motor2B->setval_gpio("1");
  }
  if (dir==4) {
    motor1A->setval_gpio("0");
    motor1B->setval_gpio("1");
    motor2A->setval_gpio("0");
    motor2B->setval_gpio("1");
  }
  if (dir==6) {
    motor1A->setval_gpio("1");
    motor1B->setval_gpio("0");
    motor2A->setval_gpio("1");
    motor2B->setval_gpio("0");
  }

  // than enable the right motors
  if (dir==1 || dir==2 || dir==4 || dir==6 || dir==7 || dir==8) {
    motor1E->setval_gpio("1");
  }else{
    motor1E->setval_gpio("0");
  }
  if (dir==3 || dir==2 || dir==4 || dir==6 || dir==9 || dir==8) {
    motor2E->setval_gpio("1");
  }else{
    motor2E->setval_gpio("0");
  }

  return true;
}
bool Move::stop(int dir)
{
  motor1E->setval_gpio("0");
  motor2E->setval_gpio("0");
  return true;
}
