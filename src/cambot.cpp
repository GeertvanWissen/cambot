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
    GPIOClass* motor1A = new GPIOClass("16");
    GPIOClass* motor1B = new GPIOClass("18");
    GPIOClass* motor1E = new GPIOClass("22");
    
    GPIOClass* sw_frontL = new GPIOClass("40");
    GPIOClass* sw_frontR = new GPIOClass("38");

    // export GPIOs to be able to read and write
    motor1A->export_gpio();
    motor1A->export_gpio();
    motor1A->export_gpio();
    
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

    while(1)
    {
        // just some code to get a sense of writing in C
        
        sw_frontL->getval_gpio(inputstate); //read state of input example
        cout << "Current input pin state is " << inputstate  <<endl;
        if(inputstate == "0") // if input pin is at state "0" i.e. button pressed
        {
            cout << "input pin state is Pressed. Will check input pin state again in 20ms "<<endl;
                usleep(20000);
                    cout << "Checking again ....." << endl;
                    sw_frontL->getval_gpio(inputstate); // checking again to ensure that state "0" is due to button press and not noise
            if(inputstate == "0")
            {
                cout << "input pin state is definitely Pressed. Turning LED ON" <<endl;
                motor1E->setval_gpio("1"); // turn motor ON

                cout << " Waiting until pin is unpressed....." << endl;
                while (inputstate == "0"){
                sw_frontL->getval_gpio(inputstate);
                };
                cout << "pin is unpressed" << endl;

            }
            else
                cout << "input pin state is definitely UnPressed. That was just noise." <<endl;

        }
        motor1E->setval_gpio("0");

    }
    cout << "Exiting....." << endl;
    return 0;
}
