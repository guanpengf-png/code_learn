#include <stdio.h>

/**
 * @brief 顺序查找
 *
 * @param arr
 * @param length
 * @param element 目标元素
 * @return int 索引
 */
int flowSort(int *arr, int length, int element)
{
    if (length == 0)
    {
        return -1;
    }

    //顺序查找
    for (int i = 0; i < length; i++)
    {
        if (arr[i] == element)
        {
            return i;
        }
    }
    
    return -1;
}

int main()
{

    return 0;
}