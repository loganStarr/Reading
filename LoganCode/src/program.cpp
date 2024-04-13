#include "ev3dev.h"
#include <iostream>


#include <chrono>
#include <thread>
#include <fstream> 

int main()
{
    std::ifstream inputFile("input.txt"); 
    while(true)
    {
        char Tick;
        Tick << inputFile;
        char 
    }
    ev3dev::medium_motor motor(ev3dev::OUTPUT_B);
    motor.set_duty_cycle_sp(100);
    motor.run_direct();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    motor.reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    int degrees = motor.position();
    std::cout << degrees;
    motor.set_duty_cycle_sp(0);

}