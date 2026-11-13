/* 案例：指针函数。函数返回一个指针，这里返回数组里某个元素的地址。 */
#include <stdio.h>

static int *element(int *p, int index)
{
    return &p[index];
}

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int *found = element(nums, 3);

    printf("*found = %d\n", *found);
    return 0;
}
