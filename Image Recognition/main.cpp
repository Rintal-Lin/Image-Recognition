//
//  main.c
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 16, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dataStructs.h"
#include "borderDetector.h"
#include "imagePreProcessing.h"
#include "fontLibrary.h"
#include "imageComparision.h"
#include "bitOperations.h"
#include "string.h"
#include "patternRecognition.h"
#include "componentsDatabase.h"
#include "inclineProcessing.h"
#include "windows.h"
u8 rawData[gHeight][gWidth/8]={0};

//format of files£ºno LFs£¬all data in a line¡£
void readData() {
    FILE *fp;
    fp = fopen("../recognition/chips_sample.txt","r");
    for(int i=0;i<gHeight;i++) {
        for(int j=0;j<gWidth;j++) {
            char temp = 0;
            temp=fgetc(fp);
            if(temp == '1') setBit(rawData[0], gWidth, gHeight, i, j);
        }
    }
    fclose(fp);
}
//'print' image
void printData(u8 * data,int height,int width) {
    for(int i=0;i<height;i++) {
        for(int j=0;j<width;j++) {
            printf("%d",readBit(data, width, height, i, j, 0));
        }
        printf("\n");
    }
}

//print subimage
void printChild(u8 * binImage,int height,int width,int count,linkList * ll) {
    LNode * p;
    p = ll -> first;
    while(p != NULL) {
        printf("%d\t",p->data[0]);
        printf("%d\t",p->data[1]);
        printf("%d\t",p->data[2]);
        printf("%d\t\n",p->data[3]);
        for(int j=0;j<p->data[2];j++) {
            for(int k=0;k<p->data[3];k++)
                printf("%d",readBit(binImage,width,height,j+p->data[0],k+p->data[1], 0));
            printf("\n");
        }
        p = p->next;
    }
    printf("\n\n");
}
int main(int argc, const char * argv[]) {
    readData();
    u8 * filtered = createImage(gWidth, gHeight);
    noiseFilter(rawData[0], filtered, gHeight, gWidth);
    u8 * edged = createImage(gWidth, gHeight);
    edgeDetector(filtered, edged, gWidth, gHeight);
    short * marked = (short *)malloc(gWidth*gHeight*sizeof(short));
    memset(marked,0,gWidth*gHeight*sizeof(short));
    int count = ConnectedComponentLabeling(edged,gWidth,gHeight,marked);
    linkList res;
    res.first = NULL;
    res.last = NULL;
    findReligion(marked,gWidth,gHeight,count,&res,0,filtered,gWidth,gHeight);
    
    float ang = inclineDetector(&res);
   
    u8 * rotated = createImage(gWidth, gHeight);
    rotation(filtered, rotated, gWidth, gHeight, ang);//whether rotate the subimage only
    memset(edged,0,gWidth*gHeight/8);
    edgeDetector(rotated, edged, gWidth, gHeight);
  
    memset(marked,0,gWidth*gHeight*sizeof(short));
    count = ConnectedComponentLabeling(edged,gWidth,gHeight,marked);
    DeleteList(&res);
    res.first = NULL;
    res.last = NULL;
    int n = findReligion(marked,gWidth,gHeight,count,&res,0,rotated,gWidth,gHeight);
   
    char * result = image2Text(rotated, gWidth, gHeight, &res, n, fontSize, fontIndex, charIndex);
  
    DeleteList(&res);
    free(edged);
    free(filtered);
    free(marked);
    free(rotated);
    printf("After incline emendation, the recognition result is: \n%s\n", result);
    printf("Finally, we consider this chip would be: %s\n",db[search(result, db, dbSize)]);
    free(result);
    
	system("pause");
    return 1;
}