/*
 * File:   RF_DataSample.h
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:48
 */

#ifndef RF_DATASAMPLE_H
#define	RF_DATASAMPLE_H

#include <opencv2/core/core.hpp>
#include <map>

using namespace std;
using namespace cv;

class RF_DataSample {
public:
    RF_DataSample();
    RF_DataSample(const RF_DataSample& orig);
    virtual ~RF_DataSample();

    void addChannel(Mat m, int i);

    void setLabel(Mat m);
    void setName(string s);
    string getName();
    Mat getChannel(int i);
    RF_DataSample* getSubsample(int lx, int ly, int hx, int hy);

    int getWidth();
    int getHeight();

    void generateChannel(int i);
    void createGrayscaleChannel();
    void createRedChannel();
    void createGreenChannel();
    void createBlueChannel();
private:
    string _name;
    map<int, Mat> _channel;
    Mat _label;
};

#endif	/* RF_DATASAMPLE_H */

