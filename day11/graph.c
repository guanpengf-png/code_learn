#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 邻接表: 每个顶点挂一条单链表, 链表里的每个节点就是一条边
typedef struct Edge
{
    size_t to;          // 这条边指向哪个顶点
    struct Edge *next;  // 同一个顶点的下一条边

} Edge;

typedef struct
{
    Edge **heads;          // heads[i] 是顶点 i 的第一条边
    size_t vertex_count;   // 顶点个数
    size_t edge_count;     // 边数

} Graph;

// init: 分配顶点数组, calloc 会把每个指针清成 NULL, 相当于每个顶点一开始都没有邻居
bool init_graph(Graph *graph, size_t vertex_count)
{
    graph->heads = (Edge **)calloc(vertex_count, sizeof(Edge *));
    if (graph->heads == NULL)
    {
        graph->vertex_count = 0;
        graph->edge_count = 0;
        return false;
    }
    graph->vertex_count = vertex_count;
    graph->edge_count = 0;
    return true;

}

// 给一个顶点挂一条单向边(内部用)
static bool add_half_edge(Graph *graph, size_t from, size_t to)
{
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    if (new_edge == NULL)
    {
        return false;
    }
    new_edge->to = to;
    new_edge->next = graph->heads[from];   // 头插法, 和你的链表是一个套路
    graph->heads[from] = new_edge;
    return true;

}

// 加一条无向边: from 的邻接表里加 to, to 的邻接表里也加 from
bool add_edge(Graph *graph, size_t from, size_t to)
{
    if (from >= graph->vertex_count || to >= graph->vertex_count)
    {
        return false;
    }
    if (!add_half_edge(graph, from, to))
    {
        return false;
    }
    if (!add_half_edge(graph, to, from))
    {
        // 第二条边分配失败的话, 把第一条摘掉, 不能留半条边
        Edge *head = graph->heads[from];
        graph->heads[from] = head->next;
        free(head);
        return false;
    }
    graph->edge_count++;
    return true;

}

// 从一个顶点的链表里摘掉指向 to 的那条边(内部用)
static bool remove_half_edge(Graph *graph, size_t from, size_t to)
{
    Edge *pre_node = NULL;
    Edge *current = graph->heads[from];
    while (current != NULL)
    {
        if (current->to == to)
        {
            if (pre_node == NULL)
            {
                // 要删的是链表第一个节点
                graph->heads[from] = current->next;
            }
            else
            {
                pre_node->next = current->next;
            }
            free(current);
            return true;
        }
        pre_node = current;
        current = current->next;
    }
    return false;

}

// 删一条无向边: 两个方向的都要删
bool remove_edge(Graph *graph, size_t from, size_t to)
{
    if (from >= graph->vertex_count || to >= graph->vertex_count)
    {
        return false;
    }
    if (!remove_half_edge(graph, from, to))
    {
        return false;
    }
    // 自环时 from == to, add_edge 加了两条, 这里也要删两条
    remove_half_edge(graph, to, from);
    graph->edge_count--;
    return true;

}

// 查 from 和 to 之间有没有边
bool has_edge(Graph *graph, size_t from, size_t to)
{
    if (from >= graph->vertex_count || to >= graph->vertex_count)
    {
        return false;
    }
    Edge *current = graph->heads[from];
    while (current != NULL)
    {
        if (current->to == to)
        {
            return true;
        }
        current = current->next;
    }
    return false;

}

// 顶点的度 = 它的邻接表有多长
size_t degree(Graph *graph, size_t vertex)
{
    if (vertex >= graph->vertex_count)
    {
        return 0;
    }
    size_t count = 0;
    Edge *current = graph->heads[vertex];
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;

}

// 打印整个图
void print_graph(Graph *graph)
{
    printf("顶点数: %zu, 边数: %zu\n", graph->vertex_count, graph->edge_count);
    for (size_t i = 0; i < graph->vertex_count; i++)
    {
        printf("v%zu:", i);
        Edge *current = graph->heads[i];
        while (current != NULL)
        {
            printf(" -> %zu", current->to);
            current = current->next;
        }
        printf("\n");
    }

}

// 广度优先遍历: 用数组当队列, 每个顶点最多进队一次, 所以队列开 vertex_count 就够
void bfs(Graph *graph, size_t start)
{
    if (start >= graph->vertex_count)
    {
        return;
    }
    bool *visited = (bool *)calloc(graph->vertex_count, sizeof(bool));
    size_t *queue = (size_t *)malloc(sizeof(size_t) * graph->vertex_count);
    if (visited == NULL || queue == NULL)
    {
        free(visited);
        free(queue);
        return;
    }
    size_t head = 0;
    size_t tail = 0;
    visited[start] = true;
    queue[tail++] = start;
    printf("bfs:");
    while (head < tail)
    {
        size_t current = queue[head++];
        printf(" %zu", current);
        Edge *edge = graph->heads[current];
        while (edge != NULL)
        {
            if (!visited[edge->to])
            {
                visited[edge->to] = true;
                queue[tail++] = edge->to;
            }
            edge = edge->next;
        }
    }
    printf("\n");
    free(visited);
    free(queue);

}

// 深度优先遍历的递归部分
static void dfs_visit(Graph *graph, size_t vertex, bool *visited)
{
    visited[vertex] = true;
    printf(" %zu", vertex);
    Edge *edge = graph->heads[vertex];
    while (edge != NULL)
    {
        if (!visited[edge->to])
        {
            dfs_visit(graph, edge->to, visited);
        }
        edge = edge->next;
    }

}

void dfs(Graph *graph, size_t start)
{
    if (start >= graph->vertex_count)
    {
        return;
    }
    bool *visited = (bool *)calloc(graph->vertex_count, sizeof(bool));
    if (visited == NULL)
    {
        return;
    }
    printf("dfs:");
    dfs_visit(graph, start, visited);
    printf("\n");
    free(visited);

}

// destroy: 每个顶点的链表逐节点释放, 最后释放顶点数组
void destroy_graph(Graph *graph)
{
    for (size_t i = 0; i < graph->vertex_count; i++)
    {
        Edge *current = graph->heads[i];
        while (current != NULL)
        {
            Edge *next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->heads);
    graph->heads = NULL;
    graph->vertex_count = 0;
    graph->edge_count = 0;

}

int main(void)
{
    Graph graph;
    if (!init_graph(&graph, 6))
    {
        printf("初始化失败\n");
        return 1;
    }
    // 0 - 1 - 3 - 4 - 5
    //  \  |  /
    //   \ 2
    add_edge(&graph, 0, 1);
    add_edge(&graph, 0, 2);
    add_edge(&graph, 1, 3);
    add_edge(&graph, 2, 3);
    add_edge(&graph, 3, 4);
    add_edge(&graph, 4, 5);
    print_graph(&graph);

    printf("v0 的度: %zu\n", degree(&graph, 0));
    printf("0-3 有边? %s\n", has_edge(&graph, 0, 3) ? "是" : "否");

    bfs(&graph, 0);
    dfs(&graph, 0);

    printf("--- 删除边 3-4 之后 ---\n");
    remove_edge(&graph, 3, 4);
    print_graph(&graph);

    destroy_graph(&graph);
    return 0;
}
