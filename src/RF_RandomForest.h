/*
 * File:   RF_RandomForest.h
 * Author: Martin Simon
 *
 * Created on 29. říjen 2013, 16:59
 */

#ifndef RF_RANDOMFOREST_H
#define	RF_RANDOMFOREST_H

#include <vector>
#include "RF_DataSampleCont.h"
#include "RF_Tree.h"
#include <iostream>

using namespace std;


class RF_RandomForest {
    /* Methods */
public:

    RF_RandomForest();
    virtual ~RF_RandomForest();

    void setTreesCount(int n);
    void setMaxDepth(int n);
    void setData(RF_DataSampleCont * data);
    void setN(int n);

    void trainForest();

private:
    int _treesCount;
    int _maxDepth;
    int _n;
    RF_DataSampleCont * _data;
    vector<RF_Tree *> _trees;
};

#endif	/* RF_RANDOMFOREST_H */

