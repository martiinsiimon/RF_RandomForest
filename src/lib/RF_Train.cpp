/*
 * File:   RF_Train.cpp
 * Author: Martin Simon <martiinsiimon@gmail.com>
 */

#include "RF_Train.h"
#include "RF_IO.h"
#include "RF_Utils.h"

#include <iostream>

using namespace std;

/**
 * Class constructor.
 */
RF_Train::RF_Train()
{
    this->_data = NULL;
    this->_forest = NULL;
}

/**
 * Class constructor with data provided
 */
RF_Train::RF_Train(string dataFile, string modelFile)
{
    this->_dataFile = dataFile;
    this->_modelFile = modelFile;

    this->trained = false;
    this->_data = NULL;
    this->_forest = NULL;

    /* Hardcoded internal variables TODO: enable configuration */
    this->_maxDepth = RF_MAX_DEPTH;
    this->_maxTrees = RF_MAX_TREES;
    this->_n = RF_N;
}

/**
 * Class destructor.
 */
RF_Train::~RF_Train()
{
    if (this->_forest != NULL)
        delete this->_forest;
    if (this->_data != NULL)
        delete this->_data;
}

/**
 * Set data file
 */
void RF_Train::setDataFile(string f)
{
    this->_dataFile = f;
}

/**
 * Set model file
 */
void RF_Train::setModelFile(string f)
{
    this->_modelFile = f;
}

/**
 * Provide needed information for model training
 */
void RF_Train::prepareTraining()
{
    RF_IO *io = new RF_IO();
    io->setDataFile(this->_dataFile);

    this->_data = io->readData();

    delete io;

    /* Generate all allowed channels */
    // TODO this should be in configuration
    this->_data->generateAllowedChannels(this->_allowedChannels, this->_chanelsLen);

    /* Generate all channels */
    //this->_data->generateAllChannels();
}

/**
 * Train random forest above provided information
 */
void RF_Train::trainForest()
{
    cout << "Training random forest started" << endl;

    RF_RandomForest *rf = new RF_RandomForest();
    rf->setData(this->_data);
    rf->setMaxDepth(this->_maxDepth);
    rf->setTreesCount(this->_maxTrees);
    rf->setN(this->_n);
    rf->addAllowedChannel(this->_allowedChannels, this->_chanelsLen);

    cout << endl << "Allowed channels:";
    for (int x = 0; x < this->_chanelsLen; x++)
    {
        cout << " " << this->_allowedChannels[x];
    }
    cout << endl;
    if (rf->trainForest())
        this->trained = true;

    this->_forest = rf;
}

/**
 * Export trained model to file
 */
void RF_Train::exportModel()
{
    cout << "Exporting model" << endl;
    RF_IO *io = new RF_IO();
    io->setModelFile(this->_modelFile);
    io->writeModel(this->_forest);
    delete io;
}

/**
 * Print information about model training
 */
void RF_Train::printResults()
{
    /* Print results */
    cout << this->getResults() << endl;
}

/**
 * Return model information after training
 *
 * @todo implement information gain from trained model to print it
 */
string RF_Train::getResults()
{
    string resultDump = "Model status: ";

    /* Check if model is trained or not */
    if (this->trained)
    {
        /* The model is already trained */
        resultDump += "TRAINED\n";
        //TODO implement information from trained forest
        resultDump += "Maximal depth: ";
        resultDump += Number2String(this->_maxDepth);
        resultDump += '\n';
        resultDump += "Maximal trees count: ";
        resultDump += Number2String(this->_maxTrees);
    } else
    {
        resultDump += "NOT TRAINED\n";
        resultDump += "Maximal depth: ";
        resultDump += Number2String(this->_maxDepth);
        resultDump += '\n';
        resultDump += "Maximal trees count: ";
        resultDump += Number2String(this->_maxTrees);
    }

    return resultDump;
}