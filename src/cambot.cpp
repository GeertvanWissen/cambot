#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "GPIOClass.h"
#include "Engine.h"

using namespace std;

int main (void)
{
    Engine eng;

    string inputstate;
    // create objects for I/O
    GPIOClass* sw_frontL = new GPIOClass("21");
    GPIOClass* sw_frontR = new GPIOClass("20");

    // export GPIOs to be able to read and write
    sw_frontL->export_gpio();
    sw_frontR->export_gpio();

    // set direction for GPIOs
    sw_frontL->setdir_gpio("in");
    sw_frontR->setdir_gpio("in");

    while(1)
    {
        // just some code to get a sense of writing in C
        
        sw_frontL->getval_gpio(inputstate); //read state of input example
        cout << "Front left switch state is " << inputstate  <<endl;
	
	if (inputstate == "1") {
		        eng.move(2);
			cout << "motor should be on" << endl;
	}else{
			eng::stop();

	}
	usleep(20000);

    }
    cout << "Exiting....." << endl;
    return 0;
}
