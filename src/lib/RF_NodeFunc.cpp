/*
 * File:   RF_NodeFunc.cpp
 * Author: Martin Simon <martiinsiimon@gmail.com>
 */

#include "RF_NodeFunc.h"

/**
 * Class constructor.
 */
RF_NodeFunc::RF_NodeFunc()
{
    this->type = 0;
    this->channel = 0;
    this->threshold = 0;
}

/**
 * Class destructor.
 */
RF_NodeFunc::~RF_NodeFunc()
{
}

/**
 * Get type of node function. See RF_FUNC enum for available functions.
 *
 * @return Function type. See RF_FUNC for more details
 */
int RF_NodeFunc::getType()
{
    return this->type;
}

/**
 * Set type of node function. See RF_FUNC enum for available functions.
 *
 * @param t Function type. See RF_FUNC for more details
 */
void RF_NodeFunc::setType(int t)
{
    this->type = t;
}

/**
 * Get channel of node function. See T_CHANNELS enum for available channels.
 *
 * @return Channel number. See T_CHANNELS for more details
 */
int RF_NodeFunc::getChannel()
{
    return this->channel;
}

/**
 * St channel of node function. See T_CHANNELS enum for available channels.
 *
 * @param ch Channel of node function. See T_CHANNELS for more details
 */
void RF_NodeFunc::setChannel(int ch)
{
    this->channel = ch;
}

/**
 * Get threshold of RF_FUNC_ABSTEST node function.
 *
 * @return Threshold of node function
 */
int RF_NodeFunc::getThreshold()
{
    return this->threshold;
}

/**
 * Set threshold of RF_FUNC_ABSTEST node function.
 *
 * @param t Threshold of node function
 */
void RF_NodeFunc::setThreshold(int t)
{
    this->threshold = t;
}