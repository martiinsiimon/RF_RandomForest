/*
 * File:   RF_RandomForest.cpp
 * Author: martin
 *
 * Created on 29. říjen 2013, 16:59
 */

#include "RF_RandomForest.h"


RF_RandomForest::RF_RandomForest()
{
}

RF_RandomForest::RF_RandomForest(const RF_RandomForest& orig)
{
}

RF_RandomForest::~RF_RandomForest()
{
}

void RF_RandomForest::trainForest()
{
    /*
     * generate this->treesCount of trees in this->_trees
     *
     * for every tree in this->_tree
     * generate random dataset (N number of random rectangles in every original sample)
     * generate random set of channels
     * call tree->trainTree()
     */
}

void RF_RandomForest::setTreesCount(int n)
{
    cout << "DBG: RF_RandomForest::setTreesCount(" << n << ")" << endl;
}

void RF_RandomForest::setMaxDepth(int n)
{
    cout << "DBG: RF_RandomForest::setMaxDepth(" << n << ")" << endl;
}

void RF_RandomForest::setData(RF_DataSampleCont * data)
{
    cout << "DBG: RF_RandomForest::setData(RF_DataSampleCont *)" << endl;
}