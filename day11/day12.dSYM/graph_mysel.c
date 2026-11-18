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
bool dequeue(Queue*q){
    if (is_empty(q))
    {
       return false;
    }
    else{
        q->front=(q->front+1)%q->capacity;
        q->length--;
        return true;
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
    g->vertx=(char*)malloc(sizeof(char)*g->vertx_number);
    g->arcs=(int**)malloc(sizeof(int)*g->arc_number);
    g->vertx_number=verx_number;
    //number of 0 or 1
    g->arc_number=0;
    return g;

}
///free 
void free_graph(Graph*g){
    free(g->vertx);
    g->vertx=NULL;
    int i=0;
    while (g->arcs[i])
    {
        free(g->arcs[i]);
        i++;
    }
    g->arc_number=0;
    g->vertx_number=0;

}
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


    
    return 0;
}
