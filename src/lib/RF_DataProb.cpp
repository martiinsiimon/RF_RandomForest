/*
 * File:   RF_DataProb.cpp
 * Author: Martin Simon <martiinsiimon@gmail.com>
 */

#include <stdexcept>
#include <iostream>
#include <vector>
#include "RF_DataProb.h"
#include "RF_Utils.h"

using namespace std;

/**
 * Class constructor.
 */
RF_DataProb::RF_DataProb()
{
}

/**
 * Class destructor.
 */
RF_DataProb::~RF_DataProb()
{
}

/**
 * Increase posterior probability for key given in argument
 *
 * @param i Key of probability record to be incresed
 */
void RF_DataProb::increasePosteriori(uint i)
{
    if (this->probabilities.count(i) == 1)
        this->probabilities[i] = this->probabilities[i] + 1;
    else
        this->probabilities[i] = 1.0f;
}

/**
 * Return stored probability for given key
 *
 * @param i Key of probability record to return
 */
float RF_DataProb::getPosteriori(uint i)
{
    if (this->probabilities.count(i) == 1)
        return this->probabilities[i];
    else
        return 0.0;
}

/**
 * Normalize all the stored probabilities to sum to 1 (like 100 %).
 */
void RF_DataProb::normalize()
{
    float sum = 0.0f;

    /* Delete black - unlabeled */
    this->probabilities.erase(0);

    /* Count sum */
    map<uint, float>::iterator it;
    for (it = this->probabilities.begin(); it != this->probabilities.end(); it++)
    {
        sum += it->second;
    }

    /* Divide every element by sum */
    for (it = this->probabilities.begin(); it != this->probabilities.end(); it++)
    {
        this->probabilities[it->first] /= sum;
    }
}

/**
 * Dump probability values into one string to export purposes. Every pair (key, value) is stored in format 'key=value' (without apostrophs).
 *
 * @return String of all probabilities stored in object
 */
string RF_DataProb::dumpProbabilities()
{
    string result = "";

    /* Append every pair key-value */
    map<uint, float>::iterator it;
    for (it = this->probabilities.begin(); it != this->probabilities.end();)
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

/**
 * Import into probability map new pair.
 *
 * @param key Key of inserted pair
 * @param value Value of insterted pair
 */
void RF_DataProb::addValue(uint key, float value)
{
    this->probabilities[key] = value;
}

/**
 * Clear the map of probabilities.
 */
void RF_DataProb::clear()
{
    this->probabilities.clear();
}

/**
 * Add given probabilities to this one (per element).
 *
 * @param p Probabilities to add to this object (per element)
 */
void RF_DataProb::sum(RF_DataProb* p)
{
    /* Iterate over all items */
    map<uint, float>::iterator it;
    for (it = p->probabilities.begin(); it != p->probabilities.end(); it++)
    {
        if (this->probabilities.count(it->first) == 1)
            this->probabilities[it->first] += it->second;
        else
            this->probabilities[it->first] = it->second;
    }
}

/**
 * Get key of maximal probability (key with maximal value). It actually returns the first maximal value if there are more of them with the very same value.
 *
 * @return Key of element with maximal probability
 */
uint RF_DataProb::getMaximal()
{
    uint max = 0;
    float maxVal = 0.0f;
    map<uint, float>::iterator it;
    for (it = this->probabilities.begin(); it != this->probabilities.end(); it++)
    {
        if (it->second > maxVal)
        {
            max = it->first;
            maxVal = it->second;
        }
    }
    return max;
}

/**
 * Return a vector of keys stored here
 */
vector<uint> RF_DataProb::getKeys()
{
    vector<uint> res;
    map<uint, float>::iterator it;
    for (it = this->probabilities.begin(); it != this->probabilities.end(); it++)
    {
        res.push_back(it->first);
    }
    return res;
}