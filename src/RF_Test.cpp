/*
 * File:   RF_Test.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:42
 */

#include "RF_Test.h"
#include <iostream>

using namespace std;

RF_Test::RF_Test()
{
    this->modelFile = "";
    this->dataFile = "";

    this->forest = NULL;
}

RF_Test::RF_Test(string _dataPath, string _modelPath)
{
    this->modelFile = _modelPath;
    this->dataFile = _dataPath;

    this->forest = NULL;
}

RF_Test::~RF_Test()
{
    if (this->forest != NULL)
        delete this->forest;
}

void RF_Test::setDataFile(string f)
{
    this->dataFile = f;
}

void RF_Test::setModelFile(string f)
{
    this->modelFile = f;
}

void RF_Test::loadModel()
{
    cout << "DBG: load model from file" << endl;
    if (this->modelFile.empty())
        return;
    RF_IO * io = new RF_IO();
    io->setModelFile(this->modelFile);

    this->forest = io->readModel();

    delete io;
}

void RF_Test::solveData()
{
    cout << "DBG: solve model " << endl;
    //TODO add solve for every point in model
}

void RF_Test::printResults()
{
    cout << "DBG: print results" << endl;
}