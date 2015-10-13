/*
 * File:   RF_Tree.cpp
 * Author: Martin Simon <martiinsiimon@gmail.com>
 */

#include <vector>
#include <queue>
#include <iostream>

#include "RF_Tree.h"

using namespace std;
using namespace cv;

/**
 * Class constructor.
 */
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

/**
 * Class destructor.
 */
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
    queue<RF_Tree *> todo;
    todo.push(this);
    string result = "";

    while (!todo.empty())
    {
        RF_Tree *tmp = todo.front();
        todo.pop();

        if (tmp->isLeaf())
        {
            /* The node is a leaf */
            result += Number2String(tmp->getId());
            result += "(:";
            result += tmp->getProbabilities()->dumpProbabilities();
            result += ") ";
        } else
        {
            /* The node is a node */
            result += Number2String(tmp->getId());
            result += "(";
            result += Number2String(tmp->getLeft()->getId());
            result += ",";
            result += Number2String(tmp->getRight()->getId());
            result += ")(";
            result += Number2String(tmp->getFunc()->getType());
            result += ",";
            result += Number2String(tmp->getFunc()->getChannel());
            result += ",";
            result += Number2String(tmp->getFunc()->getThreshold());
            result += ") ";

            todo.push(tmp->getLeft());
            todo.push(tmp->getRight());
        }
    }

    return result;
}

void RF_Tree::setChannels(vector<int> c)
{
    this->_channels = c;
}

void RF_Tree::setDataset(RF_DataSampleCont *d)
{
    this->_dataset = d;
}

RF_DataProb *RF_Tree::getProbabilities()
{
    return this->probabilities;
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
        cerr << "No dataset or no channel!" << endl;
        return;
    }

    if (this->maximalDepth < 1)
    {
        this->leaf = true;
        this->probabilities = new RF_DataProb();
        return;
    }

    RF_DataSampleCont *dsc = this->_dataset;
    this->leaf = false;
    int x = RF_REC_W / 2;
    int y = RF_REC_H / 2;

    /* Generate random combinations of function type, channel and value(s) in the test function. For every combination
     * generated, compute information */
    RF_NodeFunc *nf[5];
    float informationGain;
    float highestGain = 0.0;
    int highestIndex = 0;
    for (int i = 0; i < 5; i++)
    {
        nf[i] = new RF_NodeFunc();
        nf[i]->setType(rand() % ((uint) RF_FUNC_END));
        nf[i]->setChannel(this->_channels[rand() % ((uint) this->_channels.size())]);
        //TODO set threshold from min-max interval to avoid meaningless evaluation
        nf[i]->setThreshold(rand() % 255 + 1);
        informationGain = nf[i]->computeInformationGain(dsc);

        if (informationGain > highestGain)
        {
            highestGain = informationGain;
            highestIndex = i;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (i != highestIndex)
            delete nf[i];
    }

    this->func = nf[highestIndex];

    /* Split the dataset according to maximal divergency in corect channel */
    RF_DataSampleCont *rightDSC = new RF_DataSampleCont();
    RF_DataSampleCont *leftDSC = new RF_DataSampleCont();
    Mat tmpSample;

    for (uint i = 0; i < dsc->samplesCount(); i++)
    {
        tmpSample = dsc->getSample(i)->getChannel(this->func->getChannel());
        if ((int) tmpSample.at<uchar>(y, x) < this->func->getThreshold())
            leftDSC->addSample(dsc->getSample(i));
        else
            rightDSC->addSample(dsc->getSample(i));
    }

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

    for (uint i = 0; i < this->_dataset->samplesCount(); i++)
    {
        RF_DataSample *ds = this->_dataset->getSample(i);
        RF_Tree *tree = this;

        /* Go through the whole tree */
        while (!tree->isLeaf())
        {
            if ((int) ds->getChannel(tree->func->getChannel()).at<uchar>(y, x) < tree->func->getThreshold())
            {
                tree = tree->tLeft;
            } else
            {
                tree = tree->tRight;
            }
        }

        /* In tree is stored end leaf */
        Vec3b color = ds->getLabel().at<Vec3b>(y, x);
        tree->probabilities->increasePosteriori(color[0] + (color[1] << 8) + (color[2] << 16));
    }
}

RF_Tree *RF_Tree::getLeft()
{
    return this->tLeft;
}

RF_Tree *RF_Tree::getRight()
{
    return this->tRight;
}

void RF_Tree::normalizeProbs()
{
    this->probabilities->normalize();
}

RF_NodeFunc *RF_Tree::getFunc()
{
    return this->func;
}

RF_DataProb *RF_Tree::solveTree(RF_DataSample *ds)
{
    RF_Tree *tree = this;
    while (!tree->isLeaf())
    {
        if ((int) ds->getChannel(tree->getFunc()->getChannel()).at<uchar>(0, 0) < tree->getFunc()->getThreshold())
        {
            //left
            tree = tree->tLeft;
        } else
        {
            //right
            tree = tree->tRight;
        }
    }
    return tree->getProbabilities();
}

void RF_Tree::addSubtree(bool leaf, int id, int left, int right, RF_NodeFunc *f, RF_DataProb *p)
{
    queue<RF_Tree *> todo;

    todo.push(this);

    while (!todo.empty())
    {
        RF_Tree *tmp = todo.front();
        todo.pop();

        if (tmp->getId() == id)
        {
            if (leaf)
            {
                tmp->addLeaf(p);
                return;
            } else
            {
                tmp->addNode(left, right, f);
                return;
            }
        } else
        {
            if (tmp->tLeft != NULL)
                todo.push(tmp->tLeft);
            if (tmp->tRight != NULL)
                todo.push(tmp->tRight);
        }
    }
}

void RF_Tree::addNode(int left, int right, RF_NodeFunc *f)
{
    this->leaf = false;
    this->tLeft = new RF_Tree();
    this->tLeft->setId(left);
    this->tRight = new RF_Tree();
    this->tRight->setId(right);
    this->func = f;
}

void RF_Tree::addLeaf(RF_DataProb *p)
{
    this->leaf = true;
    this->tLeft = NULL;
    this->tRight = NULL;
    this->probabilities = p;
}