/*
 * File:   RF_Tree.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:38
 */

#include <vector>
#include <iostream>

#include "RF_Tree.h"
#include "RF_Utils.h"

using namespace std;
using namespace cv;

RF_Tree::RF_Tree()
{
    this->_treeId = -1;
    this->maximalDepth = 0;
    this->_dataset = NULL;
    this->probabilities = NULL;
    this->tLeft = NULL;
    this->tRight = NULL;
    this->func = NULL;
}


RF_Tree::~RF_Tree()
{


    if (this->probabilities != NULL)
        delete this->probabilities;

    if (this->tLeft != NULL)
        delete this->tLeft;

    if (this->tRight != NULL)
        delete this->tRight;

    if (this->func != NULL)
        delete this->func;
}

void RF_Tree::clearDataset()
{
    if (this->_dataset != NULL)
        delete this->_dataset;
}

void RF_Tree::setId(int id)
{
    this->_treeId = id;
}

int RF_Tree::getId()
{
    return this->_treeId;
}

string RF_Tree::dumpTree()
{
    return "Tree " + this->_treeId;
}

void RF_Tree::setChannels(vector<int> c)
{
    this->_channels = c;
}

void RF_Tree::setDataset(RF_DataSampleCont * d)
{
    this->_dataset = d;
}

void RF_Tree::setMaximalDepth(int i)
{
    this->maximalDepth = i;
}

int RF_Tree::getMaximalDepth()
{
    return this->maximalDepth;
}

bool RF_Tree::isLeaf()
{
    return this->leaf;
}

void RF_Tree::train()
{
    if (this->_channels.size() == 0 || this->_dataset == NULL)
    {
        //cout << "ERROR: sem jsem se nikdy nemel dostat!" << endl;
        return;
    }

    if (this->maximalDepth < 1)
    {
        //cout << "This is a leaf." << endl;
        this->leaf = true;
        this->probabilities = new RF_DataProb();
        return;
    }

    //TODO add the check for divergency among classes

    RF_DataSampleCont * dsc = this->_dataset;

    this->leaf = false;
    int x = RF_REC_W / 2;
    int y = RF_REC_H / 2;
    /* In every channel determine what's the maximal difference */
    int maximal = 0;
    int minimal = 255;
    int maxLen = 0;
    int maxCh = -1;

    //cout << "Channel Size: " << this->_channels.size() << endl;
    for (uint ch = 0; ch < this->_channels.size(); ch++)
    {
        int tmpMax = 0;
        int tmpMin = 256;

        for (int i = 0; i < dsc->samplesCount(); i++)
        {
            Mat tmpSample = dsc->getSample(i)->getChannel(this->_channels.at(ch));
            //cout << "Channel " << this->_channels.at(ch) << " - " << (int) tmpSample.at<uchar>(x, y) << endl;
            if ((int) tmpSample.at<uchar>(x, y) > tmpMax)
                tmpMax = (int) tmpSample.at<uchar>(x, y);
            if ((int) tmpSample.at<uchar>(x, y) < tmpMin)
                tmpMin = (int) tmpSample.at<uchar>(x, y);
            //break;
        }
        //cout << " Channel: " << this->_channels.at(ch) << ", min: " << tmpMin << ", max: " << tmpMax << endl;

        if (tmpMax - tmpMin >= maxLen)
        {
            maxLen = tmpMax - tmpMin;
            maxCh = ch;
            minimal = tmpMin;
            maximal = tmpMax;
        }
    }
    if (maxCh == -1)
    {
        //cout << "ChannelsCount: " << this->_channels.size() << endl;
        return;
    }

    /* Store found threshold and channel */
    int threshold = ((maximal - minimal) / 2) + minimal;
    int channel = this->_channels.at(maxCh);

    this->func = new RF_NodeFunc();
    this->func->setType(RF_FUNC_ABSTEST);
    this->func->setChannel(channel);
    this->func->setThreshold(threshold);


    /* Split the dataset according to maximal divergency in corect channel */
    RF_DataSampleCont* rightDSC = new RF_DataSampleCont();
    RF_DataSampleCont* leftDSC = new RF_DataSampleCont();


    for (int i = 0; i < dsc->samplesCount(); i++)
    {
        Mat tmpSample = dsc->getSample(i)->getChannel(channel);
        if ((int) tmpSample.at<uchar>(x, y) < threshold)
        {
            leftDSC->addSample(dsc->getSample(i));
        }
        else
        {
            rightDSC->addSample(dsc->getSample(i));
        }
    }

    //cout << "Left count: " << leftDSC->samplesCount() << ", right count:" << rightDSC->samplesCount() << endl;

    /* Initialize both sub-trees */
    this->tLeft = new RF_Tree();
    this->tLeft->setChannels(this->_channels);
    this->tLeft->setDataset(leftDSC);
    this->tLeft->setMaximalDepth(this->maximalDepth - 1);

    this->tRight = new RF_Tree();
    this->tRight->setChannels(this->_channels);
    this->tRight->setDataset(rightDSC);
    this->tRight->setMaximalDepth(this->maximalDepth - 1);

    /* Start training of both sub-trees */
    this->tLeft->train();
    this->tRight->train();
}

void RF_Tree::generatePosteriori()
{
    int x = RF_REC_W / 2;
    int y = RF_REC_H / 2;

    for (int i = 0; i < this->_dataset->samplesCount(); i++)
    {
        RF_DataSample* ds = this->_dataset->getSample(i);
        RF_Tree * tree = this;

        /* Go through the whole tree */
        while (!tree->isLeaf())
        {
            if ((int) ds->getChannel(tree->func->getChannel()).at<uchar>(x, y) < tree->func->getThreshold())
            {
                tree = tree->tLeft;
            }
            else
            {
                tree = tree->tRight;
            }
        }

        /* In tree is stored end leaf */
        tree->probabilities->increasePosteriori(ds->getLabel().at<uchar>(x, y));
    }
}

RF_DataProb* RF_Tree::solveTree(RF_DataSample *ds)
{

}
