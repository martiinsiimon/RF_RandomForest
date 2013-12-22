/*
 * File:   RF_DataSampleCont.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:51
 */

#include "RF_DataSampleCont.h"
#include "RF_Utils.h"
#include <iostream>

using namespace std;

RF_DataSampleCont::RF_DataSampleCont()
{
    //this->_data = new vector<RF_DataSample*>();
}

RF_DataSampleCont::RF_DataSampleCont(const RF_DataSampleCont& orig)
{
}

RF_DataSampleCont::~RF_DataSampleCont()
{
    for (uint i = 0; i < this->_data.size(); i++)
    {
        delete this->_data.at(i);
    }
    this->_data.clear();
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
    for (int i = T_RGB; i != T_LAST; i++)
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