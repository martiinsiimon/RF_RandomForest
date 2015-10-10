/*
 * File:   RF_RandomForest.h
 * Author: Martin Simon <martiinsiimon@gmail.com>
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

    bool trainForest();
    void validateTree(RF_Tree* t);

    string dumpForest();

    void addTree(RF_Tree* t);

    void addAllowedChannel(int ch);
    void addAllowedChannel(int *ch, int n);
    vector<int> getAllowedChannels();
    void cleanAllowedChannels();

    RF_DataSample * solveSample(RF_DataSample* ds);
private:
    int _treesCount;
    int _maxDepth;
    int _n;
    vector<int> _allowed_channels;
    RF_DataSampleCont * _data;
    vector<RF_Tree *> _trees;
};

#endif	/* RF_RANDOMFOREST_H */

