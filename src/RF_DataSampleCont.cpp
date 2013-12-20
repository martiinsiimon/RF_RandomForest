/*
 * File:   RF_DataSampleCont.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:51
 */

#include "RF_DataSampleCont.h"

RF_DataSampleCont::RF_DataSampleCont()
{
}

RF_DataSampleCont::RF_DataSampleCont(const RF_DataSampleCont& orig)
{
}

RF_DataSampleCont::~RF_DataSampleCont()
{
}

void RF_DataSampleCont::generateAllChannels()
{
    /*
     * For every channel in enum
     * call this->generateChannel(id)
     */
}

void RF_DataSampleCont::generateChannel(int id)
{
    /*
     * test if given id is in enum list of pre-defined channels
     * if so, continue. Otherwise, return
     *
     * for every sample in this->_data
     * call sample.genChannel(id)
     */
}