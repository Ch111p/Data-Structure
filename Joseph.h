#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Nodea{
    int id;
    int secret;
    struct Nodea* next; 
    struct Nodea* last;
}Node,*pNode;

pNode initNode(int num){
    pNode node = (pNode)malloc(sizeof(Node));
    pNode subNode = node;
    for(int i = 0;i < num - 1;i++){
        node->next = (pNode)malloc(sizeof(Node));
        node->next->last = node;
        node->id = i + 1;
        node = node->next;
    }
    node->next = subNode;
    subNode->last = node;
    node->id = num;
    node = node->next;
    return node;
}

void deleteNode(pNode node){
    node->next->last = node->last;
    node->last->next = node->next;
    memset(node,0,sizeof(Node));
    free(node);
}

int listLength(pNode head){
    pNode subNode = head;
    int num = 1;
    for(;head->next != subNode;head = head->next,num++);
    return num;
}

bool insertNode(pNode head,pNode node,int loc){
    if(loc == 0 || loc > listLength(head)){
        return FALSE;
    }
    for(int i = 1;i < loc;i++){
        head = head->next;
    }
    head->last->next = node;
    node->last = head->last;
    node->next = head;
    head->last = node;
    return TRUE;
}

void deleteAllNode(pNode head){
    pNode subNode = head;
    while(head->next != subNode){
        pNode node = head;
        head = head->next;
        memset(node,0,sizeof(Node));
        free(node);
    }
    memset(head,0,sizeof(Node));
    free(head);
}

void showNode(pNode head,int num){
    for(int i = 0;i < num;i++){
        head = head->next;
    }
    printf("%d",head->secret);
}