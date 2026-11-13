/* 案例：数组指针。block 是一个指针，指向整段有 5 个 int 的数组。 */
#include <stdio.h>

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int (*block)[5] = &nums;

    printf("(*block)[2] = %d\n", (*block)[2]);
    return 0;
}
