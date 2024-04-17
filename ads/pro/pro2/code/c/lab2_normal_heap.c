#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define INFINITYSIZE 100000000; // 定义无穷大

int known[24000000]; // 记录节点是否已知
int distance[24000000]; // 记录节点到起始点的距离

// 堆结构体定义
struct Heap {
    int element[10000000]; // 堆的元素数组
    int size; // 堆的大小
};
typedef struct Heap *heap;

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

// 构建图
graph build_map(char *file_name);

// 使用普通堆找到最短路径
void find_the_shortest_way(graph map, int start, int end);

// 下沉操作
void down(heap h, int *dist);

// 删除最小元素
int delete_min(heap h, int *dist);

// 插入元素到堆
void push(heap h, int a, int *dist);

// 主函数
int main() {
    srand(time(NULL));
    char file_name[20];
    scanf("%s", file_name); // 从标准输入读取文件名
    graph map = build_map(file_name); // 构建图
    clock_t c_start, c_end;
    c_start = clock();
    for (int i = 0; i < 1000; i++)
        find_the_shortest_way(map,rand() % map->nv+1, rand() % map->nv+1); // 重复运行1000次找到最短路径
    c_end = clock();
    printf("avg_time of %s = %lf\n", file_name, (((double)c_end - c_start) / CLK_TCK) / 1000.0); // 输出平均运行时间
}

// 构建图
graph build_map(char *file_name) {
    FILE *fp = fopen(file_name, "r"); // 打开文件
    int nv, ne;
    int num_enter = 0;
    graph map = (graph)malloc(sizeof(struct Graph)); // 分配图的内存空间
    while(!feof(fp)) { // 读取文件直到结束
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

// 下沉操作
void down(heap h,int *dist) {
    int i = 1; // 从根节点开始下沉
    int element = h->element[1]; // 获取根节点元素
    while (1) { // 不断进行下沉直到满足堆的性质
        if (2 * i  > h->size)
            break; // 已经到达叶子节点
        int less;
        if ((2 * i) == h->size || dist[h->element[2 * i]] < dist[h->element[2 * i + 1]])
            less = 2 * i; // 只有左子节点或者左子节点更小
        else
            less = 2 * i + 1; // 右子节点更小
        if (dist[h->element[less]] < dist[element]) { // 如果子节点更小，则交换
            h->element[i] = h->element[less];
            i = less;
        } else
            break; // 否则停止下沉
    }
    h->element[i] = element; // 将原来的元素放入合适的位置
}

// 删除最小元素
int delete_min(heap h,int *dist) {
    if(h->size==0)
        return -1; // 堆为空，返回-1
    int result = h->element[1]; // 最小元素为根节点
    h->element[1] = h->element[h->size]; // 将最后一个元素移到根节点
    h->size--; // 堆大小减一
    down(h, dist); // 对根节点进行下沉操作
    return result; // 返回删除的最小元素
}

// 插入元素到堆
void push(heap h,int a,int *dist) {
    h->size++; // 堆大小加一
    h->element[h->size] = a; // 将新元素放入堆的最后位置
    if (h->size == 1)
        return; // 如果堆中只有一个元素，不需要调整
    int i = h->size; // 新元素的位置
    while (i > 1) { // 自下而上进行调整，直到满足堆的性质
        if (dist[h->element[i / 2]] < dist[a])
            break; // 父节点比新元素小，不需要调整
        else {
            h->element[i] = h->element[i / 2]; // 父节点比新元素大，将父节点下移
            i = i / 2; // 更新新元素的位置
        }
    }
    h->element[i] = a; // 将新元素放入合适的位置
}

// 使用普通堆找到最短路径
void find_the_shortest_way(graph map, int start, int end) {
    for (int i = 1; i <= map->nv; i++) {
        known[i] = 0; // 初始化节点状态为未知
        distance[i] = INFINITYSIZE; // 初始化距离为无穷大
    }
    distance[start] = 0; // 设置起始节点距离为0
    heap normal_heap = (heap)malloc(sizeof(struct Heap)); // 分配普通堆的内存空间
    normal_heap->element[1] = start; // 将起始节点放入堆中
    normal_heap->size = 1; // 堆的大小为1
    while(1) {
        int min_i = delete_min(normal_heap, distance); // 删除堆中的最小元素
        if (min_i == -1)
            break; // 堆为空，退出循环
        node temp = map->v[min_i]; // 获取最小元素对应的节点
        if (min_i == end)
            break; // 已经找到目标节点，退出循环
        known[min_i] = 1; // 标记当前节点已知
        while (temp != NULL) {
            if (distance[temp->v] > distance[min_i] + temp->dist && known[temp->v] == 0) {
                distance[temp->v] = distance[min_i] + temp->dist; // 更新距离
                push(normal_heap, temp->v, distance); // 将新节点插入堆中
            }
            temp = temp->next; // 继续处理下一个相邻节点
        }
    }
    printf("%d %d distance = %d\n", start, end, distance[end]); // 输出最短距离
}
