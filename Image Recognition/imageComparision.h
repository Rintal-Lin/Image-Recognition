//
//  imageComparision.h
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 16, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//

#ifndef surfaceIdentifier_imageComparision_h
#define surfaceIdentifier_imageComparision_h



#endif
#include "publicStatements.h"
float imageComparision(u8 * imageIn, int width, int height,int xoffset, int yoffset, int cwidth, int cheight, u8 * fontIn);
char * image2Text (u8 * rawImage, int width, int height, linkList * res, int n, int fontsize, u8 ** fontindex, char * charindex);
