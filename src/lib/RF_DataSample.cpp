/*
 * File:   RF_DataSample.cpp
 * Author: Martin Simon <martiinsiimon@gmail.com>
 */

#include "RF_DataSample.h"
#include "RF_Utils.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

/**
 * Class constructor. The name of sample is initialized as empty string.
 */
RF_DataSample::RF_DataSample()
{
    this->_name = "";
}

/**
 * Class destructor.
 */
RF_DataSample::~RF_DataSample()
{
    this->_channel.clear();
}

/**
 * Add sample channel to internal channel vector. The new channel should have the very same size (width and height) as the original sample and the label.
 *
 * @param m New channel to be add
 * @param i Index in internal channel vector where the new channel will be stored
 */
void RF_DataSample::setChannel(Mat m, int i)
{
    this->_channel[i] = m;
}

/**
 * Return channel at given position in internal channel vector.
 *
 * @param i Index of wanted channel in internal channel vector
 * @return Channel at given index
 */
Mat RF_DataSample::getChannel(int i)
{
    if (this->_channel.count(i) == 1)
        return this->_channel[i];
    else
        return Mat();
}

/**
 * Return number of rows of label object
 *
 * @return Height (rows) of label object
 */
int RF_DataSample::getHeight()
{
    return this->_label.rows;
}

/**
 * Return number of cols of label object
 *
 * @return Width (cols) of label object
 */
int RF_DataSample::getWidth()
{
    return this->_label.cols;
}

/**
 * Insert label channel. Should have the very same size (width and height) as the original sample
 *
 * @param m The label matrix
 */
void RF_DataSample::setLabel(Mat m)
{
    this->_label = m;
}

/**
 * Return label matrix.
 *
 * @return Matrix with sample labels
 */
Mat RF_DataSample::getLabel()
{
    return this->_label;
}

/**
 * Set a name of this sample
 *
 * @param s New name of this sample
 */
void RF_DataSample::setName(string s)
{
    this->_name = s;
}

/**
 * Get a name of this sample
 * @return A name of this sample
 */
string RF_DataSample::getName()
{
    return this->_name;
}

/**
 * Create and return new sample with all channels in given region. The region is determined as rextangle with two opposite vertices (low [lx,ly] and high [hx,hy]). Also one element matrix can be returned by setting both vertices the same.
 *
 * @param lx Lower vertex x-coordinate
 * @param ly Lower vertex y-coordinate
 * @param hx Higher vertex x-coordinate
 * @param hy Higher vertex y-coordinate
 * @return New subsample in given region of this sample (with all channels)
 */
RF_DataSample *RF_DataSample::getSubsample(int lx, int ly, int hx, int hy)
{
    RF_DataSample *ds = new RF_DataSample();

    /* Set the same name */
    ds->setName(this->_name);

    /* Get subsample of label */
    if (lx == hx && ly == hy)
    {
        /* Only one element matrix wanted */
        ds->setLabel(Mat(this->_label.at<Vec3b>(ly, lx)));
    } else
    {
        /* Rectangle of original sample wanted */
        ds->setLabel(Mat(this->_label, Rect(lx, ly, hx - lx, hy - ly)));
    }

    /* Do the same with all the channels */
    for (map<int, Mat>::iterator it = this->_channel.begin(); it != this->_channel.end(); it++)
    {
        if (it->first == T_CHANNEL_RGB || it->first == T_CHANNEL_HSV)
            continue;

        if (lx == hx && ly == hy)
        {
            /* Only one element matrix wanted */
            if (it->first == T_CHANNEL_RGB || it->first == T_CHANNEL_HSV)
            {
                ds->setChannel(Mat(it->second.at<Vec3b>(ly, lx)), it->first);
            } else
            {
                ds->setChannel(Mat(1, 1, CV_8UC1, Scalar(it->second.at<uchar>(ly, lx))), it->first);
            }
        } else
        {
            /* Rectangle of original sample wanted */
            ds->setChannel(Mat(it->second, Rect(lx, ly, hx - lx, hy - ly)), it->first);
        }
    }
    return ds;
}

/**
 * Generate channel determined by id from enum T_CHANNELS. It contains switch-case statement with hardcoded action what channel should be generated. It does not actully generate the channel, only call the function witch does.
 *
 * @param id ID from T_CHANNELS enum to determine requested channel
 */
void RF_DataSample::generateChannel(int id)
{
    switch (id)
    {
        case T_CHANNEL_RGB:
            break;
        case T_CHANNEL_HSV:
            this->createHSVChannel();
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
        case T_CHANNEL_H:
            this->createHueChannel();
            break;
        case T_CHANNEL_S:
            this->createSaturationChannel();
            break;
        case T_CHANNEL_LBP:
            this->createLBPChannel();
            break;
        default:
            return;
    }
}

/**
 * Generate grayscale channel from the original rgb channel and store it
 */
void RF_DataSample::createGrayscaleChannel()
{
    Mat gray(this->_channel[T_CHANNEL_RGB].rows, this->_channel[T_CHANNEL_RGB].cols, CV_8UC1);
    cvtColor(this->_channel[T_CHANNEL_RGB], gray, CV_BGR2GRAY);
    this->_channel[T_CHANNEL_GRAY] = gray;
}

/**
 * Generate only red channel from the original rgb channel and store it
 * @todo add Mat size preallocation
 */
void RF_DataSample::createRedChannel()
{
    Mat channel[3];

    split(this->_channel[T_CHANNEL_RGB], channel); //order BGR

    Mat ch(this->_channel[T_CHANNEL_RGB].rows, this->_channel[T_CHANNEL_RGB].cols, CV_8UC1);
    channel[0].convertTo(ch, CV_8UC1);
    this->_channel[T_CHANNEL_R] = ch;
}

/**
 * Generate only green channel from the original rgb channel and store it
 * @todo add Mat size preallocation
 */
void RF_DataSample::createGreenChannel()
{
    Mat channel[3];

    split(this->_channel[T_CHANNEL_RGB], channel); //order BGR

    Mat ch(this->_channel[T_CHANNEL_RGB].rows, this->_channel[T_CHANNEL_RGB].cols, CV_8UC1);
    channel[1].convertTo(ch, CV_8UC1);
    this->_channel[T_CHANNEL_G] = ch;
}

/**
 * Generate only blue channel from the original rgb channel and store it
 * @todo add Mat size preallocation
 */
void RF_DataSample::createBlueChannel()
{
    Mat channel[3];

    split(this->_channel[T_CHANNEL_RGB], channel); //order BGR

    Mat ch(this->_channel[T_CHANNEL_RGB].rows, this->_channel[T_CHANNEL_RGB].cols, CV_8UC1);
    channel[2].convertTo(ch, CV_8UC1);
    this->_channel[T_CHANNEL_B] = ch;
}

/**
 * Generate HSV image
 */
void RF_DataSample::createHSVChannel()
{
    Mat hsv(this->_channel[T_CHANNEL_RGB].rows, this->_channel[T_CHANNEL_RGB].cols, CV_8UC3);
    cvtColor(this->_channel[T_CHANNEL_RGB], hsv, CV_BGR2HSV);
    this->_channel[T_CHANNEL_HSV] = hsv;
}

/**
 * Generate hue channel from HSV image
 * @todo add Mat size preallocation
 */
void RF_DataSample::createHueChannel()
{
    Mat channel[3];

    split(this->_channel[T_CHANNEL_HSV], channel); //order HSV

    Mat ch(this->_channel[T_CHANNEL_HSV].rows, this->_channel[T_CHANNEL_HSV].cols, CV_8UC1);
    channel[0].convertTo(ch, CV_8UC1);
    this->_channel[T_CHANNEL_H] = ch;
}

/**
 * Generate saturation channel from HSV image
 * @todo add Mat size preallocation
 */
void RF_DataSample::createSaturationChannel()
{
    Mat channel[3];

    split(this->_channel[T_CHANNEL_HSV], channel); //order HSV

    Mat ch(this->_channel[T_CHANNEL_RGB].rows, this->_channel[T_CHANNEL_RGB].cols, CV_8UC1);
    channel[1].convertTo(ch, CV_8UC1);
    this->_channel[T_CHANNEL_S] = ch;
}


/**
 * Generate LBP channel from grayscale image
 * @todo implement more efficiently and invariantly to rotation
 */
void RF_DataSample::createLBPChannel()
{
    Mat lbp = Mat(this->_channel[T_CHANNEL_GRAY].rows, this->_channel[T_CHANNEL_GRAY].cols, CV_8U, 0.0);

    // Doplnte vypocet LBP pro kazdy pixel sedotonoveho obrazu greyImage a vysledek ulozte do lbp.
    // Iplementujte zakladni verzi LBP na okoli 3x3 pixelu, ktera produkuje 8-bit kod.
    // Popis zakladni verze LBP najdete napriklad v:
    // Topi Maenpaa: THE LOCAL BINARY PATTERN APPROACH TO TEXTURE ANALYSIS  EXTENSIONS AND APPLICATIONS, http://herkules.oulu.fi/isbn9514270762/
    // Look at page 26 - 2.5.1 The original LBP

    uchar threshold;
    uchar tmp;
    for (int y = 1; y < this->_channel[T_CHANNEL_GRAY].rows - 1; y++)
    {
        for (int x = 1; x < this->_channel[T_CHANNEL_GRAY].cols - 1; x++)
        {
            threshold = this->_channel[T_CHANNEL_GRAY].at<uchar>(y, x);

            tmp = 0;

            if (this->_channel[T_CHANNEL_GRAY].at<uchar>(y - 1, x - 1) >= threshold)
                tmp += 128;
            if (this->_channel[T_CHANNEL_GRAY].at<uchar>(y, x - 1) >= threshold)
                tmp += 64;
            if (this->_channel[T_CHANNEL_GRAY].at<uchar>(y + 1, x - 1) >= threshold)
                tmp += 32;
            if (this->_channel[T_CHANNEL_GRAY].at<uchar>(y - 1, x) >= threshold)
                tmp += 16;
            if (this->_channel[T_CHANNEL_GRAY].at<uchar>(y + 1, x) >= threshold)
                tmp += 8;
            if (this->_channel[T_CHANNEL_GRAY].at<uchar>(y - 1, x + 1) >= threshold)
                tmp += 4;
            if (this->_channel[T_CHANNEL_GRAY].at<uchar>(y, x + 1) >= threshold)
                tmp += 2;
            if (this->_channel[T_CHANNEL_GRAY].at<uchar>(y + 1, x + 1) >= threshold)
                tmp += 1;

            lbp.at<uchar>(y, x) = tmp;
        }
    }
    this->_channel[T_CHANNEL_LBP] = lbp;
}


/**
 * Create Histogram of LBP in area 7x7 around every point
 */
void RF_DataSample::createHOLBP7Channel()
{
return;
}


/**
 * Evaluate result. Compare given result DataSample and compare its label with the original one.
 *
 * @param ds DataSample of the result of the classification
 * @return Float value representing percentual similarity of given and real
 */
float RF_DataSample::getSimilarityOflabels(RF_DataSample *ds)
{
    if (this->_label.cols != ds->getLabel().cols || this->_label.rows != ds->getLabel().rows)
    {
        cerr << "Error, these two samples aren't same!" << endl;
        return 0.0f;
    }

    uint sum = 0;
    uint count = 0;

    for (int y = 0; y < this->_label.rows; y++)
    {
        for (int x = 0; x < this->_label.cols; x++)
        {
            if (this->_label.at<Vec3b>(y, x) == Vec3b(0, 0, 0))
                continue;

            if (this->_label.at<Vec3b>(y, x) == ds->_label.at<Vec3b>(y, x))
            {
                sum++;
            }
            count++;
        }
    }

    return (float) sum / (float) count * 100;
}

