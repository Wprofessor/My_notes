#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define MAXSIZE 100
using namespace std;
typedef struct node {
	int key;
} snode;
typedef struct {
	snode r[MAXSIZE];
	int length;
} sqlist;
void swap(snode *x,snode *y) {
	int s;
	s = x->key;
	x->key = y->key;
	y->key = s;
}
//Ѱ�һ���������λ��
int sign(sqlist *t,int left,int right) {
	int ok = t->r[left].key;
	while(left < right) {
		while(left < right && ok <= t->r[right].key) {
			right--;
		}
		swap(&t->r[left],&t->r[right]);
		while(left < right && ok > t->r[left].key) {
			left++;
		}
		swap(&t->r[left],&t->r[right]);
	}
	return left;
}
//�ݹ�����
void qsort(sqlist *t,int left,int right) {

	if(left < right) {
		int val = sign(t,left,right);
		qsort(t,left,val-1);
		qsort(t,val+1,right);
	}
}
void display(sqlist *t) {

	for(int i= 0; i < t->length; i++) {
		if(i == 0)
			cout<<t->r[i].key;
		else
			cout<<" "<<t->r[i].key;
	}
	cout<<endl;
}
int main() {
	sqlist t;
//	t = (sqlist *)malloc(sizeof(sqlist));   //��������������ָ�룬�ǵÿ��ٿռ� 
	t.length = 5;
	t.r[0].key = 67;
	t.r[1].key =4;
	t.r[2].key =54;
	t.r[3].key =567;
	t.r[4].key =65;

	qsort(&t,0,t.length-1);
	display(&t);
	return 0;
}
