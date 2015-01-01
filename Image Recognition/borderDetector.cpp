//
//  borderDetector.c
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 15, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "borderDetector.h"
#include "dataStructs.h"
#include "bitOperations.h"
#include "string.h"
#include "math.h"
//detection function of 8-neighborhood mark of binary image 
static int NeighborDirection[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
//edge detection of binary images
void edgeDetector(u8 * image,u8 * bianyuan,int width, int height)
{
    for(int i=1;i<height-1;i++)
        for(int j=1;j<width-1;j++)
        {
            if(readBit(image, width, height, i, j, 0) == 0) {
                int t = readBit(image, width, height, i-1, j, 0)+readBit(image, width, height, i+1, j, 0)+readBit(image, width, height, i, j-1, 0)+readBit(image, width, height, i, j+1, 0);
                if(t > 0 && t < 4)/*among 1-3*/
                    setBit(bianyuan, width, height, i, j);
            }
        }
}
void SearchNeighbor(u8 *bitmap, int width, int height, short *labelmap, int labelIndex, int pixelIndex, Queue *queue)
{
    int searchIndex;
    labelmap[pixelIndex] = labelIndex;
    for(int i = 0;i < 8;i++)
    {
        searchIndex = pixelIndex + NeighborDirection[i][0] * width + NeighborDirection[i][1];
        int cx = searchIndex % width;
        int cy = searchIndex / width;
        if(cx>=0 && cx<width && cy >=0 && cy < height &&
           readBit(bitmap, width, height, searchIndex/width, searchIndex%width, 0) == 1 && labelmap[searchIndex] == 0)
        {
            labelmap[searchIndex] = labelIndex;
            PushQueue(queue, searchIndex);
        }
    }
}
//connected domain mark funtion
int ConnectedComponentLabeling(u8 *binaryImage, int width, int height, short *labeImage)
{
    int popIndex , labelIndex = 0;
    Queue *queue = NULL;
    queue = (Queue*)malloc(sizeof(Queue));
    queue->first = NULL;
    queue->last = NULL;
    /*memset(labelmap, 0, width * height);*/
    for(int cy = 1; cy < height - 1; cy++)
    {
        for(int cx = 1; cx < width - 1; cx++)
        {
            if(readBit(binaryImage, width, height, cy, cx, 0) == 1 && *(labeImage+cy*width+cx) == 0)
            {
                labelIndex++;
                SearchNeighbor(binaryImage, width, height, labeImage, labelIndex, cy*width+cx, queue);
                popIndex = PopQueue(queue);
                while(popIndex > -1)
                {
                    SearchNeighbor(binaryImage, width, height, labeImage, labelIndex, popIndex, queue);
                    popIndex = PopQueue(queue);
                }
            }
        }
    }
    free(queue);
    return labelIndex;
}
int findReligion(short * mapIn,int width,int height,int count,linkList * ll,int isChild, u8 * rawImage, int rawWidth, int rawHeight) {
    int ** temp;
    int * elements;
    temp = (int **)malloc(sizeof(int *)*count);
    elements=(int *)malloc(count*5*sizeof(int));
    int j=0;
    for(int i=0;i<count;i++) {
        temp[i]=&elements[j];
        j+=5;
    }
    for(int i=0;i<count;i++) {
        temp[i][0]=30000;
        temp[i][1]=30000;
        temp[i][2]=0;
        temp[i][3]=0;
        temp[i][4]=0;
    }
    for(int i=0;i<height;i++) {
        for(int j=0;j<width;j++) {
            if(*(mapIn+j+i*width)!=0 && temp[*(mapIn+j+i*width)-1][0]>i) temp[*(mapIn+j+i*width)-1][0]=i;
            if(*(mapIn+j+i*width)!=0 && temp[*(mapIn+j+i*width)-1][1]>j) temp[*(mapIn+j+i*width)-1][1]=j;
        }
    }
    for(int i=0;i<height;i++) {
        for(int j=0;j<width;j++) {
            if(*(mapIn+j+i*width)!=0 && temp[*(mapIn+j+i*width)-1][2]<i-temp[*(mapIn+j+i*width)-1][0]) temp[*(mapIn+j+i*width)-1][2]=i-temp[*(mapIn+j+i*width)-1][0];
            if(*(mapIn+j+i*width)!=0 && temp[*(mapIn+j+i*width)-1][3]<j-temp[*(mapIn+j+i*width)-1][1]) temp[*(mapIn+j+i*width)-1][3]=j-temp[*(mapIn+j+i*width)-1][1];
        }
    }
    int n = 0;
    for(int i=0;i<count;i++) {
        if(temp[i][2]<=2*lowThreshold || temp[i][3]<=lowThreshold || temp[i][2]>=highThreshold || temp[i][3]>=highThreshold) {
            temp[i][4]=1;
            n++;
        } //Delete tag
    }
    for(int i=0;i<count;i++) {
        if(temp[i][4]!=1) {
            for(int j=0;j<count;j++) {
                if(temp[j][4]!=1) {
                    if(temp[i][0]<temp[j][0] && temp[i][1]<temp[j][1] && temp[i][2]>temp[j][2]+temp[j][0]-temp[i][0] && temp[i][3]>temp[j][3]+temp[j][1]-temp[i][1]) {
                        temp[j][4]=1;
                        n++;
                    }
                }
            }
        }
    }
    if(count-n == 0) {
        free(elements);
        free(temp);
        return 0;
    }
    int ** result = (int **)malloc(sizeof(int *)*(count-n));
    for(int i=0;i<count-n;i++) {
        result[i]=(int *)malloc(sizeof(int)*4);
    }
    int m=0;
    for(int i=0;i<count;i++) {
        if(temp[i][4]!=1){
            result[m][0]=temp[i][0];
            result[m][1]=temp[i][1];
            result[m][2]=temp[i][2]+1;
            result[m][3]=temp[i][3]+1;
            m++;
        }
    }
    for(int i=0;i<m;i++) {
        int s1=0,s2=0,s3=0,s4=0,s5=0,s6=0,s7=0,s8=0;
        for(int j=0;j<result[i][2];j++) s1+=!readBit(rawImage, rawWidth, rawHeight, result[i][0]+j, result[i][1], 0);
        for(int j=0;j<result[i][2];j++) s2+=!readBit(rawImage, rawWidth, rawHeight, result[i][0]+j, result[i][1]+result[i][3]-1, 0);
        for(int j=0;j<result[i][3];j++) s3+=!readBit(rawImage, rawWidth, rawHeight, result[i][0], result[i][1]+j, 0);
        for(int j=0;j<result[i][3];j++) s4+=!readBit(rawImage, rawWidth, rawHeight, result[i][0]+result[i][2]-1, result[i][1]+j, 0);
        for(int j=0;j<result[i][2];j++) s5+=!readBit(rawImage, rawWidth, rawHeight, result[i][0]+j, result[i][1]+1, 0);
        for(int j=0;j<result[i][2];j++) s6+=!readBit(rawImage, rawWidth, rawHeight, result[i][0]+j, result[i][1]+result[i][3]-2, 0);
        for(int j=0;j<result[i][3];j++) s7+=!readBit(rawImage, rawWidth, rawHeight, result[i][0]+1, result[i][1]+j, 0);
        for(int j=0;j<result[i][3];j++) s8+=!readBit(rawImage, rawWidth, rawHeight, result[i][0]+result[i][2]-2, result[i][1]+j, 0);
        if(!s1 || s5/s1>=5) result[i][1]++,result[i][3]--;
        if(!s2 || s6/s2>=5) result[i][3]--;
        if(!s3 || s7/s3>=5) result[i][0]++,result[i][2]--;
        if(!s4 || s8/s4>=5) result[i][2]--;
    }
    if(isChild) {
        free(elements);
        free(temp);
        for(int i=0;i<m;i++) InsertList(ll, result[i]);
        for(int i=0;i<m;i++) {
            free(result[i]);
        }
        free(result);
        return m;
    }
    int sum = 0;
    for(int i=0;i<m;i++) {
        sum+=result[i][2];
    }
    int lineThreshold = (sum/m)*0.5;
    sum = 0;
    for(int i=0;i<m;i++) {
        sum+=result[i][3];
    }
    int widthavg = sum/m;
    int start = 0;
    for(int i=0;i<m-1;i++) {
        if(result[i+1][0]-result[i][0]>lineThreshold){
            for(int j=start;j<i;j++) {
                for(int k=start;k<start+i-j;k++) {
                    if(result[k+1][1]<result[k][1]) {
                        int t;
                        t=result[k][0];
                        result[k][0]=result[k+1][0];
                        result[k+1][0]=t;
                        t=result[k][1];
                        result[k][1]=result[k+1][1];
                        result[k+1][1]=t;
                        t=result[k][2];
                        result[k][2]=result[k+1][2];
                        result[k+1][2]=t;
                        t=result[k][3];
                        result[k][3]=result[k+1][3];
                        result[k+1][3]=t;
                    }
                }
            }
            start = i+1;
        }
        else if(i == m-2) {
            for(int j=start;j<i+1;j++) {
                for(int k=start;k<start+i+1-j;k++) {
                    if(result[k+1][1]<result[k][1]) {
                        int t;
                        t=result[k][0];
                        result[k][0]=result[k+1][0];
                        result[k+1][0]=t;
                        t=result[k][1];
                        result[k][1]=result[k+1][1];
                        result[k+1][1]=t;
                        t=result[k][2];
                        result[k][2]=result[k+1][2];
                        result[k+1][2]=t;
                        t=result[k][3];
                        result[k][3]=result[k+1][3];
                        result[k+1][3]=t;
                    }
                }
            }
        }
    }
    for(int i=0;i<m;i++) InsertList(ll, result[i]);
    
    free(elements);
    free(temp);
    for(int i=0;i<m;i++) {
        free(result[i]);
    }
    free(result);
    
    LNode * p;
    p = ll -> first;
    while(p != NULL && p->next != NULL) {
        if(p->next->data[1] - p->data[1] > widthavg * 2 && p->next->data[0] - p->data[0] < lineThreshold) {
            int cwidth = p->next->data[1]-p->data[1]-p->data[3];
            int bottommax = (p->data[2]+p->data[0]) >= (p->next->data[2]+p->next->data[0]) ? (p->data[2]+p->data[0]):(p->next->data[2]+p->next->data[0]);
            int topmin = ((p->data[0]) <= (p->next->data[0]) ? (p->data[0]):(p->next->data[0]));
            int cheight = bottommax - topmin;
            int xoffset = p->data[1]+p->data[3];
            int yoffset = p->data[0] <= p->next->data[0] ? p->data[0]:p->next->data[0];
            u8 * child = createImage(cwidth, cheight);
            for(int i=0;i<cheight;i++) {
                for(int j=0;j<cwidth;j++) {
                    if(readBit(rawImage, rawWidth, rawHeight, i+yoffset, j+xoffset, 0) == 1) setBit(child, cwidth, cheight, i, j);
                   
                }
                
            }
            u8 * edged = createImage(cwidth, cheight);
            edgeDetector(child,edged,cwidth,cheight);

            linkList temp;
            temp.first = NULL;
            temp.last = NULL;
            short * map = (short *)malloc(cwidth*cheight*sizeof(short));
            memset(map,0,cwidth*cheight*sizeof(short));
            int ccount = ConnectedComponentLabeling(edged,cwidth,cheight,map);
            int cm = findReligion(map, cwidth, cheight, ccount, &temp, 1,rawImage,rawWidth,rawHeight);
            if(cm) {
                m += cm;
                LNode * cp;
                cp = temp.first;
                while(cp != NULL) {
                    cp->data[0] = cp->data[0]+yoffset;
                    cp->data[1] = cp->data[1]+xoffset;
                    cp = cp->next;
                }
                temp.last->next = p->next;
                p->next = temp.first;
            }
            
            free(child);
            free(edged);
            free(map);
        }
        else if(p->next->data[0] - p->data[0] >= lineThreshold) {
            int tt[4] = {0};
            InsertNode(p, tt);
            m++;
            p = p->next;
        }
        p = p -> next;
    }
    return m;
}
