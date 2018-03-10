#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct Node{
    char color;
    int num;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
}node;

void leftRotate(node* x){

    node* subNode = x -> right;
    x -> right = subNode -> left;
    if(subNode -> left != NULL){
        subNode -> left -> parent = x;
    }
    //将右节点的左节点的值赋予父节点
    subNode -> parent = x -> parent;
    if(x -> parent == NULL){
        treeHead = subNode;
    }else if(x == x -> parent -> left){
        x -> parent -> left = subNode;
    }else{
        x -> parent -> right = subNode;
    }
    //分三种情况分别连接起祖父节点和子节点的关系
    subNode -> left = x;
    x -> parent = subNode;
    //将左旋后的源节点和后面的节点链接
}

void rightRotate(node* x){

    node* subNode = x -> left;
    x -> left = subNode -> right;
    if(subNode -> right != NULL){
        subNode -> right -> parent = x;
    } 
    //将左节点的右节点的值赋给子节点
    subNode -> parent = x -> parent;
    if(subNode -> parent == NULL){
        treeHead = subNode;
    }else if(subNode -> parent == x -> parent -> left){
        x -> parent -> left = subNode;
    }else{
        x -> parent -> right = subNode;
    }
    //分三种情况联系起祖父节点和子节点的关系
    subNode -> right = x;
    x -> parent = subNode;
    //建立起x和旋转节点的关系
}

int insertFix(node* x){
    
}

int insertNode(int key){

    node* subNode = (node*)malloc(sizeof(node));
    subNode -> num = key;
    subNode -> color = RED;
    subNode -> left = subNode -> right = NULL;
    node* subHead = treeHead;
    node* subParent = NULL;
    //新建一个节点 并将头结点赋予一个临时变量
    while(subHead != NULL){
        subParent = subHead;
        if(subHead -> num > key){
            subHead = subHead -> left;
        }else{
            subHead = subHead -> right；
        }
    }
    //向下遍历 找到插入点
    subNode -> parent = subParent;
    if(treeHead == NULL){
        treeHead = subNode;
    }else if(key < subParent -> num){
        subParent -> left = subNode;
    }else{
        subParent -> right = subNode;
    }
    //连接父节点和子节点的联系
    insertFix(subNode);
}

int searchNode(node* Tree){

}

int deleteNode(node* Tree){

}

int main(){

}
