/*
 * File:   RF_DataProb.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:39
 */

#include <stdexcept>
#include <iostream>
#include <string>
#include "RF_DataProb.h"
#include "RF_Utils.h"

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

void RF_DataProb::increasePosteriori(uint i)
{
    try
    {
        this->probabilities.at(i) = this->probabilities.at(i) + 1;
        //cout << "key " << (int) i << " exists: value " << this->probabilities.at(i) << endl;

    }
    catch (out_of_range)
    {
        this->probabilities.insert(pair<uint, float>(i, 1.0f));
        //cout << "out of range key " << (int) i << endl;
    }
}

void RF_DataProb::normalize()
{
    float sum = 0.0f;

    /* Delet black - unlabeled */
    this->probabilities.erase(0);

    for (map<uint, float>::iterator it = this->probabilities.begin(); it != this->probabilities.end(); it++)
    {
        sum += it->second;
    }

    for (map<uint, float>::iterator it = this->probabilities.begin(); it != this->probabilities.end(); it++)
    {
        //sum += it->second;
        this->probabilities.at(it->first) /= sum;
    }
}

string RF_DataProb::dumpProbabilities()
{
    string result = "(";

    for (map<uint, float>::iterator it = this->probabilities.begin(); it != this->probabilities.end();)
    {
        result += Number2String(it->first);
        result += "=";
        result += Number2String(it->second);

        if (++it != this->probabilities.end())
        {
            result += ",";
        }
    }
    result += ") ";

    return result;
}