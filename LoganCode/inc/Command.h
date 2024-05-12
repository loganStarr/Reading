#pragma once
#include <functional>
 class Command
{
public:
    virtual void setUp() = 0;
    virtual void run() = 0;
    std::function<bool(int)> stopFunction;
    int stopCondition;


};

