#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct{
    int rear;
    int front;
    int *arr;
    int length;
    int capacity;

}Queue;
typedef struct{
    char* vertx;
    int **arcs;
    int vertx_number;
    int arc_number;

}Graph;

//ini_q
Queue* init_queue(Queue*q,int new_capacity){
    q->arr=(int*)malloc(sizeof(int)*new_capacity);
    q->capacity=new_capacity;
    q->front=0;
    q->rear=0;
    q->length=0;
    return q;


}
//is_full
bool is_full(Queue*q){
    if (((q->rear+1)%q->capacity)==q->front)
    {
        return true;
    }else{
        return false;
    }
    
}
//is_empty
bool is_empty(Queue*q){
    if (q->rear==q->front)
    {
        return true;

    }else{
        return false;
    }
    

}
//enqueue
bool enqueue(Queue*q,int element){
    if (is_full(q))
    {
        return false;
    }else{
        q->arr[q->rear]=element;
        q->rear=(q->rear+1)%q->capacity;
        q->length++;
        return true;
    }
    

}
//dequeue
int dequeue(Queue*q,int *element){
    if (is_empty(q))
    {
       return -1;
    }
    else{
        *element=q->arr[q->front];
        q->front=(q->front+1)%q->capacity;
        q->length--;
        return *element;   // 返回的是值, 不是指针
    }

}
//free
void free_queue(Queue*q){
    free(q->arr);
    q->arr=NULL;
    q->capacity=0;
    q->front=0;
    q->rear=0;
    q->length=0;

}

//init_graph
Graph* init_graph(int verx_number){
    Graph* g=(Graph*)malloc(sizeof(Graph));
    if (g==NULL)
    {
        return NULL;
    }
    // 先把成员赋好值, 后面分配内存才能用
    g->vertx_number=verx_number;
    g->arc_number=0;
    g->vertx=(char*)malloc(sizeof(char)*g->vertx_number);
    // 1. 分配放行指针的数组: 元素是 int*, 不是 int
    g->arcs=(int**)malloc(sizeof(int*)*g->vertx_number);
    // 2. 每行单独分配, calloc 把邻接矩阵清成 0
    for (int i = 0; i < g->vertx_number; i++)
    {
        g->arcs[i]=(int*)calloc(g->vertx_number,sizeof(int));
    }
    return g;

}
///free
void free_graph(Graph*g){
    for (int i = 0; i < g->vertx_number; i++)
    {
        free(g->arcs[i]);
    }
    free(g->arcs);
    free(g->vertx);
    g->arcs=NULL;
    g->vertx=NULL;
    g->arc_number=0;
    g->vertx_number=0;

}
//bfs
void graph_bfs(Graph*g,int *visited,int index){
    Queue* Q=(Queue*)malloc(sizeof(Queue));
    if (Q==NULL)
    {
        return;
    }
    // 循环队列 (rear+1)%capacity==front 会浪费一个格子, 所以多开 1 个
    Queue*q=init_queue(Q,g->vertx_number+1);
    printf("%c\t",g->vertx[index]);
    visited[index]=1;
    enqueue(q,index);
    int current=0;
    while (!is_empty(q))
    {
        if (dequeue(q,&current)<0)
        {
            break;
        }
        for (int j = 0; j <g->vertx_number ; j++)
        {
            if (g->arcs[current][j]==1&&!visited[j])
            {
               printf("%c\t",g->vertx[j]);
               visited[j]=1;
               enqueue(q,j);   // 入队的是队列 q, 不是图 g

            }


        }

    }
    free_queue(q);
    free(Q);

}
//graph_bfs
//DFS
void graph_dfs(Graph*g,int *visited,int index){
    printf("%c\t",g->vertx[index]);
    visited[index]=1;
    for (int i = 0; i < g->vertx_number; i++)
    {
        if (g->arcs[index][i]==1&&!visited[i])
        {
            graph_dfs(g,visited,i);
        }
        
    }
    


}
//vetx_char abc
//int *arcs_number 0 or 1
void create_graph(Graph*g,char* vetx_char,int *arcs){
    for (int i = 0; i < g->vertx_number; i++)
    {
        g->vertx[i]=vetx_char[i];
       for (int j = 0; j < g->vertx_number; j++)
       {
            g->arcs[i][j]=*(arcs+i*g->vertx_number+j);
            if (g->arcs[i][j]!=0)
            {
                g->arc_number++;
            }
            
       }
       
    }
    g->arc_number/=2;
    


}
int main(int argc, char const *argv[])
{
    Graph*g=init_graph(5);
    int *vissted=(int*)(malloc(sizeof(int)*g->vertx_number));
    for (int i = 0; i < g->vertx_number; i++)
    {
        vissted[i]=0;
    }
    
    int arcs[5][5] = {
            0,1,1,1,0,
            1,0,1,1,1,
            1,1,0,0,0,
            1,1,0,0,1,
            0,1,0,1,0
    };
    create_graph(g,"ABCDE",(int*)arcs);
    graph_dfs(g,vissted,0);

    printf("\n");
    // visited 是同一块内存, BFS 前必须清零, 否则全部已访问, 什么都不打印
    for (int i = 0; i < g->vertx_number; i++)
    {
        vissted[i]=0;
    }
    graph_bfs(g,vissted,0);
    printf("\n");

    free(vissted);
    free_graph(g);
    free(g);

    return 0;
}
