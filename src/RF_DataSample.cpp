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
    //this->_channel.clear();
}

void RF_DataSample::addChannel(Mat m, int i)
{
    this->_channel[i] = m;
}

Mat RF_DataSample::getChannel(int i)
{
    return this->_channel.at(i);
}

int RF_DataSample::getHeight()
{
    return this->_label.rows;
}

int RF_DataSample::getWidth()
{
    return this->_label.cols;
}

void RF_DataSample::setLabel(Mat m)
{
    this->_label = m;
}

Mat RF_DataSample::getLabel()
{
    return this->_label;
}

void RF_DataSample::setName(string s)
{
    this->_name = s;
}

RF_DataSample* RF_DataSample::getSubsample(int lx, int ly, int hx, int hy)
{
    RF_DataSample * ds = new RF_DataSample();

    ds->setName(this->_name);
    ds->setLabel(Mat(this->_label, Rect(lx, ly, hx - lx, hy - ly)));

    for (map<int, Mat>::iterator it = this->_channel.begin(); it != this->_channel.end(); it++)
    {
        ds->addChannel(Mat(it->second, Rect(lx, ly, hx - lx, hy - ly)), it->first);
    }
    return ds;
}

void RF_DataSample::generateChannel(int id)
{
    switch (id)
    {
    case T_CHANNEL_RGB:
        break;
    case T_CHANNEL_GRAY:
        this->createGrayscaleChannel();
        break;
    case T_CHANNEL_R:
        this->createRedChannel();
        break;
    case T_CHANNEL_G:
        this->createGreenChannel();
        break;
    case T_CHANNEL_B:
        this->createBlueChannel();
        break;
    default:
        return;
    }
}

void RF_DataSample::createGrayscaleChannel()
{
    Mat gray;
    cvtColor(this->_channel[T_CHANNEL_RGB], gray, CV_BGR2GRAY);
    this->_channel[T_CHANNEL_GRAY] = gray;
}

void RF_DataSample::createRedChannel()
{
    Mat channel[3];

    split(this->_channel[T_CHANNEL_RGB], channel); //order BGR

    this->_channel[T_CHANNEL_R] = channel[2];
}

void RF_DataSample::createGreenChannel()
{
    Mat channel[3];

    split(this->_channel[T_CHANNEL_RGB], channel); //order BGR

    this->_channel[T_CHANNEL_G] = channel[1];
}

void RF_DataSample::createBlueChannel()
{
    Mat channel[3];

    split(this->_channel[T_CHANNEL_RGB], channel); //order BGR

    this->_channel[T_CHANNEL_B] = channel[0];
}