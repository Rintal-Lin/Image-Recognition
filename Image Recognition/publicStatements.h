//
//  publicStatements.h
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 16, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//

#ifndef surfaceIdentifier_publicStatements_h
#define surfaceIdentifier_publicStatements_h
typedef struct QNode
{
    int data;
    struct QNode *next;
}QNode;
//use queue structure
typedef struct Queue
{
    struct QNode* first;
    
    struct QNode* last;
}Queue;

//define nodes
typedef struct LNode
{
    int data[4];
    struct LNode *next;
}LNode;

//use chain structure
typedef struct linkList
{
    struct LNode* first;
    
    struct LNode* last;
}linkList;
typedef unsigned char u8;
#define PI 3.1415926535
#define fontSize 36
#define fontWidth 24
#define fontHeight 30
#define gHeight 240
#define gWidth 320
#define lowThreshold 10
#define highThreshold 50
#endif
