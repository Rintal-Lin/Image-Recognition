//
//  bitOperations.h
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 17, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//

#ifndef surfaceIdentifier_bitOperations_h
#define surfaceIdentifier_bitOperations_h



#endif
u8 * createImage(int width, int height);
u8 readBit(u8 * data, int width, int height, int x, int y, int offset);
void setBit(u8 * data, int width, int height, int x, int y);
void resetBit(u8 * data, int width, int height, int x, int y);