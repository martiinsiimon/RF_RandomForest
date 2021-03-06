/*
 * File:   RF_DataSampleCont.h
 * Author: Martin Simon <martiinsiimon@gmail.com>
 */

#ifndef RF_DATASAMPLECONT_H
#define	RF_DATASAMPLECONT_H

#include <vector>
#include "RF_DataSample.h"

using namespace std;

class RF_DataSampleCont {
public:
    RF_DataSampleCont();
    virtual ~RF_DataSampleCont();

    ulong samplesCount();
    vector<RF_DataSample*>* getSamples();
    RF_DataSample* getSample(uint id);
    void addSample(RF_DataSample* s);
    void generateAllChannels();
    void generateAllowedChannels(int *ch, int len);

    void generateChannel(int);
private:
    vector<RF_DataSample*> _data;
};

#endif	/* RF_DATASAMPLECONT_H */

