/*
 * File:   RF_DataProb.h
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:39
 */

#ifndef RF_DATAPROB_H
#define	RF_DATAPROB_H

#include <map>

using namespace std;
typedef unsigned char uchar;


class RF_DataProb {
public:
    RF_DataProb();
    RF_DataProb(const RF_DataProb& orig);
    virtual ~RF_DataProb();

    float getPosteriori(uchar i);
    int getMaximal();
    void increasePosteriori(uchar i);
    void normalize();
private:

    map<uchar, float> probabilities;
};

#endif	/* RF_DATAPROB_H */

