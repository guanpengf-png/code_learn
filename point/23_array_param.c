/* 案例：数组名传进函数后变成指针。函数里看到的是指针的大小，不是整段数组。 */
#include <stdio.h>

static void show(int a[5])
{
    int *as_pointer = a;

    printf("函数里这个参数占 %zu 字节\n", sizeof as_pointer);
    printf("a[0] = %d\n", a[0]);
}

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};

    printf("main 里 nums 占 %zu 字节\n", sizeof nums);
    show(nums);
    return 0;
}
