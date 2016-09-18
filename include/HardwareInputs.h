#ifndef HARDWAREINPUTS_H
#define HARDWAREINPUTS_H

#include "GPIOClass.h"

class HardwareInputs {
private:
  GPIOClass* sw_backL;
  GPIOClass* sw_backR;
  GPIOClass* sw_frontL;
  GPIOClass* sw_frontR;
  GPIOClass* eye_L;
  GPIOClass* eye_R;
  
public:
  HardwareInputs();
  bool changeFlag;
  int readAll();
};

#endif
