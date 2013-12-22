/*
 * File:   RF_Utils.h
 * Author: martin
 *
 * Created on 9. listopad 2013, 14:51
 */

#ifndef RF_UTILS_H
#define	RF_UTILS_H

/* Hardcoded constant. TODO: make them user defined variables */
#define RF_MAX_DEPTH 5
#define RF_MAX_TREES 5
#define RF_N 3
#define RF_REC_W 10
#define RF_REC_H 10

enum T_CHANNELS
{
    T_RGB = 0,
    T_GRAY,
    T_R,
    T_G,
    T_B,
    T_LAST //sentinel
};

#endif	/* RF_UTILS_H */

