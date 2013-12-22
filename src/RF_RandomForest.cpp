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


        /* Generate random dataset */
        //TODO (N number of random rectangles in every original sample)

        /* Generate random channel set */
        vector<int> channels;
        for (int j = 0; j < this->_n; j++)
        {
            int ch = rand() % T_LAST;
            uint x;
            for (x = 0; x < channels.size(); x++)
            {
                if (channels.at(x) == ch)
                    break;
            }
            if (x < channels.size())
            {
                j--;
                continue;
            }
            channels.push_back(ch);
        }
        t->setChannels(channels);

        /* Train the tree */
        t->train();

        /* Put the tree into forest */
        this->_trees.push_back(t);

    }
    /*
     * generate this->treesCount of trees in this->_trees
     *
     * for every tree in this->_tree
     * generate random dataset (N number of random rectangles in every original sample)
     * generate random set of channels
     * call tree->trainTree()
     */
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