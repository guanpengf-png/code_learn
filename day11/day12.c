#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// init
typedef struct
{
    size_t length;
    int *data;
    size_t capacity;

} Stack;

void init_stack(Stack *stack, size_t new_capacity)
{
    stack->data = (int *)malloc(sizeof(int) * new_capacity);
    if (stack->data == NULL)
    {
        stack->capacity = 0;
        stack->length = 0;
        return;
    }
    stack->capacity = new_capacity;
    stack->length = 0;
}
// resize
void resize_stack(Stack *stack, size_t new_capacity)
{
    int *new_data = (int *)realloc(stack->data, sizeof(int) * new_capacity);
    if (new_data == NULL)
    {
        return;
    }
    stack->data = new_data;
    stack->capacity = new_capacity;
}

// destroy
void destroy_stack(Stack *stack)
{
    free(stack->data);
    stack->data = NULL;
    stack->capacity = 0;
    stack->length = 0;
}
// get_length
size_t get_length(Stack *stack)
{
    return stack->length;
}
// push
void push(Stack *stack, int element)
{
    if (stack->length == stack->capacity)
    {
        size_t new_capacity = stack->capacity == 0 ? 1 : stack->capacity * 2;
        resize_stack(stack, new_capacity);
        if (stack->length == stack->capacity)
        {
            // 扩容失败, 放弃这次 push
            return;
        }
    }
    stack->data[stack->length++] = element;
}
// pop
bool pop(Stack *stack, int *element)
{
    if (stack->length == 0)
    {
        return false;
    }
    stack->length--;
    *element = stack->data[stack->length];
    return true;
}
// printf_stack
void printf_stack(Stack *stack)
{
    for (size_t i = 0; i < stack->length; i++)
    {
        printf("stack data is %d\n", stack->data[i]);
    }
}

int main(int argc, char const *argv[])
{
    Stack s;
    init_stack(&s, 5);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    push(&s, 3);
    push(&s, 4);
    push(&s, 5);
    push(&s, 6);
    printf_stack(&s);

    int del = 0;
    pop(&s, &del);
    pop(&s, &del);
    pop(&s, &del);
    pop(&s, &del);
    printf("四次数 pop 后, 栈顶被移除的值是 %d\n", del);
    printf_stack(&s);
    destroy_stack(&s);

    return 0;
}
