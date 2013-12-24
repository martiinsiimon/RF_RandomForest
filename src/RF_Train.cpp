/*
 * File:   RF_Train.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:39
 */

#include "RF_Train.h"
#include "RF_IO.h"
#include "RF_Utils.h"

#include <iostream>

using namespace std;

RF_Train::RF_Train()
{
    this->_data = NULL;
    this->_forest = NULL;
}


RF_Train::RF_Train(string dataFile, string modelFile)
{
    cout << "DBG: constructor" << endl;

    this->_dataFile = dataFile;
    this->_modelFile = modelFile;

    this->_trained = false;
    this->_data = NULL;
    this->_forest = NULL;

    /* Hardcoded internal variables TODO: enable configuration */
    this->_maxDepth = RF_MAX_DEPTH;
    this->_maxTrees = RF_MAX_TREES;
    this->_n = RF_N;
}

RF_Train::~RF_Train()
{

    if (this->_forest != NULL)
        delete this->_forest;
    if (this->_data != NULL)
        delete this->_data;
}

void RF_Train::setDataFile(string f)
{
    this->_dataFile = f;
}

void RF_Train::setModelFile(string f)
{
    this->_modelFile = f;
}

void RF_Train::prepareTraining(void)
{
    cout << "DBG: prepareTraining" << endl;
    RF_IO * io = new RF_IO();
    io->setDataFile(this->_dataFile);

    this->_data = io->readData();

    delete io;

    /* Generate all channels */
    this->_data->generateAllChannels();
}

void RF_Train::trainForest()
{
    cout << "DBG: trainForest" << endl;

    RF_RandomForest* rf = new RF_RandomForest();
    rf->setData(this->_data);
    rf->setMaxDepth(this->_maxDepth);
    rf->setTreesCount(this->_maxTrees);
    rf->setN(this->_n);

    rf->trainForest();

    this->_forest = rf;
}

void RF_Train::exportModel(void)
{
    cout << "DBG: exportModel" << endl;
    RF_IO * io = new RF_IO();
    io->setModelFile(this->_modelFile);
    io->writeModel(this->_forest);
    delete io;
}

void RF_Train::printResults(void)
{
    /* Print results */
    this->getResults();
}

string RF_Train::getResults(void)
{
    string resultDump = "Model status: ";

    /* Check if model is trained or not */
    if (this->_trained)
    {
        /* The model is already trained */
        resultDump += "TRAINED\n";
        //TODO implement information from trained forest
    }
    else
    {
        resultDump += "NOT TRAINED\n";
        resultDump += "Maximal depth: ";
        resultDump += this->_maxDepth;
        resultDump += '\n';
        resultDump += "Maximal trees count: ";
        resultDump += this->_maxTrees;
        resultDump += '\n';
    }

    return resultDump;
}