#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int data;
	struct Node *lchild, *rchild, *father;    // 记得要注意定义类型 
}Node;

Node* init(Node *_father, int _data) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = _data;
	node->lchild = NULL;
	node->rchild = NULL;
	node->father = _father;
	return node;							// 记得要注意有返回值 
}

Node* insert(Node *node, int value) {
	if (node == NULL) {						// 为空时 返回空节点 
		return node;
	}
	if (value > node->data) {        // 插入值比当前节点值大 
		if (node->rchild == NULL) {			// 为空时插入 
			node->rchild = init(node, value);
		} else {							//不为空时递归查找 
			node->rchild = insert(node->rchild, value);
		}
	} else if (value < node->data) {		// 同上 
		if (node->lchild == NULL) {
			node->lchild = init(node, value);
		} else {							
			node->lchild = insert(node->lchild, value);
		}
	}
	return node;
} 

void clear(Node *node) {
	if (node != NULL) {
		if (node->rchild != NULL) {
			clear(node);
		}
		if (node->lchild != NULL) {
			clear(node);
		}
		free(node);
	}
}

int main(){
	Node *roottree = NULL;					// 先定义一个空节点 
	int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (int i = 0; i < 10; i++) {
		roottree = insert(roottree, arr[i]);   // 每次的一个节点的插入 
	}
	clear(roottree);
	return 0;
}
