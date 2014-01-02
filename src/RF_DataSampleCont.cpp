/*
 * File:   RF_DataSampleCont.cpp
 * Author: Martin Simon <martiinsiimon@gmail.com>
 */

#include "RF_DataSampleCont.h"
#include "RF_Utils.h"
#include <iostream>

using namespace std;

/**
 * Class constructor.
 */
RF_DataSampleCont::RF_DataSampleCont()
{
}

/**
 * Class destructor.
 */
RF_DataSampleCont::~RF_DataSampleCont()
{
    for (uint i = 0; i < this->_data.size(); i++)
    {
        delete this->_data.at(i);
    }
    this->_data.clear();
}

int RF_DataSampleCont::samplesCount()
{
    return this->_data.size();
}

RF_DataSample* RF_DataSampleCont::getSample(int id)
{
    return this->_data.at(id);
}

vector<RF_DataSample*>* RF_DataSampleCont::getSamples()
{
    return &(this->_data);
}

/**
 * Add given data sample into internal vector.
 * @param s RF_DataSample to add into vector
 */
void RF_DataSampleCont::addSample(RF_DataSample* s)
{
    if (s == NULL)
    {
        return;
    }
    this->_data.push_back(s);
}

void RF_DataSampleCont::generateAllChannels()
{
    for (int i = T_CHANNEL_RGB; i != T_CHANNEL_LAST; i++)
    {
        this->generateChannel(i);
    }
}

void RF_DataSampleCont::generateChannel(int id)
{
    for (uint i = 0; i< this->_data.size(); i++)
    {
        this->_data.at(i)->generateChannel(id);
    }
}