#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "GPIOClass.h"

using namespace std;

int main (void)
{

    string inputstate;
    
    // create objects for I/O
    GPIOClass* motor1A = new GPIOClass("23");
    GPIOClass* motor1B = new GPIOClass("24");
    GPIOClass* motor1E = new GPIOClass("25");
    
    GPIOClass* sw_frontL = new GPIOClass("21");
    GPIOClass* sw_frontR = new GPIOClass("20");

    // export GPIOs to be able to read and write
    motor1A->export_gpio();
    motor1B->export_gpio();
    motor1E->export_gpio();
    
    sw_frontL->export_gpio();
    sw_frontR->export_gpio();

    cout << " GPIO pins exported" << endl;

    // set direction for GPIOs
    motor1A->setdir_gpio("out");
    motor1B->setdir_gpio("out");
    motor1E->setdir_gpio("out");

    sw_frontL->setdir_gpio("in");
    sw_frontR->setdir_gpio("in");

    cout << " Set GPIO pin directions" << endl;

    motor1A->setval_gpio("1");
    motor1B->setval_gpio("0");

    cout << "motor 1 set" << endl;

    while(1)
    {
        // just some code to get a sense of writing in C
        
        sw_frontL->getval_gpio(inputstate); //read state of input example
        cout << "Front left switch state is " << inputstate  <<endl;
	
	if (inputstate == "1") {
		        motor1E->setval_gpio("1");
			cout << "motor should be on" << endl;
	}else{
			motor1E->setval_gpio("0");

	}
	usleep(20000);

    }
    cout << "Exiting....." << endl;
    return 0;
}
