/*
 * File:   RF_NodeFunc.cpp
 * Author: Martin Simon <martiinsiimon@gmail.com>
 */

#include "RF_NodeFunc.h"
#include "RF_Utils.h"
#include "RF_DataProb.h"

/**
 * Class constructor.
 */
RF_NodeFunc::RF_NodeFunc()
{
    this->type = 0;
    this->channel = 0;
    this->threshold = 0;
}

/**
 * Class destructor.
 */
RF_NodeFunc::~RF_NodeFunc()
{
}

/**
 * Get type of node function. See RF_FUNC enum for available functions.
 *
 * @return Function type. See RF_FUNC for more details
 */
int RF_NodeFunc::getType()
{
    return this->type;
}

/**
 * Set type of node function. See RF_FUNC enum for available functions.
 *
 * @param t Function type. See RF_FUNC for more details
 */
void RF_NodeFunc::setType(int t)
{
    this->type = t;
}

/**
 * Get channel of node function. See T_CHANNELS enum for available channels.
 *
 * @return Channel number. See T_CHANNELS for more details
 */
int RF_NodeFunc::getChannel()
{
    return this->channel;
}

/**
 * St channel of node function. See T_CHANNELS enum for available channels.
 *
 * @param ch Channel of node function. See T_CHANNELS for more details
 */
void RF_NodeFunc::setChannel(int ch)
{
    this->channel = ch;
}

/**
 * Get threshold of RF_FUNC_ABSTEST node function.
 *
 * @return Threshold of node function
 */
int RF_NodeFunc::getThreshold()
{
    return this->threshold;
}

/**
 * Set threshold of RF_FUNC_ABSTEST node function.
 *
 * @param t Threshold of node function
 */
void RF_NodeFunc::setThreshold(int t)
{
    this->threshold = t;
}

/**
 * Compute information gain for this function.
 *
 * @todo this func needs to be fixed for general function type
 * @todo implement also Gain Ration as an alternative for InfoGain (GainInfo/IntrinsicInfo)
 * @param dsc dataset for which the information gain should be computed
 */
float RF_NodeFunc::computeInformationGain(RF_DataSampleCont *dsc)
{
    ulong rightCnt = 0;
    ulong leftCnt = 0;
    ulong allCnt = dsc->samplesCount();
    uchar tmpSample, tmpLabel;
    int x = RF_REC_W / 2;
    int y = RF_REC_H / 2;
    RF_DataProb *leftCnts = new RF_DataProb();
    RF_DataProb *rightCnts = new RF_DataProb();
    RF_DataProb *allCnts = new RF_DataProb();

    /* Compute counts of similar labels and the same for dataset after split */
    for (uint i = 0; i < allCnt; i++)
    {
        tmpSample = dsc->getSample(i)->getChannel(this->channel).at<uchar>(y, x);
        tmpLabel = dsc->getSample(i)->getLabel().at<uchar>(y, x);

        allCnts->increasePosteriori(tmpLabel);

        if ((int) tmpSample < this->threshold)
        {
            leftCnts->increasePosteriori(tmpLabel);
            leftCnt++;
        } else
        {
            rightCnts->increasePosteriori(tmpLabel);
            rightCnt++;
        }
    }

    /* Compute entropy for actual dataset
     *   E(S) = -\sum_{i=1}^{n}{pi*log pi}
     *    0 * log 0 == 0 !!
     */
    float ES = 0.0;
    float ES_l = 0.0;
    float ES_r = 0.0;
    float pi;
    vector<uint> allKeys = allCnts->getKeys();

    for (uint i = 0; i < allKeys.size(); i++)
    {
        pi = (allCnts->getPosteriori(allKeys[i]) / allCnt);
        ES -= (pi * log2(pi));
        if (leftCnts->getPosteriori(allKeys[i]) > 0.0)
        {
            pi = (leftCnts->getPosteriori(allKeys[i]) / leftCnt);
            ES_l -= (pi * log2(pi));
        }
        if (rightCnts->getPosteriori(allKeys[i]) > 0.0)
        {
            pi = (rightCnts->getPosteriori(allKeys[i]) / rightCnt);
            ES_r -= (pi * log2(pi));
        }
    }

    /* Compute average entropy
     *   I(S,A) = \sum{\frac{|Si|}{|S|} * E(Si)}
     *     Si... samples of class i (class i is left or right sub-tree)
     *     S.... all samples (in root)
     *     Ei... entropy in class i (class i is left or right sub-tree)
     */
    float ISA = ((float) leftCnt / allCnt) * ES_l + ((float) rightCnt / allCnt) * ES_r;

    /* Compute Information Gain
     *   Gain(S,A) = E(S,A) - I(S,A)
     */
    float infoGain = ES - ISA;

    /* Clear allocated memory */
    delete allCnts;
    delete leftCnts;
    delete rightCnts;

    return infoGain;
}
