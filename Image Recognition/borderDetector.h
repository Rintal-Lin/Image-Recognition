//
//  borderDetector.h
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 15, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//

#ifndef surfaceIdentifier_borderDetector_h
#define surfaceIdentifier_borderDetector_h



#endif
#include "publicStatements.h"
void SearchNeighbor(u8 *bitmap, int width, int height, short *labelmap, int labelIndex, int pixelIndex, Queue *queue);
int ConnectedComponentLabeling(u8 *binaryImage, int width, int height, short *labeImage);
int findReligion(short * mapIn,int width,int height,int count,linkList * ll,int isChild, u8 * rawImage, int rawWidth, int rawHeight);
void edgeDetector(u8 * image,u8 * bianyuan,int width, int height);