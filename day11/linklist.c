#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct Node
{
    int data;
    
    struct Node* next;
}Node;
typedef struct{
    Node *header;
    int length;


}Linklist;
void init_linklist(Linklist* Linklist){
   Linklist->header=NULL;
   Linklist->length=0;


}
void destry_Linklist(Linklist* Linklist){
    Node* current=Linklist->header;
    while (current!=NULL)
    {
        Node* next=current->next;
        free(current);
        current=next;
    }
    Linklist->header=NULL;
    Linklist->length=0;
}
Node* get_pre_node(Linklist* list,int index){
    if (index<=0||index>list->length)
    {
        return NULL;
    }
    Node* prenode=list->header;

    for (int i = 0; i < index-1; i++)
    {
        prenode=prenode->next;
    } 
    return prenode;
    }
void insert_linklist(Linklist* list,int index,int element){
    if (index<0||index>list->length)
    {
        return;
    }
    Node* new_node=(Node*)malloc(sizeof(Node));
    new_node->data=element;
    new_node->next=NULL;
    //input at header
    if (index==0)
    {
        new_node->next=list->header;
        list->header=new_node;

    }
    else{
        Node* pre_node=get_pre_node(list,index);
        new_node->next=pre_node->next;
        pre_node->next=new_node;
        }
        list->length++;
    
}

bool delete_at(Linklist*list,int index,int *element){
    if (index<0||index>=list->length)
    {
        return false;
    }
    Node* del_node;
    if (index==0)
    {
        del_node=list->header;
        list->header=list->header->next;
    }else{
        Node* pre_node=get_pre_node(list,index);
        del_node=pre_node->next;
        pre_node->next=pre_node->next->next;

    }
    *element=del_node->data;
    del_node->next=NULL;
    free(del_node);
    list->length--;
    return true;

    

    
    }
bool set_link(Linklist*list,int index,int element,int *ipdate_element){
    if(index<0||list->length<=index)
    {
        return false;

    }
    if(index==0)
    {
        *ipdate_element=list->header->data;
        list->header->data=element;
    }else{
        Node* pre_node=get_pre_node(list,index);
       *ipdate_element=pre_node->next->data;
       pre_node->next->data=element;
    }
    return true;
    
}
int get_element(Linklist*list,int index){
    if(index<0||list->length<=index)
    {
        return -1;

    }
    if (index==0)
    {
        return list->header->data;

    }else{
        Node* node=get_pre_node(list,index);
        return node->next->data;
    }

    


}
void print_linked(Linklist*list){
    if (list->length==0)
    {
        return;
    }
    Node* start_node=list->header;
    while (start_node!=NULL)
    {
        printf("data is %d\n",start_node->data);
        start_node=start_node->next;
    }
    printf("\n");
    
}
bool delete_tail(Linklist*list,int *remove_element){
    return delete_at(list,list->length-1,remove_element);
}
void add_element(Linklist*list,int element){
    insert_linklist(list,list->length,element);
}
int main(int argc, char const *argv[])
{
    Linklist list;
    init_linklist(&list);
    add_element(&list,100);
    add_element(&list,101);
    add_element(&list,102);
    add_element(&list,103);
    add_element(&list,104);
    print_linked(&list);
    destry_Linklist(&list);
    int num=0;

    set_link(&list,0,4,&num);print_linked(&list);

  return 0;
}
