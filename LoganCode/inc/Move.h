#pragma once
#include <functional>
#include "Command.h"
#include "ev3dev.h"

class Move : public Command
{
public:
	int powerLeft;
	int powerRight;
	ev3dev::medium_motor* Left;
	ev3dev::medium_motor* Right;
    Move()
    {

    }
	Move(int powerLeft, int powerRight, std::function<bool(int)> stopFunction, int stopCondition, ev3dev::medium_motor* Left, ev3dev::medium_motor* Right);
	virtual void setUp() override;
	virtual void run() override;
};

