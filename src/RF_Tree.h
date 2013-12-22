/*
 * File:   RF_Tree.h
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:38
 */

#ifndef RF_TREE_H
#define	RF_TREE_H

#include <vector>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

class RF_Tree {
public:
    RF_Tree();
    RF_Tree(const RF_Tree& orig);
    virtual ~RF_Tree();

    void train();

    void setDataset(vector<Mat> d);
    void setChannels(vector<int> c);

    string dumpTree();

private:
    int _treeId;

    vector<Mat> _dataset;
    vector<int> _channels;
};

#endif	/* RF_TREE_H */

