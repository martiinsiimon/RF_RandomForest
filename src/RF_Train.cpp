/*
 * File:   RF_Train.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:39
 */

#include "RF_Train.h"
#include "RF_IO.h"


#include <iostream>

using namespace std;

RF_Train::RF_Train()
{
}

RF_Train::RF_Train(const RF_Train& orig)
{
}

RF_Train::~RF_Train()
{
}

RF_Train::RF_Train(string dataFile, string labelFile, string modelFile)
{
    cout << "DBG: constructor" << endl;

    this->_dataFile = dataFile;
    this->_labelFile = labelFile;
    this->_modelFile = modelFile;

    this->_trained = false;

    /* Hardcoded internal variables TODO: enable configuration */
    this->_maxDepth = RF_MAX_DEPTH;
    this->_maxTrees = RF_MAX_TREES;
}

void RF_Train::setDataFile(string f)
{
    this->_dataFile = f;
}

void RF_Train::setLabelFile(string f)
{
    this->_labelFile = f;
}

void RF_Train::setModelFile(string f)
{
    this->_modelFile = f;
}

void RF_Train::prepareTraining(void)
{
    cout << "DBG: prepareTraining" << endl;
    RF_IO io = RF_IO();
    io.setDataFile(this->_dataFile);
    io.setLabelFile(this->_labelFile);

    this->_data = io.readData();

    /* Generate all channels */
    this->_data->generateAllChannels();
}

void RF_Train::trainForest(void)
{
    cout << "DBG: trainForest" << endl;

    RF_RandomForest* rf = new RF_RandomForest();
    rf->setData(this->_data);
    rf->setMaxDepth(this->_maxDepth);
    rf->setTreesCount(this->_maxTrees);

    rf->trainForest();

    this->_forest = rf;
}

//void RF_Train::trainTree(void)
//{
//    cout << "DBG: trainTree" << endl;
/*
 * every node starts as leaf
 * jestli neni dosazena maximalni hloubka a mezi daty k trenovani je dostatecna diverzita
 * najdi channel, kde je nejvetsi diverzita (max - min)
 * najdi stredni hodnotu [(max - min)/2 + min]
 * zapis do uzlu
 */
//}

void RF_Train::exportModel(void)
{
    cout << "DBG: exportModel" << endl;
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
        resultDump += "Maximal depth: " + this->_maxDepth + '\n';
        resultDump += "Maximal trees count: " + this->_maxTrees + '\n';
    }

    return resultDump;
}