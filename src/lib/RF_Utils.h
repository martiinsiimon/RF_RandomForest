/*
 * File:   RF_Utils.h
 * Author: Martin Simon <martiinsiimon@gmail.com>
 */

#ifndef RF_UTILS_H
#define	RF_UTILS_H

#include <string>
#include <sstream>

/* Hardcoded constant. TODO: make them user defined variables */
#define RF_MAX_DEPTH 8
#define RF_MAX_TREES 8
#define RF_N 3
#define RF_REC_W 5
#define RF_REC_H 5

using namespace std;

enum T_CHANNELS
{
    T_CHANNEL_RGB = 0, // original color image
    T_CHANNEL_GRAY, // grayscale channel
    T_CHANNEL_R, // red color channel
    T_CHANNEL_G, // green color channel
    T_CHANNEL_B, // blue color channel
    T_CHANNEL_HSV, // original image in HSV color model
    T_CHANNEL_H, // hue color channel (HSV)
    T_CHANNEL_S, // saturation color channel (HSV)
    T_CHANNEL_LAST, //sentinel
    T_CHANNEL_LBP, // rotation invariant local binary pattern (8-neighbourhood)
    T_CHANNEL_SOBEL_H, // horizontal sobel filter response
    T_CHANNEL_SOBEL_V, // vertical sobel filter response
    T_CHANNEL_HOLBP21, // histogram of LBP 21x21
    T_CHANNEL_HOLBP13, // histogram of LBP 13x13
    T_CHANNEL_HOLBP7, // histogram of LBP 7x7
};

template <typename T>
string Number2String(T i)
{
    ostringstream ss;
    ss << i;
    return ss.str();
}

template <typename T>
inline T String2Number(const string& st)
{
    T t;
    istringstream(st) >> t;
    return t;
}

#endif	/* RF_UTILS_H */

