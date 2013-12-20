/*
 * File:   RF_DataSampleCont.h
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:51
 */

#ifndef RF_DATASAMPLECONT_H
#define	RF_DATASAMPLECONT_H

#include <vector>
#include "RF_DataSample.h"

using namespace std;

class RF_DataSampleCont {
public:
    RF_DataSampleCont();
    RF_DataSampleCont(const RF_DataSampleCont& orig);
    virtual ~RF_DataSampleCont();

    int addSample(RF_DataSample s);
    void generateAllChannels();
    void generateChannel(int);
private:
    vector<RF_DataSample> _data;
};

#endif	/* RF_DATASAMPLECONT_H */

