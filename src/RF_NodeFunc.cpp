/*
 * File:   RF_NodeFunc.cpp
 * Author: martin
 *
 * Created on 23. prosinec 2013, 11:30
 */

#include "RF_NodeFunc.h"

RF_NodeFunc::RF_NodeFunc()
{
}

RF_NodeFunc::RF_NodeFunc(const RF_NodeFunc& orig)
{
}

RF_NodeFunc::~RF_NodeFunc()
{
}

int RF_NodeFunc::getType()
{
    return this->type;
}

void RF_NodeFunc::setType(int t)
{
    this->type = t;
}

int RF_NodeFunc::getChannel()
{
    return this->channel;
}

void RF_NodeFunc::setChannel(int ch)
{
    this->channel = ch;
}

int RF_NodeFunc::getThreshold()
{
    return this->threshold;
}

void RF_NodeFunc::setThreshold(int t)
{
    this->threshold = t;
}