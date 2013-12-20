/*
 * File:   RF_Train.h
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:39
 */

#ifndef RF_TRAIN_H
#define	RF_TRAIN_H

#include <iostream>
#include "RF_DataSampleCont.h"
#include "RF_RandomForest.h"

/* Hardcoded constant. TOTO: make them user defined variables */
#define RF_MAX_DEPTH 5
#define RF_MAX_TREES 5

using namespace std;

class RF_Train {
public:
    RF_Train();
    RF_Train(const RF_Train& orig);
    RF_Train(string dataFile, string labelFile, string modelFile);
    virtual ~RF_Train();
    void setDataFile(string f);
    void setLabelFile(string f);
    void setModelFile(string f);

    void prepareTraining(void);
    void trainForest(void);

    void exportModel(void);

    void printResults(void);
    string getResults(void);
private:

    /* Forest configuration */
    int _maxDepth;
    int _maxTrees;

    /* Other attributes */
    string _dataFile;
    string _labelFile;
    string _modelFile;
    bool _trained;

    /* Training data */
    RF_DataSampleCont * _data;

    /* Random Forest */
    RF_RandomForest * _forest;

};

#endif	/* RF_TRAIN_H */

