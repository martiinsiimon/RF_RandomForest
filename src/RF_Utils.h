/*
 * File:   RF_Utils.h
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:51
 */

#ifndef RF_UTILS_H
#define	RF_UTILS_H

#include <string>
#include <sstream>

/* Hardcoded constant. TODO: make them user defined variables */
#define RF_MAX_DEPTH 5
#define RF_MAX_TREES 5
#define RF_N 3
#define RF_REC_W 5
#define RF_REC_H 5

enum T_CHANNELS
{
    T_CHANNEL_RGB = 0,
    T_CHANNEL_GRAY,
    T_CHANNEL_R,
    T_CHANNEL_G,
    T_CHANNEL_B,
    T_CHANNEL_LAST //sentinel
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

