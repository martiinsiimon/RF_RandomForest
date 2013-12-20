/*
 * File:   RF_Tree.h
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:38
 */

#ifndef RF_TREE_H
#define	RF_TREE_H

class RF_Tree {
public:
    RF_Tree();
    RF_Tree(const RF_Tree& orig);
    virtual ~RF_Tree();
private:
    int _treeId;
};

#endif	/* RF_TREE_H */

