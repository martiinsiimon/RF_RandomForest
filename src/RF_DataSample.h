/*
 * File:   RF_DataSample.h
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:48
 */

#ifndef RF_DATASAMPLE_H
#define	RF_DATASAMPLE_H

#include <opencv2/core/core.hpp>
#include <vector>

using namespace std;
using namespace cv;

class RF_DataSample {
public:
    RF_DataSample();
    RF_DataSample(const RF_DataSample& orig);
    virtual ~RF_DataSample();

    void addChannel(Mat& m);
    void generateChannel(int id);
    void setLabel(Mat& m);
    void setName(string s);
private:
    string _name;
    vector<Mat> _channel;
    Mat _label;
};

#endif	/* RF_DATASAMPLE_H */

