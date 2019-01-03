#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct info{
    char **name;
    char **shortInfo;
}typeInfo,*pTypeInfo;

typedef struct Form{
    typeInfo info;
    int* matrix;
    int vexNum;
    int edgeNum;
    bool* searchFlag;
}form,*pForm;

pForm initForm(int num){
    pForm head = (pForm)malloc(sizeof(form));
    head->edgeNum = 0;
    head->vexNum = num;
    head->matrix = (int*)malloc(sizeof(int) * num * num);
    head->info.name = (char**)malloc(sizeof(char*) * num);
    head->info.shortInfo = (char**)malloc(sizeof(char*) * num);
    head->searchFlag = (bool*)malloc(head->vexNum);
    memset(head->searchFlag,0,head->vexNum);
    memset(head->matrix,-1,num * num * sizeof(int));
    return head;
}

void deleteForm(pForm head){
    for(int i = 0; i < head -> vexNum; i++){
        free(head->info.name[i]);
        free(head->info.shortInfo[i]);
    }
    free(head->matrix);
    free(head->searchFlag);
    free(head);
}

pForm fillForm(char** name,char** infor,int (*edgeInfo)[3],int vexNum,int eNum){
    pForm head = initForm(vexNum);
    for(int i = 0; i < vexNum; i++){
        head->info.name[i] = (char*)malloc(strlen(name[i]));
        head->info.shortInfo[i] = (char*)malloc(strlen(infor[i]));
        strcpy(head->info.name[i],name[i]);
        strcpy(head->info.shortInfo[i],infor[i]);
        head->matrix[i + vexNum * i] = 0;
    }
    head->edgeNum = eNum;
    for(int i = 0; i < eNum; i++){
        head->matrix[edgeInfo[i][0] * vexNum + edgeInfo[i][2]] = edgeInfo[i][1];
        head->matrix[edgeInfo[i][2] * vexNum + edgeInfo[i][0]] = edgeInfo[i][1];
    }
    return head;
}

char** findMin(pForm head,int start,int end){
    int* dis = (int*)malloc(sizeof(int) * head->vexNum);
    char** orderName = (char**)malloc(sizeof(char*) * (head->vexNum + 1));
    memcpy(dis,&head->matrix[start * (head->vexNum - 1)],sizeof(int) * head->vexNum);
    for(int i = 0; i < head->vexNum; i++){
        if(head->matrix[i] == -1){
            orderName[i] = NULL;
        }else{
            orderName[i] = (char*)malloc(sizeof(char) * 100);
            snprintf(orderName[i],100,"%s->%s",head->info.name[start],head->info.name[i]);
        }
    }
    bool* flag = (bool*)malloc(sizeof(bool) * head->vexNum);
    memset(flag,0,sizeof(bool) * head->vexNum);
    for(int i = 0; i < head->vexNum; i++){
        int minNum = 0;
        int min = dis[0];
        for(int j = 0; j < head->vexNum && dis[j] != -1 && !flag[j]; j++){
            if(min < dis[j]){
                min = dis[j];
                minNum = j;
            }
        }
        flag[minNum] = 1;
        for(int j = 0; j < head->vexNum && head->matrix[minNum * head->vexNum + j] != -1; j++){
            if(dis[j] > dis[minNum] + head->matrix[minNum * head->vexNum + j] || dis[j] == -1){
                dis[j] = dis[minNum] + head->matrix[minNum * head->vexNum + j];
                if(j == end){
                    orderName[head->vexNum] = (char*)dis[j];
                }
                if(orderName[j]){
                    free(orderName[j]);
                }
                orderName[j] = (char*)malloc(sizeof(char) * 100);
                snprintf(orderName[j],100,"%s->%s",orderName[minNum],head->info.name[j]);
            }
        }
    }
    free(dis);
    free(flag);
    return orderName;
}

bool deleteSide(pForm head,int point1,int point2){
    if(point1 >= head->vexNum || point2 >= head->vexNum || point1 < 0 || point1 < 0){
        return 0;
    }
    head->matrix[point1 * head->vexNum + point2] = -1;
    head->matrix[point2 * head->vexNum + point1] = -1;
    head->edgeNum--;
    return 1;
}

bool deletePoint(pForm head,int point){
    int num = 0;
    if(point >= head->vexNum || point < 0){
        return 0;
    }
    int* newSpace = (int*)malloc(sizeof(int) * (head->vexNum - 1) * (head->vexNum - 1));
    for(int i = 0; i < head->vexNum && i != point; i++){
        for(int j = 0;j < head->vexNum && j != point; j++){
            newSpace[num++] = head->matrix[i * head->vexNum + j];
        }
    }
    head->vexNum--;
    free(head->matrix);
    head->matrix = newSpace;
    return 1;
}

bool addPoint(pForm head){
    head->vexNum++;
    int* newSpace = (int*)malloc(sizeof(int) * head->vexNum * head->vexNum);
    memset(newSpace,-1,head->vexNum * head->vexNum * sizeof(int));
    newSpace[head->vexNum * head->vexNum - 1] = 0;
    for(int i = 0; i < head->vexNum - 1; i++){
        for(int j = 0;j < head->vexNum - 1; j++){
            newSpace[i * head->vexNum + j] = head->matrix[i * (head->vexNum - 1) + j];
        }
    }
    free(head->matrix);
    head->matrix = newSpace;
    return 1;
}

bool addEdge(pForm head,int start,int end,int weight){
    if(start >= head->vexNum || end >= head->vexNum || start < 0 || end < 0){
        return 0;
    }
    head->matrix[start * head->vexNum + end] = weight;
    head->matrix[end * head->vexNum + start] = weight;
    head->edgeNum++;
    return 1;
}

void showMatrix(pForm head){
    for(int i = 0; i < head->vexNum; i++){
        for(int j = 0; j < head->vexNum; j++){
            printf("%d ",head->matrix[i * head->vexNum + j]);
        }
        printf("\n");
    }
}

void getRoads(int start,int end,pForm head,int* stack,int num){
    int* subStack = stack;
    if(!stack){
        subStack = (int*)malloc(sizeof(int) * head->vexNum);
        memset(subStack,-1,sizeof(int) * head->vexNum);
    }
    subStack[num] = start;
    head->searchFlag[start] = 1;
    if(start == end){
        for(int i = 0; subStack[i + 1] != -1 && (i + 1) < head->vexNum; i++){
            printf("%s->",head->info.name[i]);
        }
        printf("%s\n",head->info.name[end]);
        subStack[num] = -1;
        head->searchFlag[end] = 0;
        return;
    }
    for(int j = 0; j < head->vexNum; j++){
        if(head->matrix[head->vexNum * start + j] > 0 && !head->searchFlag[j]){
            getRoads(j,end,head,subStack,num + 1);
        }
    }
    head->searchFlag[subStack[num]] = 0;
    subStack[num] = -1;
    if(!stack){
        free(subStack);
    }
}