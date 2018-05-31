#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int *data, size;
} Heap;

void init(Heap *h, int length_input) {         // 堆申请 
    h->data = (int *)malloc(sizeof(int) * length_input);
    h->size = 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(Heap *h, int value) {               // 插入操作 
    h->data[h->size] = value;
    int current = h->size;                    // 根节点
	int father = (current - 1) / 2;           //父节点 
	while (h->data[current] > h->data[father]) {  // 交换操作 
		swap(&h->data[current], &h->data[father]);
		current = father;
		father = (current - 1) / 2;
	} 
	h->size++;
}

void output(Heap *h) {                       // 遍历 
    for (int i = 0; i < h->size; i++) {
    	printf("%d ", h->data[i]);
	}
	printf("\n");
}

int top(Heap *h) {                          // 返出堆顶 
    return h->data[0]; 
}

void update(Heap *h, int pos, int n) {      // 堆调整 
    int lchild = pos * 2 + 1;
	int rchild = pos * 2 + 2;
	int max_value = pos;					// 存下标， 在进行交换 做标计量 
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

void pop(Heap *h) {							// 堆顶删除 
    swap(&h->data[0], &h->data[h->size - 1]);
	h->size--;
	update(h, 0, h->size);                  // 传入 （h , 堆顶下标， 数量 ）对堆进行调整 
}

void clear(Heap *h) {
    free(h->data);
    free(h);
}

int main() {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
	int arr[100];
	init (heap, 100);
	for (int i = 8; i >= 0; i--) {
		arr[i] = i;
	push (heap, arr[i]);
	} 
	output(heap);                    // 先输出堆元素 
    
    printf("%d\n", top(heap));		 // 输出堆顶	
    pop(heap);						 // 将堆顶弹出 
    output(heap);					 // 输出剩余元素 
    
    
    clear(heap); 
    return 0;
}
