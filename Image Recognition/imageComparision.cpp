//
//  imageComparision.c
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 16, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include "imageComparision.h"
#include "bitOperations.h"
#include <math.h>
#include "imagePreProcessing.h"

float imageComparision(u8 * imageIn, int width, int height,int xoffset, int yoffset, int cwidth, int cheight, u8 * fontIn) {  //∑µªÿœ‡À∆∂»
    float wratio = (float)fontIn[0]/cwidth;
    float hratio = (float)fontIn[1]/cheight;
    int counter = 0;
    for(int i=0;i<cheight;i++) {
        for(int j=0;j<cwidth;j++) {
            int tr = readBit(imageIn, width, height, i+yoffset, j+xoffset, 0);
            int tf = !readBit(fontIn, (int)fontIn[0], (int)fontIn[1], (int)((float)i*hratio), (int)((float)j*wratio), 3);
            if(tr == tf) {
                if(tr == 0) {
                    int w = readBit(imageIn, width, height, i+yoffset-1, j+xoffset-1, 0)+readBit(imageIn, width, height, i+yoffset-1, j+xoffset, 0)+readBit(imageIn, width, height, i+yoffset-1, j+xoffset+1, 0)+readBit(imageIn, width, height, i+yoffset, j+xoffset-1, 0)+readBit(imageIn, width, height, i+yoffset, j+xoffset+1, 0)+readBit(imageIn, width, height, i+yoffset+1, j+xoffset-1, 0)+readBit(imageIn, width, height, i+yoffset+1, j+xoffset, 0)+readBit(imageIn, width, height, i+yoffset+1, j+xoffset+1, 0);
                    if(w < 1)
                        counter+=2;
                    else if (w < 5) counter++;
                }
                else counter++;
            }
        }
    }
    return (float)counter/(cwidth*cheight);
}

float power(u8 * image, int width, int height, int xoffset, int yoffset, int cwidth, int cheight) {
    float * entropy = (float *)malloc(cheight*sizeof(float));
    for(int i=0;i<cheight;i++) {
        float ent=0;
        for(int j=0;j<cwidth;j++) {
            float pj = (float)(j+1)/(cwidth*(cwidth+1)/2);
            ent+=-(float)readBit(image, width, height, i+yoffset, j+xoffset, 0)*pj*log10f(pj);
        }
        entropy[i]=ent;
    }
    float max = 0;
    for(int i=0;i<cheight;i++) {
        if(entropy[i]>max) max = entropy[i];
    }
    for(int i=0;i<cheight;i++) {
        entropy[i]/=max;
        //printf("%f ",entropy[i]);
    }
    float * relative = (float *)malloc(cheight*sizeof(float));
    for(int i=0;i<cheight;i++) {
        float rel=0;
        for(int j=0;j<cheight;j++) {
            rel+=entropy[j]*entropy[(j+i)%cheight];
        }
        relative[i] = rel;
    }
    max = 0;
    for(int i=0;i<cheight;i++) {
        if(relative[i]>max) max = relative[i];
    }
    free(relative);
    free(entropy);
    return max;
}


char * image2Text (u8 * rawImage, int width, int height, linkList * res, int n, int fontsize, u8 ** fontindex, char * charindex) {
    LNode * p;
    p = res->first;
    char * temp = (char *)malloc(n*sizeof(char)+1);
    float * ratio = (float *)malloc(n*sizeof(float));
    for(int i=0;i<n;i++) ratio[i]=0;
    int ccounter = 0, rcounter = 0;
    float total = 0;
    while (p != NULL) {
        if(p->data[2] == 0 && p->data[3] == 0) {
            temp[ccounter] = '\n';
            ccounter++;
            p = p->next;
            continue;
        }
        float t = 0;
        int k = 0;
        for(int i=0;i<fontsize;i++) {
            float current = imageComparision(rawImage, width, height, p->data[1], p->data[0], p->data[3], p->data[2], fontindex[i]);
           
            if(current > t) {
                t = current;
                k = i;
            }
        }
       
        ratio[ccounter] = t;
        total += t;
        temp[ccounter] = charindex[k];
        p = p->next;
        ccounter ++;
        rcounter ++;
    }
    temp[ccounter] = '\0';
    float mean = total/rcounter;
    total = 0;
    for(int i=0;i<ccounter;i++) {
        if(ratio[i]!=0) total += (ratio[i]-mean)*(ratio[i]-mean);
    }
    float stdDiv = sqrt(total/rcounter);
    for(int i=0;i<ccounter;i++) {
        if(ratio[i]<mean-2*stdDiv && ratio[i]!=0) ratio[i] = -1;
    }
    char * result = (char *)malloc(n*sizeof(char)+1);
    rcounter = 0;
    for(int i=0;i<ccounter;i++) {
        if(ratio[i]+1 > 1e-2) {
            result[rcounter] = temp[i];
            rcounter++;
        }
    }
    result[rcounter]='\0';
    free(temp);
    free(ratio);
    return result;
}
