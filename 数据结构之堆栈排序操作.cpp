/*
这次输入有三种元素
第一个是代表插入的元素有多少
第二个是输入插入的元素
第三个是输入一个数， 表示执行几次“每次删除堆顶操作前的堆顶元素“

输出
输出所有执行次数的   “每次执行的删除堆顶操作前的堆顶元素“
然后遍历剩下的堆元素
然后对其剩下的堆元素进行从小到大的排序 并输出
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int *data, size;
} Heap;

void init(Heap *h, int length_input) {
    h->data = (int *)malloc(sizeof(int ) * length_input);
    h->size = 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(Heap *h, int value) {       // 上滤操作
    h->data[h->size] = value;
    int current = h->size;
    int father = (current - 1) / 2;
    while (h->data[current] > h->data[father]) {
        swap(&h->data[current], &h->data[father]);
        current = father;
        father = (current - 1) / 2;
    }
    h->size++;
}

void output(Heap *h) {
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->data[i]);
    }
    printf("\n");
}

int top(Heap *h) {
    return h->data[0];
}

void update(Heap *h, int pos, int n) {                    // 下滤
    int lchild = pos * 2 + 1, rchild = pos * 2 + 2;
    int max_value = pos;
    if (lchild < n && h->data[lchild] > h->data[max_value]) {
        max_value = lchild;
    }
    if (rchild < n && h->data[rchild] > h->data[max_value]) {
        max_value = rchild;
    }
    if (max_value != pos) {
        swap(&h->data[pos], &h->data[max_value]);
        update(h, max_value, n);
    }
}

void pop(Heap *h) {
    swap(&h->data[0], &h->data[h->size - 1]);
    h->size--;
    update(h, 0, h->size);
}

void heap_sort(Heap *h) {                          // 堆排序
    for (int i = h->size - 1; i >= 1; i--) {
        swap(&h->data[i], &h->data[0]);
        update(h, 0, i);
    }
}

void clear(Heap *h) {
    free(h->data);
    free(h);
}

int main() {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    init(heap, 105);
    int n;
    scanf("%d", &n);                           // 要插入堆的个数
    for (int i = 0; i < n; i++) {
        int sum;
        scanf("%d", &sum);                     // 插入的堆元素
        push(heap, sum); 
    }
    int num;
    scanf("%d", &num);                         // 输出的堆顶元素
    while(num--) {
        printf("%d\n", top(heap));          
        pop(heap);
    }
    output(heap);
    heap_sort(heap);                           // 排序后的输出 
    output(heap);
    return 0;
}
