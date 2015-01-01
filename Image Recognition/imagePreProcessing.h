//
//  imagePreProcessing.h
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 15, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//

#ifndef surfaceIdentifier_imagePreProcessing_h
#define surfaceIdentifier_imagePreProcessing_h



#endif
#include "publicStatements.h"
void houghTransForm(unsigned char * imgBinaryIn,int width,int height,int *houghBuf,int houghWidth,int houghHeight,float radiusResolution,float angleResolution,float *radius,float *angle);
void noiseFilter(u8 * imageIn,u8 * image,int height,int width);
void sampleData(u8* rawData,u8 * data,int ratio,int width, int height);
void bolden(u8 * imageIn, u8 * image, int height, int width,int xoffset, int yoffset);