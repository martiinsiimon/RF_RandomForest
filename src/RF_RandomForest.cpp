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
#include <queue>
#include <string>
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
        //t->setId(0);

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
        t->setMaximalDepth(this->_maxDepth - 1);

        /* Train the tree */
        cout << "Training tree: " << i << endl;
        t->train();

        /* Generate posteriori probabilities */
        cout << "Generating probabilities for tree: " << i << endl;
        t->generatePosteriori();

        /* Validate tree */
        this->validateTree(t);

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

void RF_RandomForest::validateTree(RF_Tree* t)
{
    queue<RF_Tree*> todo;

    int id = 0;
    t->setId(id++);

    todo.push(t);

    while (!todo.empty())
    {
        RF_Tree* tmp = todo.front();
        todo.pop();

        if (tmp->isLeaf())
        {
            tmp->normalizeProbs();
            if (tmp->getLeft() != NULL)
            {
                cerr << "Tree is marked as a leaf and has left sub-tree!" << endl;
                delete tmp->getLeft();
            }
            if (tmp->getRight() != NULL)
            {
                cerr << "Tree is marked as a leaf and has right sub-tree!" << endl;
                delete tmp->getRight();
            }
            if (tmp->getFunc() != NULL)
            {
                cerr << "Tree is marked as a leaf and has a node function set!" << endl;
                delete tmp->getFunc();
            }
        }
        else
        {
            if (tmp->getLeft() == NULL)
            {
                cerr << "Tree is marked as a node and has no left sub-tree!" << endl;
                return;
            }
            if (tmp->getRight() == NULL)
            {
                cerr << "Tree is marked as a node and has no right sub-tree!" << endl;
                return;
            }
            if (tmp->getFunc() == NULL)
            {
                cerr << "Tree is marked as a node and has no node function set!" << endl;
                return;
            }

            tmp->getLeft()->setId(id++);
            tmp->getRight()->setId(id++);

            todo.push(tmp->getLeft());
            todo.push(tmp->getRight());
        }
    }
}

void RF_RandomForest::setN(int n)
{
    this->_n = n;
}

string RF_RandomForest::dumpForest()
{
    string result = "";
    for (vector<RF_Tree*>::iterator it = this->_trees.begin(); it != this->_trees.end(); it++)
    {
        result += "#Tree \n";
        result += (*it)->dumpTree();
        result += '\n';
    }
    return result;
}

void RF_RandomForest::addTree(RF_Tree* t)
{
    this->_trees.push_back(t);
}