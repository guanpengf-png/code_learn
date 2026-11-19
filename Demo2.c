#include <stdio.h>
#include <stdlib.h>

// 定义结构体
typedef struct
{
    // 指向首个数据的指针 [栈底]
    int *data;
    int length;
    int capacity;
} Stack;

/**
 * @brief 初始化栈
 *
 * @param Stack 要被操作栈
 * @param initCapacity 初始容量
 */
void initStack(Stack *stack, int initCapacity);

/**
 * @brief 销毁栈
 *
 * @param Stack
 */
void destoryStack(Stack *stack);

/**
 * @brief 扩容 2 倍
 *
 * @param Stack
 */
void resizeStack(Stack *stack);

/**
 * @brief 进栈 [在栈顶添加元素]
 *
 * @param Stack
 * @param element
 */
void push(Stack *stack, int element);

/**
 * @brief 弹栈[从栈顶移除元素]
 *
 * @param Stack
 * @return int 出栈的元素
 */
int pop(Stack *stack);

// 栈结构没有 改查 函数

void printStack(Stack *stack);

int main()
{
    // 创建栈结构
    Stack stack;

    // 初始化栈
    initStack(&stack, 5);

    // 打印长度和容量
    printf("长度是 : %d , 容量是 : %d \n", stack.length, stack.capacity);

    // 添加元素 [进栈]
    push(&stack, 100);
    push(&stack, 200);
    push(&stack, 300);
    push(&stack, 400);
    push(&stack, 500);
    // 打印长度和容量
    printf("长度是 : %d , 容量是 : %d \n", stack.length, stack.capacity);
    printStack(&stack);

    push(&stack, 600);
    // 打印长度和容量
    printf("长度是 : %d , 容量是 : %d \n", stack.length, stack.capacity);
    printStack(&stack);

    // 弹栈
    for (size_t i = 0; i < 6; i++)
    {
        int element = pop(&stack);
        printf("弹栈的元素是 : %d \n", element);
        // 打印长度和容量
        printf("长度是 : %d , 容量是 : %d \n", stack.length, stack.capacity);
        printStack(&stack);
    }

    // 继续弹 [得到垃圾值]
    int element = pop(&stack);
    printf("弹栈的元素是 : %d \n", element);

    // 销毁栈
    destoryStack(&stack);

    return 0;
}

/**
 * @brief 初始化栈
 *
 * @param Stack 要被操作栈
 * @param initCapacity 初始容量
 */
void initStack(Stack *stack, int initCapacity)
{
    // 给stack的每一个属性赋值
    stack->data = (int *)malloc(initCapacity * sizeof(int));
    stack->capacity = initCapacity;
    stack->length = 0;
}

/**
 * @brief 销毁栈
 *
 * @param Stack
 */
void destoryStack(Stack *stack)
{
    // 把每个属性清零
    free(stack->data);
    stack->capacity = 0;
    stack->length = 0;
    stack = NULL;
}

/**
 * @brief 扩容 2 倍
 *
 * @param Stack
 */
void resizeStack(Stack *stack)
{
    int newCapacity = stack->capacity << 1;
    stack->data = (int *)realloc(stack->data, newCapacity * sizeof(int));
    // 把新容量赋值给容量属性
    stack->capacity = newCapacity;
}

/**
 * @brief 进栈 [在栈顶添加元素]
 *
 * @param Stack
 * @param element
 */
void push(Stack *stack, int element)
{
    // 判断是否满了
    if (stack->length == stack->capacity)
    {
        resizeStack(stack);
    }

    // 要添加的元素位置就是length的值
    stack->data[stack->length] = element;

    // 加完一个元素 长度+1
    stack->length++;
}

/**
 * @brief 弹栈[从栈顶移除元素]
 *
 * @param Stack
 * @return int 出栈的元素
 */
int pop(Stack *stack)
{
    if (stack->length <= 0)
    {
        // 说明没有元素
        return rand(); // 异常码
    }

    int element = stack->data[stack->length - 1];
    // 把长度--
    stack->length--;
    return element;
}

// 栈结构没有 改查 函数

void printStack(Stack *stack)
{
    printf("stack : [");

    for (size_t i = 0; i < stack->length; i++)
    {
        printf("%d", stack->data[i]);
        if (i == stack->length - 1)
        {
            printf("] \n");
        }
        else
        {
            printf(", ");
        }
    }
}