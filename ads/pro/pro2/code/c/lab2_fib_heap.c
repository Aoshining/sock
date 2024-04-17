#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define INFINITYSIZE 100000000; // 定义无穷大

int known[24000000]; // 记录节点是否已知
int distance[24000000]; // 记录节点到起始点的距离

// 图节点结构体定义
struct Node;
typedef struct Node *node;
struct Node {
    int v; // 目标节点
    int dist; // 距离
    node next; // 下一个节点指针
};
struct Graph {
    int nv; // 节点数
    int ne; // 边数
    node *v; // 节点数组
};
typedef struct Graph *graph;

// 斐波那契堆结构体定义
struct fib_node;
typedef struct fib_node *fn;
struct fib_node {
    int degree; // 节点度数
    int element; // 节点元素
    fn p; // 父节点指针
    fn child; // 子节点指针
    fn left; // 左兄弟指针
    fn right; // 右兄弟指针
};
struct fib_heap {
    fn min; // 最小节点指针
    int n; // 节点数
};
typedef struct fib_heap *fh;

// 构建图
graph build_map(char *file_name);

// 使用斐波那契堆找到最短路径
void fib_find_the_shortest_way(graph map, int start, int end);

// 合并斐波那契堆
void consolidate(fh h, int *dist);

// 删除最小节点
int fib_delete_min(fh h, int *dist);

// 插入节点到斐波那契堆
void fib_push(fh h, int a, int *dist);

// 主函数
int main() {
    srand(time(NULL)); // 设置随机种子
    char file_name[20];
    scanf("%s", file_name); // 从标准输入读取文件名
    graph map = build_map(file_name); // 构建图
    clock_t c_start, c_end;
    c_start = clock(); // 记录开始时间
    for (int i = 0; i < 1000; i++)
        fib_find_the_shortest_way(map,rand() % map->nv+1, rand() % map->nv+1); // 重复运行1000次找到最短路径
    c_end = clock(); // 记录结束时间
    printf("avg_time of %s = %lf\n", file_name, (((double)c_end - c_start) / CLK_TCK) / 1000.0); // 输出平均运行时间
}

// 构建图
graph build_map(char *file_name) {
    FILE *fp = fopen(file_name, "r"); // 打开文件
    int nv, ne;
    int num_enter = 0;
    graph map = (graph)malloc(sizeof(struct Graph)); // 分配图的内存空间
    // 读取文件
    while(!feof(fp)) {
        char k;
        k = fgetc(fp); // 读取字符
        if (k == '\n') { // 换行符表示一行结束
            num_enter++;
            if (num_enter == 4) { // 第四行开始是节点数和边数的声明
                fscanf(fp, "p sp %d %d", &nv, &ne); // 读取节点数和边数
                map->nv = nv; // 设置图的节点数
                map->ne = ne; // 设置图的边数
                map->v = (node *)malloc(sizeof(node) * (nv+1)); // 分配节点数组的内存空间
                for (int i = 1; i <= nv; i++)
                    map->v[i] = NULL; // 初始化节点数组为空
            }
            if (num_enter >= 7 && num_enter <= map->ne + 6) { // 边的信息从第七行开始
                int a, b, distance;
                fscanf(fp, "a %d %d %d", &a, &b, &distance); // 读取边的信息
                node temp = (node)malloc(sizeof(struct Node)); // 创建新的节点
                temp->v = b; // 设置目标节点
                temp->dist = distance; // 设置距离
                temp->next = NULL; // 设置下一个节点指针为空
                node k = map->v[a]; // 获取节点数组中的节点
                if (k == NULL)
                    map->v[a] = temp; // 如果节点为空，则直接插入
                else {
                    while (k ->next!= NULL)
                        k = k->next; // 寻找到节点链表的末尾
                    k->next = temp; // 插入新节点
                }
            }
        }
    }
    fclose(fp); // 关闭文件
    return map; // 返回构建好的图
}

// 合并斐波那契堆
void consolidate(fh h, int *dist) {
    // 如果堆只有一个节点，直接返回
    if (h->min->left == h->min)
        return;
    // 计算最大度数
    int max_degree = (int)(log(h->n) / log(2.0) + 0.5);
    // 创建一个数组用于存储各度数的节点
    fn a[max_degree + 1];
    for (int i = 0; i <= max_degree; i++) {
        a[i] = NULL;
    }
    // 从最小节点开始遍历
    fn t = h->min;
    fn end_while = t->left;
    do {
        // 当前节点的度数
        while(a[t->degree]!=NULL) {
            // 如果有相同度数的节点，则合并
            fn y = a[t->degree];
            // 比较节点值，保证父节点的值小于子节点的值
            if (dist[t->element] > dist[y->element]) {
                fn temp = t;
                t = y;
                y = temp;
            }
            // 移除子节点
            y->left->right = y->right;
            y->right->left = y->left;
            // 设置父子关系
            y->p = t;
            if (t->child == NULL) {
                t->child = y;
            } else {
                t->child->left->right = y;
                y->left = t->child->left;
                t->child->left = y;
                y->right = t->child;
            }
            // 清空数组中的该度数位置
            a[t->degree] = NULL;
            // 父节点度数增加
            t->degree++;
        }
        // 将当前节点存入数组
        a[t->degree] = t;
        // 移动到下一个节点
        t = t->left;
    } while (t != end_while);
    // 重置堆的最小节点
    h->min = NULL;
    for (int i = 0; i <= max_degree; i++) {
        // 找到最小节点
        if (a[i] != NULL) {
            if (h->min == NULL) {
                h->min = a[i];
            } else {
                if (dist[h->min->element] > dist[a[i]->element])
                    h->min = a[i];
            }
        }
    }
}

// 删除最小节点
int fib_delete_min(fh h, int *dist) {
    fn result = h->min;
    // 如果堆为空，返回-1
    if (result == NULL)
        return -1;
    else {
        // 移动子节点到堆顶
        fn child = result->child;
        for (int i = 0; i < h->min->degree; i++) {
            fn temp = child;
            child = temp->right;
            result->left->right = temp;
            temp->left = result->left;
            result->left = temp;
            temp->right = result;
            temp->p = NULL;
        }
        // 移除最小节点
        result->left->right = result->right;
        result->right->left = result->left;
        h->n--;
        if (h->n == 0)
            h->min = NULL;
        else {
            h->min = result->right;
            consolidate(h,dist);
        }
    }
    return result->element;
}

// 插入节点到斐波那契堆
void fib_push(fh h,int a,int *dist) {
    fn temp = (fn)malloc(sizeof(struct fib_node));
    temp->child = NULL;
    temp->degree = 0;
    temp->element = a;
    temp->p = NULL;
    temp->left = temp;
    temp->right = temp;
    if (h->min == NULL) {
        h->min = temp;
    } else {
        h->min->left->right = temp;
        temp->left = h->min->left;
        h->min->left = temp;
        temp->right = h->min;
        if (dist[a] < dist[h->min->element])
            h->min = temp;
    }
    h->n++;
}

// 使用斐波那契堆找到最短路径
void fib_find_the_shortest_way(graph map, int start, int end) {
    // 初始化已知和距离数组
    for (int i = 1; i <= map->nv; i++) {
        known[i] = 0;
        distance[i] = INFINITYSIZE;
    }
    distance[start] = 0;
    // 初始化斐波那契堆
    fh fib_heap = (fh)malloc(sizeof(struct fib_heap));
    fn s_node = (fn)malloc(sizeof(struct fib_node));
    s_node->degree = 0;
    s_node->p = NULL;
    s_node->child = NULL;
    s_node->left = s_node;
    s_node->right = s_node;
    s_node->element = start;
    fib_heap->min = s_node;
    fib_heap->n = 1;
    // 进行最短路径计算
    while(1) {
        int min_i = fib_delete_min(fib_heap, distance);
        if (min_i == -1)
            break;
        node temp = map->v[min_i];
        if (min_i == end)
            break;
        known[min_i] = 1;
        while (temp != NULL) {
            if (distance[temp->v] > distance[min_i] + temp->dist && known[temp->v] == 0) {
                distance[temp->v] = distance[min_i] + temp->dist;
                fib_push(fib_heap, temp->v, distance);
            }
            temp = temp->next;
        }
    }
    // 打印结果
    printf("%d %d distance = %d\n", start, end, distance[end]);
}
