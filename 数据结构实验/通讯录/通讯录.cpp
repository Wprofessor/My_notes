#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define MAXSIZE 100
using namespace std;
typedef char datatype;
typedef struct node {
	datatype phone[MAXSIZE];
	datatype name[MAXSIZE];
	struct node *next;
} node;
node * init() {
	return NULL;
}
node* find(node *head,datatype x[]) {
	node *p;
	p = head;
	while(p) {
		if(strcmp(p->name,x))
			return p;
		p = p->next;
	}
	return NULL;
}
//录入
node* add(node *head) {
	node *p,*q;
	p = head;
	int n;
	//文件读取
	FILE *rf;
	rf = fopen("C:/Users/王教授/Desktop/contacts.txt","rb");
	if(rf) {
		fscanf(rf,"%d",&n);
		for(int i = 0; i < n; i++) {
			q = (node*)malloc(sizeof(node));
			fscanf(rf,"%s%s",&q->name,&q->phone);
			if(!p) {
				p = q;
				p->next = NULL;  //头节点已经改变
				head = p;
			} else {
				q->next = p->next;
				p->next = q;
			}
		}
		fclose(rf);
		return head;
	}
}
node *insert(node *head,char name[],char phone[]) {
	node *p,*q,*end;
	p = head;
	if(!p) {
		q = (node*)malloc(sizeof(node));
		strcpy(q->name,name);
		strcpy(q->phone,phone);
		p = q;
		p->next = NULL;  //头节点已经改变
		head = p;
		return head;
	} else {
		end = p->next;
		while(end) {
			p = p->next;
			end = p->next;
		}
		q = (node*)malloc(sizeof(node));
		strcpy(q->name,name);
		strcpy(q->phone,phone);
		q->next = p->next;
		p->next = q;
		return head;
	}
}
node *del(node *head,char name[]) {
	node *p,*x;
	p = head;
	if(!find(head,name)) {
		cout<<"删除的人不存在"<<endl;
		return head; 
	} else {
		x = NULL;
		while(p && strcmp(p->name,name) != 0) {
			x = p;
			p = p->next;
		}
		if(p) {
			if(!x) {
				head = head->next;
			} else {
				x->next = p->next;
			}
			free(p);
		}
		return head;
	}
}
void display(node *head) {
	node *p;
	p = head;
	while(p) {
		cout<<p->name<<"--"<<p->phone<<endl;
		p = p->next;
	}
}
int main() {
	node *head;
	head = init();
	head = add(head);
	head = insert(head,"dsfds","435");
	head = del(head,"王佳豪");
	display(head);
	return 0;
}
