//
//  bitOperations.c
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 17, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "publicStatements.h"
#include "bitOperations.h"
#include "string.h"
#include "math.h"
u8 readBit(u8 * data, int width, int height, int x, int y, int offset) {
    if(x<0 || y<0 || x>=height || y>=width)
        return 0;
    u8 temp = *(data+y/8+(int)ceilf((float)width/8)*x+offset);
    switch (y%8) {
        case 0:
            temp = temp & 1;
            break;
        case 1:
            temp = (temp & 2)>>1;
            break;
        case 2:
            temp = (temp & 4)>>2;
            break;
        case 3:
            temp = (temp & 8)>>3;
            break;
        case 4:
            temp = (temp & 16)>>4;
            break;
        case 5:
            temp = (temp & 32)>>5;
            break;
        case 6:
            temp = (temp & 64)>>6;
            break;
        case 7:
            temp = (temp & 128)>>7;
            break;
    }
    return temp;
}
void setBit(u8 * data, int width, int height, int x, int y) {
    if(x<0 || y<0 || x>=height || y>=width)
        return;
    u8 temp = *(data+y/8+(int)ceilf((float)width/8)*x);
    switch (y%8) {
        case 0:
            temp = temp | 1;
            break;
        case 1:
            temp = temp | 2;
            break;
        case 2:
            temp = temp | 4;
            break;
        case 3:
            temp = temp | 8;
            break;
        case 4:
            temp = temp | 16;
            break;
        case 5:
            temp = temp | 32;
            break;
        case 6:
            temp = temp | 64;
            break;
        case 7:
            temp = temp | 128;
            break;
    }
    *(data+y/8+(int)ceilf((float)width/8)*x) = temp;
}
void resetBit(u8 * data, int width, int height, int x, int y) {
    if(x<0 || y<0 || x>=height || y>=width)
        return;
    u8 temp = *(data+y/8+(int)ceilf((float)width/8)*x);
    switch (y%8) {
        case 0:
            temp = temp & 254;
            break;
        case 1:
            temp = temp & 253;
            break;
        case 2:
            temp = temp & 251;
            break;
        case 3:
            temp = temp & 247;
            break;
        case 4:
            temp = temp & 239;
            break;
        case 5:
            temp = temp & 223;
            break;
        case 6:
            temp = temp & 191;
            break;
        case 7:
            temp = temp & 127;
            break;
    }
    *(data+y/8+(int)ceilf((float)width/8)*x) = temp;
}
u8 * createImage(int width, int height) {
    u8 * temp = (u8 *)malloc((int)ceilf((float)width/8)*height);
    memset(temp,0,(int)ceilf((float)width/8)*height);
   
    return temp;
}