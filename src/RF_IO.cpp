/*
 * File:   RF_IO.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:43
 */

#include "RF_IO.h"
#include <iostream>

using namespace std;

/**
 * Constructor of RF_IO
 */
RF_IO::RF_IO()
{
    this->_dataFile = "";
    this->_labelFile = "";
    this->_modelFile = "";
}

RF_IO::RF_IO(const RF_IO& orig)
{
    this->_dataFile = orig._dataFile;
    this->_labelFile = orig._labelFile;
    this->_modelFile = orig._modelFile;
}

RF_IO::~RF_IO()
{
}

void RF_IO::setDataFile(string f)
{
    this->_dataFile = f;
}

void RF_IO::setLabelFile(string f)
{
    this->_labelFile = f;
}

void RF_IO::setModelFile(string f)
{
    this->_modelFile = f;
}

RF_DataSampleCont* RF_IO::readData()
{
    if (this->_dataFile.length() < 1 || this->_labelFile.length() < 1)
        throw Exception();

    cout << "DBG: readData" << endl;

    return new RF_DataSampleCont();
}

RF_RandomForest RF_IO::readModel()
{
    if (this->_modelFile.length() < 1)
        throw Exception();
}