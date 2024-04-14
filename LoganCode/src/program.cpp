#include "ev3dev.h"
#include <iostream>


#include <chrono>
#include <thread>
#include <fstream> 

int main()
{
    //std::ifstream fileBuffer("input file path");
    char input[1024];
    //if (fileBuffer.is_open())
    //{
        //fileBuffer.seekg(0, ios::beg);
        //fileBuffer.getline(input, 1024);
    //}
    int index = 0;
    float D = 254.43;
    input[0] = 'T';
    input[1] = 244;
    input[2] = 00;
    ev3dev::medium_motor Right(ev3dev::OUTPUT_B);
    ev3dev::medium_motor Left(ev3dev::OUTPUT_C);
    Right.set_polarity(ev3dev::medium_motor::polarity_inversed);
    Left.set_polarity(ev3dev::medium_motor::polarity_normal);


    while (index < 1)
    {
        if (input[index] == 'T')
        {
            short Degree = input[index+1];
            while (Left.position() < Degree && Right.position() < Degree)
            {
                int Diff = Left.position()-Right.position();
                float curr = Diff / D;
                
                Right.set_duty_cycle_sp(60);
                Right.run_direct();
                Left.set_duty_cycle_sp(60);
                Left.run_direct();
            }
            index+=2;
            Left.set_position(0);
            Right.set_position(0);
        }
        if (input[index] == 'M')
        {
            short Degree = input[index+1];
            while (Left.position() < Degree && Right.position() < Degree)
            {
                Right.set_duty_cycle_sp(60);
                Right.run_direct();
                Left.set_duty_cycle_sp(60);
                Left.run_direct();
            }
            index+=2;
            Left.set_position(0);
            Right.set_position(0);
        }
        
    }
    Right.set_duty_cycle_sp(0);
    Right.run_direct();
    Left.set_duty_cycle_sp(0);
    Left.run_direct();

}