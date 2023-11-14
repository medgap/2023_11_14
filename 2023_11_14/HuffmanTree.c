#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    int weight;
    int parent;
    int lchild;
    int rchild;
}TreeNode;

typedef struct HFTree{
    TreeNode* data;
    int length;
}HFTree;

HFTree* initHFTree(int* weight,int length){
    HFTree* T = (HFTree*)malloc(sizeof(HFTree));
    T->data = (TreeNode*)malloc(sizeof(TreeNode) * (2 * length - 1));
    for(int i = 0; i < length ; i++){
        T->data[i].weight = weight[i];
        T->data[i].parent = 0;
        T->data[i].lchild = -1;
        T->data[i].rchild = -1;
    }
    T->length = length;
    return T;
}

int* selectMin(HFTree* T){
    int Min = 10000;
    int SecondMin = 10000;
    int MinIndex;
    int secondIndex;
    for(int i = 0; i < T->length; i++){
        if(T->data[i].parent == 0){
            if(T->data[i].weight < Min){
                Min = T->data[i].weight;
                MinIndex = i;
            }
        }
    }
    for(int i = 0; i < T->length; i++){
        if(T->data[i].parent == 0){
            if(T->data[i].weight < SecondMin && i != MinIndex){
                SecondMin = T->data[i].weight;
                secondIndex = i;
            }
        }
    }
    int* res = (int*)malloc(sizeof(int) * 2);
    res[0] = MinIndex;
    res[1] = secondIndex;
    return res;
}

void createHFTree(HFTree* T){
    int length = 2 * T->length - 1;
    int min;
    int secondMin;
    for(int i = T->length; i < length; i++){
        int* res = selectMin(T);
        min = res[0];
        secondMin = res[1];
        T->data[i].weight = T->data[min].weight + T->data[secondMin].weight;
        T->data[i].lchild = min;
        T->data[i].rchild = secondMin;
        T->data[min].parent = i;
        T->data[secondMin].parent = i;
        T->length++;
        T->data[i].parent = 0;
    }
}

void preOrder(HFTree* T,int index){
    if(index != -1){
        printf("%d ",T->data[index].weight);
        preOrder(T,T->data[index].lchild);
        preOrder(T,T->data[index].rchild);
    }
}

int main(){
    int weight[7] = {5,1,3,6,11,2,4};
    HFTree* T = initHFTree(weight,7);
    createHFTree(T);
    preOrder(T,T->length - 1);
    printf("\n");
    return 0;
}