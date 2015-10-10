/*
 * File:   RF_Train.h
 * Author: Martin Simon <martiinsiimon@gmail.com>
 */

#ifndef RF_TRAIN_H
#define	RF_TRAIN_H

#include <iostream>
#include "RF_DataSampleCont.h"
#include "RF_RandomForest.h"


using namespace std;

class RF_Train {
public:
    RF_Train();
    RF_Train(string dataFile, string modelFile);
    virtual ~RF_Train();
    void setDataFile(string f);
    void setModelFile(string f);

    void prepareTraining();
    void trainForest();

    void exportModel();

    void printResults();
    string getResults();
    bool trained;
private:

    /* Forest configuration */
    int _maxDepth;
    int _maxTrees;
    int _n;
    int _allowedChannels[7] = {T_CHANNEL_GRAY, T_CHANNEL_R, T_CHANNEL_G, T_CHANNEL_B, T_CHANNEL_H, T_CHANNEL_S, T_CHANNEL_LBP}; // TODO move to user definition
    int _chanelsLen = 7;

    /* Other attributes */
    string _dataFile;
    string _modelFile;


    /* Training data */
    RF_DataSampleCont * _data;

    /* Random Forest */
    RF_RandomForest * _forest;

};

#endif	/* RF_TRAIN_H */

