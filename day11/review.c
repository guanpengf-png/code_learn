// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #define MAX 5
// typedef struct Graph{
//     char* vertx;
//     int **arr;
//     int vert_number;
//     int arc_array;

// }Graph;
// typedef struct Queue
// {
//     int front;
//     int rear;
//     int data[MAX];
// }Queue;
// Queue* init_queue(void){
//     Queue* q=(Queue*)malloc(sizeof(Queue));
//     if (q==NULL)
//     {
//         return NULL;
//     }
//     q->rear=q->front=0;
//     return q;   // 原来漏了 return, 调用方拿到的是垃圾指针

// }
// int is_full(Queue*q){
//     if ((q->rear+1)%MAX==q->front)
//     {
//         return 1;

//     }else{
//         return 0;

//     }

// }
// int is_empty(Queue*q){
//     if (q->front==q->rear)
//     {
//         return 1;
//     }else{
//         return 0;
//     }

// }
// int enqueue(Queue*q,int element){
//     if (is_full(q))
//     {
//         return 0;
//     }else{
//         q->data[q->rear]=element;
//         q->rear=(q->rear+1)%MAX;
//         return 1;
//     }

// }
// bool dequeue(Queue*q,int *element){
//     if (is_empty(q))
//     {
//        return false;
//     }else{
//         *element=q->data[q->front];
//         q->front=(q->front+1)%MAX;
//         return true;
//     }

// }
// Graph* init_graph(int verx_number){
//     Graph* g=(Graph*)malloc(sizeof(Graph));
//     if (g==NULL)
//     {
//         return NULL;
//     }
//     // 先赋值, 后面分配内存要用到
//     g->vert_number=verx_number;
//     g->arc_array=0;
//     g->vertx=(char*)malloc(sizeof(char)*g->vert_number);
//     g->arr=(int**)malloc(sizeof(int*)*g->vert_number);
//     for (int i = 0; i < g->vert_number; i++)
//     {
//         g->arr[i]=(int*)calloc(g->vert_number,sizeof(int));
//     }
//     return g;   // 原来漏了 return

// }
// void create_graph(Graph*g,char* vertx,int *array){
//     for (int i = 0; i < g->vert_number; i++)
//     {
//         g->vertx[i]=vertx[i];
//         for (int j = 0; j <g->vert_number ; j++)
//         {
//             g->arr[i][j]=*(array+i*g->vert_number+j);
//             if (g->arr[i][j]!=0)
//             {
//                 g->arc_array++;
//             }

//         }

//     }
//     g->arc_array/=2;   // 之前写在外层循环里, 每行都除了一次

// }
// void destroy(Graph*g){
//     for (int i = 0; i < g->vert_number; i++)
//     {
//         free(g->arr[i]);
//     }
//     free(g->arr);      // 行指针数组本身也要释放
//     free(g->vertx);
//     free(g);           // 图结构本身也由 init_graph 分配

// }
// void DFS(Graph*g,int *visited,int index){
//     printf("%c",g->vertx[index]);
//     visited[index]=1;
//     for (int i = 0; i < g->vert_number; i++)
//     {
//         if (g->arr[index][i]==1&&!visited[i])
//         {
//             /* code */
//             DFS(g,visited,i);
//         }

//     }

// }
// void destroy_queue(Queue*q);
// void BFS(Graph*G,int *visited,int index){
//     Queue*q=init_queue();
//     if (q==NULL)
//     {
//         return;
//     }
//     printf("%c\t",G->vertx[index]);
//     visited[index]=1;
//     enqueue(q,index);
//     int current=0;
//     while (!is_empty(q))
//     {
//         if (!dequeue(q,&current))
//         {
//             break;
//         }
//         for (int i = 0; i <G->vert_number; i++)
//         {
//             if (G->arr[current][i]==1&&!visited[i])
//             {
//                 printf("%c\t",G->vertx[i]);
//                 visited[i]=1;
//                 if (!enqueue(q,i))
//                 {
//                     // 队列满了, 这个点会被丢掉: MAX 需要调大
//                     destroy_queue(q);
//                     return;
//                 }
//             }

//         }

//     }
//     printf("\n");
//     destroy_queue(q);

// }
// void destroy_queue(Queue*q){
//     free(q);   // data 是结构体内嵌的数组, 不能单独 free
// }
// int main(void)
// {
//     Graph* g=init_graph(5);
//     if (g==NULL)
//     {
//         return 1;
//     }
//     int* visited=(int*)malloc(sizeof(int)*g->vert_number);
//     if (visited==NULL)
//     {
//         destroy(g);
//         return 1;
//     }
//     for (int i = 0; i < g->vert_number; i++)
//     {
//         visited[i]=0;

//     }
//     int arr[5][5]={
//         0,1,1,1,0,
//         1,0,1,1,1,
//         1,1,0,0,0,
//         1,1,0,0,1,
//         0,1,0,1,0
//     };
//     create_graph(g,"ABCDE",&arr[0][0]);
//     DFS(g,visited,0);
//     printf("\n");

//     // 复用 visited, BFS 之前必须清零
//     for (int i = 0; i < g->vert_number; i++)
//     {
//         visited[i]=0;
//     }
//     BFS(g,visited,0);

//     free(visited);
//     destroy(g);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("=== 1) 非方阵: V 用错 ===\n");
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int *p = &a[0][0];
    // a[1][2] 的正确线性下标是 1*3+2 = 5
    printf("正确 i*3+j: p[5] = %d (a[1][2]=%d)\n", p[1 * 3 + 2], a[1][2]);
    printf("错误 i*2+j: p[4] = %d  <- 这是 a[1][1]\n", p[1 * 2 + 2]);

    printf("\n=== 2) 子矩阵 / 行步长 (leading dimension) ===\n");
    int m[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            m[i][j] = i * 10 + j;
    int *view = &m[1][1]; // 3x3 子矩阵, 原矩阵每行 5 个
    printf("view 内 (1,0):\n");
    printf("正确 view[1*5+0] = %d (m[2][1]=%d)\n", view[1 * 5 + 0], m[2][1]);
    printf("错误 view[1*3+0] = %d (其实是 m[1][4])\n", view[1 * 3 + 0]);

    printf("\n=== 3) int ** 独立行: 不连续 ===\n");
    int **r = malloc(sizeof(int *) * 3);
    
    for (int i = 0; i < 3; i++)
    {
        r[i] = malloc(sizeof(int) * 3);
        for (int j = 0; j < 3; j++)
            r[i][j] = i * 10 + j;
    }
    printf("r[0]=%p, r[1]=%p, r[0]+3=%p\n", (void *)r[0], (void *)r[1], (void *)(r[0] + 3));
    printf("r[0]+3 == r[1] ? %s\n", (r[0] + 3 == r[1]) ? "是" : "否 -> 展平会读到间隙");
    for (int i = 0; i < 3; i++)
        free(r[i]);
    free(r);
    return 0;
}
