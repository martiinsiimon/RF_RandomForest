/*
 * File:   RF_NodeFunc.h
 * Author: Martin Simon <martiinsiimon@gmail.com>
 */

#ifndef RF_NODEFUNC_H
#define RF_NODEFUNC_H

#include "RF_DataSampleCont.h"

enum RF_FUNC
{
    RF_FUNC_ABSTEST,
    //RF_FUNC_DIFFTEST,
    //RF_FUNC_WEIGHTEDTEST,
    RF_FUNC_END,
};

class RF_NodeFunc
{
public:
    RF_NodeFunc();

    virtual ~RF_NodeFunc();

    float computeInformationGain(RF_DataSampleCont *dsc);

    int getType();

    void setType(int t);

    int getChannel();

    void setChannel(int ch);

    /* ABSTEST */
    int getThreshold();

    void setThreshold(int t);

private:

    int type;

    /* ABSTEST */
    int threshold;
    int channel;
};

#endif	/* RF_NODEFUNC_H */

