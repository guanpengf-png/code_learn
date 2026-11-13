/* 案例：数组指针 +1，跨过整段数组。 */
#include <stdio.h>

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int (*block)[5] = &nums;

    printf("这段数组的第一个数 = %d\n", (*block)[0]);
    printf("block + 1 跨过 %zu 字节\n", sizeof(*block));
    return 0;
}
