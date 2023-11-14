#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 5

typedef struct Queue{
    int front;
    int rear;
    int data[MAXSIZE];
}Queue;

typedef struct Graph{
    char* vexs;
    int** arcs;
    int verNum;
    int arcNum;
}Graph;

Queue* initQueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = 0;
    q->rear = 0;
    return q;
}

Graph* initGraph(int verNum){
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->vexs = (char*)malloc(sizeof(char) * verNum);
    G->arcs = (int**)malloc(sizeof(int*) * verNum);
    for(int i = 0; i < verNum; i++){
        G->arcs[i] = (int*)malloc(sizeof(int) * verNum);
    }
    G->verNum = verNum;
    G->arcNum = 0;
    return G;
}

int isFull(Queue* q){
    if((q->rear + 1) % MAXSIZE == q->front)
        return 1;
    return 0;
}

void enQueue(Queue* q,int data){
    if(!isFull(q)){
        q->data[q->rear] = data;
        q->rear = (q->rear + 1) % MAXSIZE;
    }
}

int isEmpty(Queue* q){
    if(q->front == q->rear)
        return 1;
    return 0;
}

int deQueue(Queue* q){
    if(!isEmpty(q)){
        int data = q->data[q->front];
        q->front = (q->front + 1) % MAXSIZE;
        return data;
    }
    else{
        return -1;
    }
}

void createGraph(Graph* g,char* vexs,int* arcs){
    for(int i = 0; i < g->verNum; i++){
        g->vexs[i] = vexs[i];
        for(int j = 0; j < g->verNum; j++){
            g->arcs[i][j] = *(arcs + i * g->verNum + j);
            if(g->arcs[i][j] == 1)
                g->arcNum++;
        }
    }
    g->arcNum /= 2;
}

void DFS(Graph* g,int* visited,int index){
    //depth first search
    printf("%c\t",g->vexs[index]);
    visited[index] = 1;
    for(int i = 0; i < g->verNum; i++){
        if(g->arcs[index][i] == 1 && !visited[i]){
            DFS(g,visited,i);
        }
    }
}

void BFS(Graph* g,int* visited,int index){
    //Breadth First Search
    Queue* q = initQueue();
    printf("%c\t",g->vexs[index]);
    visited[index] = 1;
    enQueue(q,index);
    while(!isEmpty(q)){
        int i = deQueue(q);
        for(int j = 0; j < g->verNum; j++){
            if(g->arcs[i][j] == 1 && !visited[j]){
                visited[j] = 1;
                printf("%c\t",g->vexs[j]);
                enQueue(q,j);
            }
        }
    }
}

int main(int argc,char* argv[]){
    Graph* g = initGraph(5);
    int arr[5][5] = {
            0,1,1,1,0,
            1,0,1,1,1,
            1,1,0,0,0,
            1,1,0,0,1,
            0,1,0,1,0
    };
    createGraph(g,"ABCDE",(int*)arr);
    int* visited = (int*)malloc(sizeof(int) * g->verNum);
    for(int i = 0; i < g->verNum; i++){
        visited[i] = 0;
    }
    BFS(g,visited,0);
    printf("\n");
    for(int i = 0; i < g->verNum; i++){
        visited[i] = 0;
    }
    BFS(g,visited,0);
    printf("\n");
    return 0;
}