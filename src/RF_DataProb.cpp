/*
 * File:   RF_DataProb.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:39
 */

#include <stdexcept>
#include <iostream>
#include "RF_DataProb.h"

using namespace std;

RF_DataProb::RF_DataProb()
{
}

RF_DataProb::RF_DataProb(const RF_DataProb& orig)
{
}

RF_DataProb::~RF_DataProb()
{
}

void RF_DataProb::increasePosteriori(uchar i)
{
    try
    {
        this->probabilities.at(i) = this->probabilities.at(i) + 1;
        //cout << "key " << (int) i << " exists: value " << this->probabilities.at(i) << endl;

    }
    catch (out_of_range)
    {
        this->probabilities.insert(pair<uchar, float>(i, 1.0f));
        //cout << "out of range key " << (int) i << endl;
    }
}