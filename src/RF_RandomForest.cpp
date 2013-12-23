/*
 * File:   RF_RandomForest.cpp
 * Author: martin
 *
 * Created on 29. říjen 2013, 16:59
 */

#include "RF_RandomForest.h"
#include "RF_Utils.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

RF_RandomForest::RF_RandomForest()
{
    this->_data = NULL;
    this->_maxDepth = 0;
    this->_treesCount = 0;
    this->_n = 0;
}

RF_RandomForest::~RF_RandomForest()
{
    for (uint i = 0; i < this->_trees.size(); i++)
    {
        this->_trees.at(i)->clearDataset();
        delete this->_trees.at(i);
    }
}

void RF_RandomForest::trainForest()
{
    if (this->_data == NULL || this->_maxDepth == 0 || this->_n == 0 || this->_treesCount == 0)
    {
        cerr << "Some of needed parameters are not set!" << endl;
        return;
    }

    /* Re-set random seed */
    srand(time(NULL));

    /* For every tree in forest*/
    for (int i = 0; i < this->_treesCount; i++)
    {
        /* Create tree */
        RF_Tree* t = new RF_Tree();
        t->setId(i);

        /* Generate random dataset */
        RF_DataSampleCont * sdc = new RF_DataSampleCont();
        for (int s = 0; s < this->_data->samplesCount(); s++)
        {
            RF_DataSample * tmp = this->_data->getSample(s);
            int w = tmp->getWidth();
            int h = tmp->getHeight();

            for (int j = 0; j < this->_n; j++)
            {
                int lx = rand() % (w - this->_n);
                int ly = rand() % (h - this->_n);
                sdc->addSample(tmp->getSubsample(lx, ly, lx + this->_n, ly + this->_n));
            }
        }
        t->setDataset(sdc);

        /* Generate random channel set */
        vector<int> channels;
        for (int j = 0; j < this->_n;)
        {
            int ch = (rand() % (T_CHANNEL_LAST - 1)) + 1;
            uint x;
            for (x = 0; x < channels.size(); x++)
            {
                if (channels.at(x) == ch)
                    break;
            }
            if (x < channels.size())
            {
                continue;
            }
            channels.push_back(ch);
            j++;
        }
        t->setChannels(channels);
        t->setMaximalDepth(this->_maxDepth);

        /* Train the tree */
        cout << "Training tree: " << t->getId() << endl;
        t->train();

        /* Generate posteriori probabilities */
        cout << "Generating probabilities for tree: " << t->getId() << endl;
        t->generatePosteriori();

        /* Put the tree into forest */
        this->_trees.push_back(t);
    }
}

void RF_RandomForest::setTreesCount(int n)
{
    this->_treesCount = n;
}

void RF_RandomForest::setMaxDepth(int n)
{
    this->_maxDepth = n;
}

void RF_RandomForest::setData(RF_DataSampleCont * data)
{
    this->_data = data;
}

void RF_RandomForest::setN(int n)
{
    this->_n = n;
}