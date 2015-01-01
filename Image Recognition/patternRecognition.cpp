//
//  schema.c
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 17, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "patternRecognition.h"

float levenshteinRatio (const char * word1,const char * word2) {
    int len1 = (int)strlen(word1);
    int len2 = (int)strlen(word2);
    int ** matrix = (int **)malloc((len1+1)*sizeof(int *));
    int * elements = (int *)malloc((len1+1)*(len2+1)*sizeof(int));
    memset(elements,0,(len1+1)*(len2+1)*sizeof(int));
    int j=0;
    for(int i=0;i<len1+1;i++) {
        matrix[i]=&elements[j];
        j+=len2+1;
    }
    int i;
    for (i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }
    for (i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }
    for (i = 1; i <= len1; i++) {
        int j;
        char c1;
        
        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;
            
            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                int del;
                int insert;
                int substitute;
                int minimum;
                
                del = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = del;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    float result = 1 - (float)matrix[len1][len2]/(len1 > len2 ? len1 : len2);
    free(elements);
    free(matrix);
    return result;
}
int search(char * label,char * database[], int dbsize) {
    float curRatio = 0;
    int id = 0;
    float total = 0;
    float * ratio = (float *)malloc(dbsize*sizeof(float));
    for(int i=0;i<dbsize;i++) {
        float ra = levenshteinRatio(label,database[i]);
        total += ra;
        ratio[i] = ra;
        if(ra > curRatio) {
            curRatio = ra;
            id = i;
        }
    }
    float mean = total/dbsize;
    total = 0;
    for(int i=0;i<dbsize;i++) {
        total += (ratio[i]-mean)*(ratio[i]-mean);
    }
    float stdDiv = sqrt(total/dbsize);
   
    //下面使用拉依达准则
    free(ratio);
    if(curRatio > mean+2*stdDiv) return id;
    else return -1;
}
