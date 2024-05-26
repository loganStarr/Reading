#define _USE_MATH_DEFINES

#include "ev3dev.h"

#include <iostream>
#include<cmath>
#include <functional>
#include "Turn.h"
#include "Command.h"
#include "Move.h"
#include <chrono>
#include <thread>
#include <fstream> 

class RobotDefition
{
public:

    const double diameterRobot = 254.43;
    ev3dev::medium_motor* Left;
    ev3dev::medium_motor* Right;
    ev3dev::color_sensor* LeftColor;
    bool MoveToDegree(int degreeTarget)
    {
        return  (Left->position() > degreeTarget) || (-Right->position() > degreeTarget);
    }
    bool TurnToDegree(int degreeTarget)
    {
        double Amount = Left->position() - Right->position();
        Amount /= diameterRobot;
        Amount *= (180/M_PI);
        std::cout << Amount << std::endl;

        return  (Amount > degreeTarget);
    }
    bool MoveToColor(int brightness)
    {
        return  (brightness == LeftColor->reflected_light_intensity());
    }
    RobotDefition(ev3dev::medium_motor* Left, ev3dev::medium_motor* Right,ev3dev::color_sensor* LeftColor)
    {
        this->Left = Left;
        this->Right = Right;
        this->LeftColor = LeftColor;
    }


};
int main()
{
   
    ev3dev::medium_motor* Right =  new ev3dev::medium_motor(ev3dev::OUTPUT_B);
    ev3dev::medium_motor* Left = new ev3dev::medium_motor(ev3dev::OUTPUT_C);
    ev3dev::color_sensor* LeftColor = new ev3dev::color_sensor(ev3dev::INPUT_1);
    Right->set_polarity(ev3dev::medium_motor::polarity_inversed);
    Left->set_polarity(ev3dev::medium_motor::polarity_normal);
    RobotDefition s{Left,Right,LeftColor};
    int amountCommands = 1;


    std::function<bool(int)> MoveToAngle = std::bind(&RobotDefition::MoveToDegree, &s, std::placeholders::_1);
    std::function<bool(int)> TurnToDegree = std::bind(&RobotDefition::TurnToDegree, &s, std::placeholders::_1);
    std::function<bool(int)> MoveToColor = std::bind(&RobotDefition::MoveToColor, &s, std::placeholders::_1);
    std::shared_ptr<Command> Commands[8];

    std::shared_ptr<Move> move(new Move(75, 75, MoveToColor,9,Left,Right));
    std::shared_ptr<Turn> turn(new Turn(50, -50, TurnToDegree, 90, Left, Right));

    Commands[0] = move;
    Commands[1] = turn;
    Commands[2] = move;
    Commands[3] = turn;
    Commands[4] = move;
    Commands[5] = turn;
    Commands[6] = move;
    Commands[7] = turn;

    int index = 0;
    Commands[index]->setUp();
    while (index < amountCommands)
    {

        if (Commands[index]->stopFunction(Commands[index]->stopCondition))
        {


            index++;
            if (index == amountCommands) break;
            Commands[index]->setUp();
         
        }
        else
        {
            Commands[index]->run();
        }
    
    }

    return 0;
}