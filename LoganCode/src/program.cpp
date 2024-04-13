#include "ev3dev.h"
#include <iostream>


#include <chrono>
#include <thread>
#include <fstream> 

int main()
{
    std::ifstream fileBuffer("input file path", ios::in | ios::binary);
    char input[1024];
    if (fileBuffer.is_open())
    {
        fileBuffer.seekg(0, ios::beg);
        fileBuffer.getline(input, 1024);
    }
    int index = 0;
    while (true)
    {
        if (input[index] == 'T')
        {
            short Degree = 0;
            while (motor.position() < Degree)
            {
                motor.set_duty_cycle_sp(40);

            }
        }
        if (input[index] == 'M')
        {
            short Degree = 0;
            while(motor.position() < Degree)
            {
                motor.set_duty_cycle_sp(40);

            }
        }
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