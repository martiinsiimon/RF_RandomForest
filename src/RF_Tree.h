/*
 * File:   RF_Tree.h
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:38
 */

#ifndef RF_TREE_H
#define	RF_TREE_H

#include <vector>
#include <opencv2/core/core.hpp>
#include "RF_DataSampleCont.h"
#include "RF_NodeFunc.h"
#include "RF_DataProb.h"

using namespace std;
using namespace cv;

class RF_Tree {
public:
    RF_Tree();
    virtual ~RF_Tree();

    void train();

    void setDataset(RF_DataSampleCont* d);
    void setChannels(vector<int> c);

    string dumpTree();
    void setId(int id);
    int getId();
    void setMaximalDepth(int i);
    int getMaximalDepth();

    bool isLeaf();

    void generatePosteriori();

    RF_DataProb* solveTree(RF_DataSample *ds);

    void clearDataset();

private:
    int _treeId;

    bool leaf;
    RF_NodeFunc * func;
    RF_Tree* tLeft;
    RF_Tree* tRight;

    RF_DataProb* probabilities;

    int maximalDepth;
    RF_DataSampleCont * _dataset;
    vector<int> _channels;
};

#endif	/* RF_TREE_H */

