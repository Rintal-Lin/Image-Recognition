//
//  inclineProcessing.c
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 6, August.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//

#include <stdio.h>
#include "inclineProcessing.h"
#include <math.h>
#include "bitOperations.h"
#include "string.h"
float inclineDetector(linkList * ll) {     //outcome is rad
    LNode * p;
    p = ll -> first;
    float k=0, r=0;
    while(p!=NULL) {
        if(p->data[2]==0 || p->data[3]==0) {
            p=p->next;
            continue;
        }
        float sx=0, sy=0;
        int n=0;
        LNode * start = p;
        while(p!=NULL && p->data[2]!=0 && p->data[3]!=0) {
            sx += (float)p->data[1]+(float)p->data[3]/2;
            sy += (float)p->data[0]+(float)p->data[2]/2;
         
            n++;
            p = p->next;
        }
        p = start;
        float ax = sx/n, ay = sy/n;
        float sum1=0,sum2=0,sum3=0;
        while(p!=NULL && p->data[2]!=0 && p->data[3]!=0) {
            sum1 += (((float)p->data[1]+(float)p->data[3]/2)-ax)*(((float)p->data[0]+(float)p->data[2]/2)-ay);
            sum2 += (((float)p->data[1]+(float)p->data[3]/2)-ax)*(((float)p->data[1]+(float)p->data[3]/2)-ax);
            sum3 += (((float)p->data[0]+(float)p->data[2]/2)-ay)*(((float)p->data[0]+(float)p->data[2]/2)-ay);
            p=p->next;
        }
        if(sum1/(sqrt(sum2)*sqrt(sum3))*sum1/(sqrt(sum2)*sqrt(sum3)) > r) {
            r = sum1/(sqrt(sum2)*sqrt(sum3))*sum1/(sqrt(sum2)*sqrt(sum3));
            k = sum1/sum2;
        }
        if(p!=NULL) p=p->next;
    }
   
    return atan(k);
}
void rotation(u8 * raw, u8 * res, int width, int height, float angle) {
    float vcos = cos(angle);
    float vsin = sin(angle);
    memset(res,255,width*height/8);
    for(int i=0;i<height;i++) {
        for(int j=0;j<width;j++) {
            //rotation formula£º
            //x'= (x - rx0)*cos(RotaryAngle) + (y - ry0)*sin(RotaryAngle) + rx0
            //y'= =-(x - rx0)*sin(RotaryAngle) + (y - ry0)*cos(RotaryAngle) + ry0
            if(readBit(raw, width, height, i, j, 0) == 0) resetBit(res, width, height, -(j-width/2)*vsin+(i-height/2)*vcos+height/2, (j-width/2)*vcos+(i-height/2)*vsin+width/2);
        }
    }
}
void religionRotation(linkList * ll,float angle,int width, int height) {
    float vcos = cos(angle);
    float vsin = sin(angle);
    LNode * p = ll->first;
    while (p!=NULL) {
        if(p->data[2]!=0 && p->data[3]!=0) {
            int sx = p->data[1],sy = p->data[0];
            int ex = p->data[1]+p->data[3], ey = p->data[0]+p->data[2];
            int nsx = (sx-width/2)*vcos + (sy-height/2)*vsin+width/2;
            int nsy = -(sx-width/2)*vsin + (sy-height/2)*vcos+height/2;
            int nex = (ex-width/2)*vcos + (ey-height/2)*vsin+width/2;
            int ney = -(ex-width/2)*vsin + (ey-height/2)*vcos+height/2;
            p->data[0] = nsy;
            p->data[1] = nsx;
            p->data[2] = ney-nsy;
            p->data[3] = nex-nsx;
        }
        p=p->next;
    }
}