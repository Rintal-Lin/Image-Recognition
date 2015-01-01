//
//  imagePreProcessing.c
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 15, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "imagePreProcessing.h"
#include "bitOperations.h"
//immature noise filter
void noiseFilter(u8 * imageIn,u8 * image,int height,int width) {
    memcpy(image, imageIn, height*width/8);
    for(int i=1;i<height-1;i++) {
        for(int j=1;j<width-1;j++) {
            if(readBit(image, width, height, i, j, 0)==0) {
                if(readBit(image, width, height, i-1, j-1, 0)+readBit(image, width, height, i-1, j, 0)+readBit(image, width, height, i-1, j+1, 0)+readBit(image, width, height, i, j-1, 0)+readBit(image, width, height, i, j+1, 0)+readBit(image, width, height, i+1, j-1, 0)+readBit(image, width, height, i+1, j, 0)+readBit(image, width, height, i+1, j+1, 0)>4) setBit(image, width, height, i, j);
            }
        }
    }
    for(int i=1;i<height-1;i++) {
        for(int j=1;j<width-1;j++) {
            if(readBit(image, width, height, i, j, 0)==0) {
                if(readBit(image, width, height, i-1, j-1, 0)+readBit(image, width, height, i-1, j, 0)+readBit(image, width, height, i-1, j+1, 0)+readBit(image, width, height, i, j-1, 0)+readBit(image, width, height, i, j+1, 0)+readBit(image, width, height, i+1, j-1, 0)+readBit(image, width, height, i+1, j, 0)+readBit(image, width, height, i+1, j+1, 0)>4) setBit(image, width, height, i, j);
            }
        }
    }
}
void bolden(u8 * imageIn, u8 * image, int height, int width,int xoffset, int yoffset) {  //以黑点为中心判断八领域黑点个数，超过阈值全部变成黑点
    memcpy(image, imageIn, height*width/8);
    for(int i=1;i<height-1;i+=3) {
        for(int j=1;j<width-1;j+=3) {
            int sum = readBit(image, width, height, i+yoffset-1, j+xoffset-1, 0)+readBit(image, width, height, i+yoffset-1, j+xoffset, 0)+readBit(image, width, height, i+yoffset-1, j+xoffset+1, 0)+readBit(image, width, height, i+yoffset, j+xoffset-1, 0)+readBit(image, width, height, i+yoffset, j+xoffset+1, 0)+readBit(image, width, height, i+yoffset+1, j+xoffset-1, 0)+readBit(image, width, height, i+yoffset+1, j+xoffset, 0)+readBit(image, width, height, i+yoffset+1, j+xoffset+1, 0);
            if(sum<4) {
                resetBit(image, width, height, i+yoffset, j+xoffset);
                resetBit(image, width, height, i+yoffset+1, j+xoffset);
                resetBit(image, width, height, i+yoffset, j+xoffset+1);
                resetBit(image, width, height, i+yoffset+1, j+xoffset+1);
                resetBit(image, width, height, i+yoffset-1, j+xoffset-1);
                resetBit(image, width, height, i+yoffset-1, j+xoffset);
                resetBit(image, width, height, i+yoffset+1, j+xoffset-1);
                resetBit(image, width, height, i+yoffset, j+xoffset-1);
                resetBit(image, width, height, i+yoffset-1, j+xoffset+1);
            }
            else {
                setBit(image, width, height, i+yoffset, j+xoffset);
                setBit(image, width, height, i+yoffset+1, j+xoffset);
                setBit(image, width, height, i+yoffset, j+xoffset+1);
                setBit(image, width, height, i+yoffset+1, j+xoffset+1);
                setBit(image, width, height, i+yoffset-1, j+xoffset-1);
                setBit(image, width, height, i+yoffset-1, j+xoffset);
                setBit(image, width, height, i+yoffset+1, j+xoffset-1);
                setBit(image, width, height, i+yoffset, j+xoffset-1);
                setBit(image, width, height, i+yoffset-1, j+xoffset+1);
            }
        }
    }
}
