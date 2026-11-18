#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//init
typedef struct 
{
    size_t length;
    int *data;
    size_t capacity;

    /* data */
}Stack;

void init_stack(Stack* stack,size_t new_capacity){
    stack->data=(int*)malloc(sizeof(int)*new_capacity);
    stack->capacity=new_capacity;
    stack->length=0;

}
//resize
void resize_stack(Stack*stack,size_t capacity){
    if (stack->length==stack->capacity)
    {
        stack->data=(int*)realloc(stack->data,stack->capacity*2);
    }
    }
    

//destroy
void destroy_stack(Stack*stack){
    free(stack->data);
    stack->data=NULL;
    stack->capacity=0;
    stack->length=0;

}
//get_length
int get_length(Stack*stack){
    return stack->length;
}
//push
void push(Stack*stack,int element){
    if (stack->length>stack->capacity)
    {
        resize_stack(stack,stack->capacity);
    }
    stack->data[stack->length++]=element;
    

}
//pop
bool pop(Stack*stack,int *elemnt){
    if (stack->length==0)
    {
        return false;
    }
    *elemnt=stack->data[stack->length-1];
    stack->data[stack->length--];
    printf("pop number is %d",stack->data[stack->length-1]);
    return true;

    

}
//printf_stack
void printf_stack(Stack*stack){
    for (int i = 0; i < stack->length; i++)
    {
        printf("stack data is %d",stack->data[i]);
        printf("\n");
    }
    
    
}

int main(int argc, char const *argv[])
{
    Stack *s;
    init_stack(&s,5);
    push(&s,1);
    push(&s,2);
    push(&s,3);
    push(&s,3);
    push(&s,4);
    push(&s,5);
    push(&s,6);
    //printf_stack(&s);
    int del=0;
    pop(&s,&del);
    pop(&s,&del);
    pop(&s,&del);
    pop(&s,&del);
    printf_stack(&s);

    return 0;
}
