/*
 * File:   RF_DataProb.cpp
 * Author: Martin Simon <martiinsiimon@gmail.com>
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

RF_DataProb::~RF_DataProb()
{
}

void RF_DataProb::increasePosteriori(uint i)
{
    try
    {
        this->probabilities.at(i) = this->probabilities.at(i) + 1;
    }
    catch (out_of_range)
    {
        this->probabilities.insert(pair<uint, float>(i, 1.0f));
    }
}

void RF_DataProb::normalize()
{
    float sum = 0.0f;

    /* Delete black - unlabeled */
    this->probabilities.erase(0);

    for (map<uint, float>::iterator it = this->probabilities.begin(); it != this->probabilities.end(); it++)
    {
        sum += it->second;
    }

    for (map<uint, float>::iterator it = this->probabilities.begin(); it != this->probabilities.end(); it++)
    {
        this->probabilities.at(it->first) /= sum;
    }
}

string RF_DataProb::dumpProbabilities()
{
    string result = "";

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

    return result;
}

void RF_DataProb::addValues(uint key, float val)
{
    this->probabilities.insert(pair<uint, float>(key, val));
}

void RF_DataProb::clear()
{
    this->probabilities.clear();
}

void RF_DataProb::sum(RF_DataProb* p)
{
    for (map<uint, float>::iterator it = p->probabilities.begin(); it != p->probabilities.end(); it++)
    {
        try
        {
            this->probabilities.at(it->first) += it->second;
        }
        catch (out_of_range)
        {
            this->probabilities.insert(pair<uint, float>(it->first, it->second));
        }
    }
}

void RF_DataProb::product(RF_DataProb* p)
{
    for (map<uint, float>::iterator it = p->probabilities.begin(); it != p->probabilities.end(); it++)
    {
        try
        {
            this->probabilities.at(it->first) *= it->second;
        }
        catch (out_of_range)
        {
            this->probabilities.insert(pair<uint, float>(it->first, it->second));
        }
    }
}

uint RF_DataProb::getMaximal()
{
    uint max = 0;
    float maxVal = 0.0f;
    for (map<uint, float>::iterator it = this->probabilities.begin(); it != this->probabilities.end(); it++)
    {
        if (it->second > maxVal)
        {
            max = it->first;
            maxVal = it->second;
        }
    }
    return max;
}