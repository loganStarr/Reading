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

    const double diameterRobot = 50;
    ev3dev::medium_motor* Left;
    ev3dev::medium_motor* Right;
    bool MoveToDegree(int degreeTarget)
    {
        return  (Left->position() > degreeTarget) || (Right->position() > degreeTarget);
    }
    bool TurnToDegree(int degreeTarget)
    {
        double Amount = Left->position() - Right->position();
        Amount /= diameterRobot;
        Amount *= (180/M_PI);
        return  (Amount > degreeTarget);
    }
    RobotDefition(ev3dev::medium_motor* Left, ev3dev::medium_motor* Right)
    {
        this->Left = Left;
        this->Right = Right;
    }


};
int main()
{
    ev3dev::medium_motor* Right =  new ev3dev::medium_motor(ev3dev::OUTPUT_B);
    ev3dev::medium_motor* Left = new ev3dev::medium_motor(ev3dev::OUTPUT_C);
    
    RobotDefition s{Left,Right};
    int amountCommands = 8;


    std::function<bool(int)> MoveToAngle = std::bind(&RobotDefition::MoveToDegree, &s, std::placeholders::_1);
    std::function<bool(int)> TurnToDegree = std::bind(&RobotDefition::TurnToDegree, &s, std::placeholders::_1);

    Command* Commands[8];

    Move* move = new Move(75, 75, MoveToAngle,100,Left,Right);
    Turn* turn = new Turn(30, -30, TurnToDegree, 90, Left, Right);

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