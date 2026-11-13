/* 案例：二级指针。实参是 &cursor，函数里的 *pp 就是 cursor 自己。 */
#include <stdio.h>

static void hop(int **pp)
{
    *pp = *pp + 1;
}

int main(void)
{
    int nums[3] = {10, 20, 30};
    int *cursor = nums;

    printf("移动前 %d\n", *cursor);
    hop(&cursor);
    printf("移动后 %d\n", *cursor);
    return 0;
}
