//
//  dataStructs.c
//  surfaceIdentifier
//
//  Created by Tao Lin and Justin Jewcci on 15, July.
//  Copyright (c) 2013 Tao Lin and Justin Jewcci | All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"

int PopQueue(Queue *queue)
{
    QNode *p = NULL;
    int data;
    if(queue->first == NULL)
    {
        return -1;
    }
    p = queue->first;
    data = p->data;
    if(queue->first->next == NULL)
    {
        queue->first = NULL;
        queue->last = NULL;
    }
    else
    {
        queue->first = p->next;
    }
    free(p);
    return data;
}
void PushQueue(Queue *queue, int data)
{
    QNode *p = NULL;
    p = (QNode*)malloc(sizeof(QNode));
    p->data = data;
    if(queue->first == NULL)
    {
        queue->first = p;
        queue->last = p;
        p->next = NULL;
    }
    else
    {
        p->next = NULL;
        queue->last->next = p;
        queue->last = p;
    }
}
void InsertList(linkList *ll, int data[4])
{
    LNode *p = NULL;
    p = (LNode*)malloc(sizeof(LNode));
    p->data[0] = data[0];
    p->data[1] = data[1];
    p->data[2] = data[2];
    p->data[3] = data[3];
    if(ll->first == NULL)
    {
        ll->first = p;
        ll->last = p;
        p->next = NULL;
    }
    else
    {
        p->next = NULL;
        ll->last->next = p;
        ll->last = p;
    }
}
void InsertNode(LNode *ln, int edata[4])//Insert algorithm
{
    LNode * newnode =(LNode*)malloc(sizeof(LNode));
    newnode->data[0] = edata[0];
    newnode->data[1] = edata[1];
    newnode->data[2] = edata[2];
    newnode->data[3] = edata[3];
    newnode->next=ln->next;
    ln->next=newnode;
}
void delNode(LNode *q) //delete function
{
	LNode *newnode;
	newnode=q->next;
	q->data[0] = q->next->data[0];
    q->data[1] = q->next->data[1];
    q->data[2] = q->next->data[2];
    q->data[3] = q->next->data[3];
	q->next=q->next->next;
	free(newnode);
}
void DeleteList(linkList *ll)//destroy link
{
    LNode* tmp;
    tmp =ll->first;
    while(tmp!=NULL)
    {
        
        ll->first = tmp->next;
        free(tmp);
        tmp=ll->first;
    }
}