/*
 * File:   RF_Tree.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:38
 */

#include <vector>

#include "RF_Tree.h"
#include "RF_DataProb.h"

using namespace std;
using namespace cv;

RF_Tree::RF_Tree()
{
    this->_treeId = -1;
}

RF_Tree::RF_Tree(const RF_Tree& orig)
{
}

RF_Tree::~RF_Tree()
{
}

string RF_Tree::dumpTree()
{
    return "Tree " + this->_treeId;
}

void RF_Tree::setChannels(vector<int> c)
{
    this->_channels = c;
}

void RF_Tree::setDataset(vector<Mat> d)
{
    this->_dataset = d;
}

void RF_Tree::train()
{
    if (this->_channels.size() == 0 || this->_dataset.size() == 0)
        return;


}
