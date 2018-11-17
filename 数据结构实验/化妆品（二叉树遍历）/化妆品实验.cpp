#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define MAXSIZE 100
using namespace std;
typedef char datatype;
typedef struct node {
	datatype info[MAXSIZE];
	int value;
	struct node *lchild,*rchild;
} node,*treenode;
//先序递归创建
treenode creatTree() {
	char ch[MAXSIZE];
	int x;
	treenode t;
	cin>>ch;
	getchar();
	cin>>x;
	if(strcmp(ch,"#") == 0)
		t = NULL;
	else {
		t = (node *)malloc(sizeof(node));
		strcpy(t->info,ch);
		t->value = x;
		t->lchild = creatTree();
		t->rchild = creatTree();
	}
	return t;
}
//递归遍历
void perorder(treenode t) {
	if(t) {
		cout<<t->info<<"的价钱是："<<t->value<<endl;
		perorder(t->lchild);
		perorder(t->rchild);
	}
}
void inorder(treenode t) {
	if(t) {
		inorder(t->lchild);
		cout<<t->info<<"的价钱是："<<t->value<<endl;
		inorder(t->rchild);
	}
}
void postorder(treenode t) {
	if(t) {
		postorder(t->lchild);
		postorder(t->rchild);
		cout<<t->info<<"的价钱是："<<t->value<<endl;
	}
}
//非递归遍历
void perorder1(treenode t) {
	treenode data[MAXSIZE];
	int top = 0;
	while(t || top != 0) {
		if(t) {
			cout<<t->info<<"的价钱是："<<t->value<<endl;
			data[top] = t;
			top++;
			t = t->lchild;
		} else {
			top--;
			t = data[top];
			t = t->rchild;
		}
	}
	cout<<endl;
}
void inorder1(treenode t) {
	treenode data[MAXSIZE];
	int top = 0;
	while(t || top != 0) {
		if(t) {
			data[top] = t;
			top++;
			t = t->lchild;
		} else {
			top--;
			t = data[top];
			cout<<t->info<<"的价钱是："<<t->value<<endl;
			t = t->rchild;
		}
	}
	cout<<endl;
}
void postorder1(treenode t) {
	treenode data[MAXSIZE];
	int sign[MAXSIZE];
//	memset(sign,-1,sizeof(sign));
	int top = 0;
	while(t || top != 0) {
		if(t) {
			data[top] = t;
			sign[top] = 0;
			top++;
			t = t->lchild;
		} else if(sign[top-1] == 1) {
			top--;
			t = data[top];
			cout<<t->info<<"的价钱是："<<t->value<<endl;
			t = NULL;
		} else if(sign[top-1] == 0) {
			t = data[top-1];
			sign[top-1] = 1;
			t = t->rchild;
		} else {
			t == NULL;
		}
	}
	cout<<endl;
}
void show() {
	cout<<"-----化妆品实验-----"<<endl;
	cout<<"1.递归前序遍历"<<endl;
	cout<<"2.递归中序遍历"<<endl;
	cout<<"3.递归后序遍历"<<endl;
	cout<<"4.非递归前序遍历"<<endl;
	cout<<"5.非递归中序遍历"<<endl;
	cout<<"6.非递归后序遍历"<<endl;
	cout<<"7.退出程序"<<endl;
}
int main() {
	cout<<"请先输入化妆品品牌和价格"<<endl;
	cout<<"记得前序输入哦！"<<endl;
	treenode t;
	t = creatTree();
	cout<<"二叉树创建完毕"<<endl;
	system("pause");
	while(1) {
		system("cls");
		show();
		cout<<"请选择您需要的遍历方式"<<endl;
		int n;
		cin>>n;
		switch(n) {
			case 1: {
				system("cls");
				perorder(t);
				system("pause");
				break;
			}
			case 2: {
				system("cls");
				inorder(t);
				system("pause");
				break;
			}
			case 3: {
				system("cls");
				postorder(t);
				system("pause");
				break;
			}
			case 4: {
				system("cls");
				perorder1(t);
				system("pause");
				break;
			}
			case 5: {
				system("cls");
				inorder1(t);
				system("pause");
				break;
			}
			case 6: {
				system("cls");
				postorder1(t);
				system("pause");
				break;
			}
			case 7: {
				system("cls");
				exit(1);
				break;
			}
		}
	}
//	perorder1(t);
//	inorder1(t);
//	postorder1(t);
	return 0;
}

