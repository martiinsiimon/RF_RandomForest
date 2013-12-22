/*
 * File:   RF_DataSample.cpp
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:48
 */

#include "RF_DataSample.h"
#include "RF_Utils.h"
#include <opencv2/imgproc/imgproc.hpp>

RF_DataSample::RF_DataSample()
{
    this->_name = "";
}

RF_DataSample::RF_DataSample(const RF_DataSample& orig)
{
}

RF_DataSample::~RF_DataSample()
{
    this->_channel.clear();
}

void RF_DataSample::addChannel(Mat m, int i)
{
    this->_channel[i] = m;
}



void RF_DataSample::setLabel(Mat m)
{
    this->_label = m;
}

void RF_DataSample::setName(string s)
{
    this->_name = s;
}

void RF_DataSample::generateChannel(int id)
{
    switch (id)
    {
    case T_RGB:
        break;
    case T_GRAY:
        this->createGrayscaleChannel();
        break;
    case T_R:
        this->createRedChannel();
        break;
    case T_G:
        this->createGreenChannel();
        break;
    case T_B:
        this->createBlueChannel();
        break;
    default:
        return;
    }
}

void RF_DataSample::createGrayscaleChannel()
{
    Mat gray;
    cvtColor(this->_channel[T_RGB], gray, CV_BGR2GRAY);
    this->_channel[T_GRAY] = gray;
}

void RF_DataSample::createRedChannel()
{
    Mat channel[3];

    split(this->_channel[T_RGB], channel); //order BGR

    this->_channel[T_R] = channel[2];
}

void RF_DataSample::createGreenChannel()
{
    Mat channel[3];

    split(this->_channel[T_RGB], channel); //order BGR

    this->_channel[T_G] = channel[1];
}

void RF_DataSample::createBlueChannel()
{
    Mat channel[3];

    split(this->_channel[T_RGB], channel); //order BGR

    this->_channel[T_B] = channel[0];
}