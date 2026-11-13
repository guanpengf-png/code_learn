/* 案例：普通指针 +1，跨过一个元素。 */
#include <stdio.h>

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int *p = nums;

    printf("p 指向 %d\n", *p);
    printf("p + 1 指向 %d\n", *(p + 1));
    printf("这一步是 %zu 字节\n", sizeof(int));
    return 0;
}
