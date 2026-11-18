//init

//enqueue
//dequeue
//get_length
//destroy
//printf_queue
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct{
    int*data;
    int length;
    int front;
    int rear;
    int capacity;


}Qnqueue;
//init
void init_enqueue(Qnqueue*q,size_t capacity){
    q->data=(int *)malloc(sizeof(int)*capacity);
    q->front=0;
    q->rear=0;
    q->length=0;
    q->capacity=capacity;

}
//destory
void destory(Qnqueue*q){
    free(q->data);
    q->front=0;
    q->capacity=0;
    q->length=0;
    q->rear=0;

}
int get_length(Qnqueue*q){
    return q->length;

}
void enqueue(Qnqueue*q,int element){
    if (q->length>=q->capacity)
    {
       return;
    }
    // q->data[q->rear]=element;
    // 
    // if (q->rear>q>q->length)
    // {
    //    q->data[q->rear[(q->length)%(q->capacity+1)]]=element;
    // }else{
    //     q->data[q->rear]=element;

    // }
    // q->rear++;
    // q->length++;
    q->data[q->rear]=element;
    q->rear=(q->rear+1)%q->capacity;
    q->length++;
}
bool dequeue(Qnqueue*q,int *element){
    if (q->length==0)
    {
       return false;
    }
    // if (q->front>q->length)
    // {
    //    *element= q->data[q->front[(q->length)%(q->capacity+1)]]
    //    q>data[q->front];
    //    q->length++;
    //    return true
    // }else{
    //     q>data[q->front++];
    //     return true;
    // }
     *element=q->data[q->front];
     q->front=(q->front+1)%q->capacity;
     q->length--;
    



}
void printf_queue(Qnqueue*q){
    for (int i = 0; i < q->length; i++)
    {
        int index=(q->front+i)%q->capacity;
        printf("%d\n",q->data[index]);
    }
    printf("\n");

}



int main(int argc, char const *argv[])
{
    Qnqueue q;
    init_enqueue(&q,5);
    enqueue(&q,1);
    enqueue(&q,1);
    enqueue(&q,2);
    enqueue(&q,3);
    enqueue(&q,4);
    enqueue(&q,5);
    printf_queue(&q);

    
    return 0;
}
