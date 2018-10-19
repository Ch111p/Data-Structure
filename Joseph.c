#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Joseph.h"

//pNode
void playGame(pNode head,int num){
    int subSecret = 0;
    printf("请输入开始的位置:");
    scanf("%d",&subSecret);
    for(int i = 0;i < num;i++){
        subSecret %= num - i + 1;
        if(subSecret <= (num - i - 1) / 2){
            printf("right");
            for(int j = 0;j < subSecret - 1;j++){
                head = head->next;
            }
        }else{
            printf("left");
            for(int j = 0;j < num - i - subSecret + 1;j++){
                head = head->last;
            }
        }
        pNode subNode = head;
        printf("第%d个出局的是:%d\n",i + 1,head->id);
        subSecret = head->secret;
        head = head->next;
        deleteNode(subNode);
        if(i == num - 1){
            break;
        }
    }
}

int main(){
    int num = 0;
    printf("请输入一共的人数为:");
    scanf("%d",&num);
    pNode head = initNode(num);
    for(int i = 0;i < num;i++){
        printf("请输入%d个人的密码:",i + 1);
        scanf("%d",&head->secret);
        head = head->next;
    }
    playGame(head,num);
    system("pause");
    return 0;
}