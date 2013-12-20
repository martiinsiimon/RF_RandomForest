/*
 * File:   RF_IO.h
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:43
 */

#ifndef RF_IO_H
#define	RF_IO_H

#include "RF_DataSampleCont.h"
#include "RF_DataSample.h"
#include "RF_RandomForest.h"

using namespace std;

class RF_IO {
public:
    RF_IO();
    RF_IO(const RF_IO& orig);
    virtual ~RF_IO();

    void setDataFile(string f);
    void setLabelFile(string f);
    void setModelFile(string f);

    RF_DataSampleCont * readData();
    RF_RandomForest readModel();

    void writeModel(RF_RandomForest rf);
private:
    string _dataFile;
    string _labelFile;
    string _modelFile;

};

#endif	/* RF_IO_H */

