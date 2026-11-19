#include <stdio.h>
/**
 * @brief 二分查找法 [前提 : 序列有序]
 * 升序和降序序列的逻辑是反着的
 *
 * 现在写的是升序容器二分查找法 逻辑
 * @param arr
 * @param length
 * @param element 目标元素
 * @return int 所在位置
 */
int binarySearch(int *arr, int length, int element)
{
    //先定义2个变量分别指向 序列的头尾
    int start = 0;
    int end = length - 1;

    //循环进行二分查找
    while (start <= end)
    {
        //计算中间索引位置
        int mid = (start + end) >> 1;

        //判断中间mid指向的元素和目标元素的关系
        if (element > arr[mid])
        {
            //目标元素在mid的右边 -> 动start
            start = mid + 1;
        }else if (element < arr[mid])
        {
            //目标元素在mid的左边 -> 动end
            end = mid - 1;
        }else
        {
            //找到了
            return mid;
        }
    }
    //当循环完毕,都没有找到元素 -> 元素不存在
    return -1;
}

int main()
{

    return 0;
}