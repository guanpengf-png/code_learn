#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <>
// 定义一个结构体的数组
typedef struct 
{
    int *arr;
    size_t capacity;
    size_t length;
}Array;

// 初始化数组,动态分配内存空间,并对其相关成员进行初始化操作
void inti_array(Array *arr,size_t capactiy);
void inti_array(Array *arr,size_t capactiy){
    //inti_array
    //data
    //capacty
    arr->arr=(int*)malloc(sizeof(int)*capactiy);
    arr->capacity=capactiy;
    arr->length=0;

}

// 重新分配数组的内存空间(数组的数据是可以增加的,动态数组)

void resize_array(Array* new_array,size_t new_capactiy);
void resize_array(Array* new_array,size_t new_capactiy){
    new_array->arr=(int*)realloc(new_array->arr,new_capactiy*sizeof(int));
    new_array->capacity=new_capactiy;
    
}
//if
//realloc

// 释放动态数组的内存空间
void destroy_array(Array* array);
void destroy_array(Array* array){
    //
    free(array->arr);
    array->arr=NULL;
    array->capacity=0;
    


}


// 获取数组的长度(实际的数据个数)
int get_length(Array* Array);
int get_length(Array* Array){
    return Array->length;
}
//get length


// 向指定索引位置插入一个元素数据
void insert_index(Array* Array,size_t index,int element);
void insert_index(Array* Array,size_t index,int element){
    if (index>Array->length)
    {
        return;
    }
    if (Array->length==Array->capacity)
    {
       resize_array(Array,2*Array->capacity);
    }
    
    for (int i = Array->length; i >index ; i--)
    {
        Array->arr[i]=Array->arr[i-1];
        //Array->arr[index]=element;
    }
     Array->arr[index]=element;
    Array->length++;
    
    
}
            //if 
            //insert

// 向数组尾部插入一个元素数据
void tail_insert(Array* Array,int element);
void tail_insert(Array* Array,int element){
    insert_index(Array,Array->length,element);
}
// 从指定索引位置移除一个元素数据
bool remove_at(Array* Array,size_t index,int *element);
bool remove_at(Array* Array,size_t index,int *element){
    if (index>Array->length)
    {
        return false;
    }
    *element=Array->arr[index];
    for (int i = index; i < Array->length-1; i++)
    {
        Array->arr[i]=Array->arr[i+1];
    }
    Array->length--;
    return true;
    

}
// 从数组尾部移除一个元素数据
void remove_at_tail(Array* Array,int *element);
void remove_at_tail(Array* Array,int *element){
    remove_at(Array,Array->length-1,element);

}

// 遍历动态数组中的所有数据
void printf_array(Array*Array);
void printf_array(Array*Array){
    if (Array->length==0)
    {
        return;
    }
    
    for (int i = 0; i < Array->length; i++)
    {
       printf("%d",Array->arr[i]);
       printf("\n");
    }
   // printf("\n");
    
}


int main(int argc, char const *argv[])
{
    Array arr;
    inti_array(&arr,5);
    insert_index(&arr,0,1);
    insert_index(&arr,0,2);
    insert_index(&arr,0,3);
    insert_index(&arr,0,4);
    insert_index(&arr,0,5);
    //printf_array(&arr);
    //printf("get_length%d\n",get_length(&arr));
    //tail_insert(&arr,1);
    int del_num=0;
   // printf_array(&arr);
    remove_at(&arr, 3, &del_num);
    printf_array(&arr);
    printf("get_length%d\n",get_length(&arr));
    printf("移除的数据是:%d \n", del_num);
    remove_at_tail(&arr, &del_num);
    printf("数组长度:%d \n", get_length(&arr));
    printf_array(&arr);
    destroy_array(&arr);




    
    return 0;
}
