/*
 * File:   RF_IO.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:43
 */

#include "RF_IO.h"
#include "RF_Utils.h"
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

/**
 * Constructor of RF_IO
 */
RF_IO::RF_IO()
{
    this->_dataFile = "";
    this->_modelFile = "";
}

RF_IO::RF_IO(const RF_IO& orig)
{
    this->_dataFile = orig._dataFile;
    this->_modelFile = orig._modelFile;
}

RF_IO::~RF_IO()
{
}

void RF_IO::setDataFile(string f)
{
    this->_dataFile = f;
}


void RF_IO::setModelFile(string f)
{
    this->_modelFile = f;
}

RF_DataSampleCont* RF_IO::readData()
{
    if (this->_dataFile.length() < 1)
        throw Exception();
    cout << "DBG: readData" << endl;

    RF_DataSampleCont * cont = new RF_DataSampleCont();

    /* Read data */
    ifstream inData(this->_dataFile.c_str());
    int i = 0;
    for (string line; getline(inData, line); i++)
    {
        RF_DataSample *sample = new RF_DataSample();

        if (line.find(";") == string::npos)
        {
            delete sample;
            continue;
        }

        string imgPath = line.substr(0, line.find(";"));
        string labelPath = line.substr(line.find(";") + 1, line.length() - line.find(";") - 1);

        sample->setName(line);
        sample->addChannel(imread(imgPath), T_CHANNEL_RGB);
        sample->setLabel(imread(labelPath));

        cont->addSample(sample);
    }
    inData.close();




    return cont;
}

RF_RandomForest* RF_IO::readModel()
{
    if (this->_modelFile.length() < 1)
        throw Exception();

    RF_RandomForest * rf = new RF_RandomForest();

    //parse input file


    return rf;
}

/**
 * Write random forest model given in parameter into file also given in parameter.
 *
 * @param rf
 * @param path
 */
void RF_IO::writeModel(RF_RandomForest * rf)
{
    if (this->_modelFile.length() < 1)
        throw Exception();

    ofstream outData(this->_modelFile.c_str());
    outData << rf->dumpForest();
    outData.close();
}