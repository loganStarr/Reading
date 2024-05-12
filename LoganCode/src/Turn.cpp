#include "Turn.h"

Turn::Turn(int powerLeft, int powerRight, std::function<bool(int)> stopFunction, int stopCondition, ev3dev::medium_motor* Left, ev3dev::medium_motor* Right)
{
	this->powerLeft = powerLeft;
	this->powerRight = powerRight;
	this->stopCondition = stopCondition;
	this->stopFunction = stopFunction;
	this->Left = Left;
	this->Right = Right;
}
void Turn::setUp() 
{
	Left->set_position(0);
	Right->set_position(0);
}

void Turn::run() 
{
	Right->set_duty_cycle_sp(powerRight);
	Right->run_direct();
	Left->set_duty_cycle_sp(powerLeft);
	Left->run_direct();
}