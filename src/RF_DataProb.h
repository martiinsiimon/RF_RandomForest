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
typedef unsigned int uint;


class RF_DataProb {
public:
    RF_DataProb();
    RF_DataProb(const RF_DataProb& orig);
    virtual ~RF_DataProb();

    float getPosteriori(uint i);
    uint getMaximal();
    void increasePosteriori(uint i);
    void normalize();

    string dumpProbabilities();

    void addValues(uint key, float val);
    void clear();
    void sum(RF_DataProb * p);
    void product(RF_DataProb * p);
private:

    map<uint, float> probabilities;
};

#endif	/* RF_DATAPROB_H */

