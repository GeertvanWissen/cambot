#include "GPIOClass.h"

class Engine {
private:
  int status;
  GPIOClass* motor1A;
  GPIOClass* motor1B;
  GPIOClass* motor1E;
  GPIOClass* motor2A;
  GPIOClass* motor2B;
  GPIOClass* motor2E;
  
public:
  Engine();
  bool move(int dir);
  bool stop();
  int getStatus;
};
