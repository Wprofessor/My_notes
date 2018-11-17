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
		if(!strcmp(p->name,x))
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
	char ch[MAXSIZE];
	FILE *rf;
	int count;
	rf = fopen("C:/Users/王教授/Desktop/contacts.txt","rb");
	if(rf) {
		fscanf(rf,"%d",&count);
		fclose(rf);
	}
	FILE *rt;
	rt = fopen("C:/Users/王教授/Desktop/contacts.txt","r+");
	if(rt) {
		fprintf(rt,"%d",count+1);
		fclose(rt);
	}
	p = head;

	if(!p) {

		q = (node*)malloc(sizeof(node));
		strcpy(q->name,name);
		strcpy(ch,q->name);
		strcat(ch," ");
		strcpy(q->phone,phone);
		strcat(ch,q->phone);
		p = q;
		p->next = NULL;  //头节点已经改变
		head = p;
	} else {
		end = p->next;
		while(end) {
			p = p->next;
			end = p->next;
		}
		q = (node*)malloc(sizeof(node));
		strcpy(q->name,name);
		strcpy(ch,q->name);
		strcat(ch," ");
		strcpy(q->phone,phone);
		strcat(ch,q->phone);
		q->next = p->next;
		p->next = q;
	}
	FILE *radd;
	radd = fopen("C:/Users/王教授/Desktop/contacts.txt","a");
	if(radd) {

		fprintf(radd," %s",ch);
		fclose(radd);
	}
	return head;
}
node *del(node *head,char name[]) {
	node *p,*x;
	p = head;
	if(!find(head,name)) {
		cout<<"删除的人不存在"<<endl;
		return head;
	} else {
		FILE *rf;
		int count;
		rf = fopen("C:/Users/王教授/Desktop/contacts.txt","rb");
		if(rf) {
			fscanf(rf,"%d",&count);
			fclose(rf);
		}
		FILE *radd;
		radd = fopen("C:/Users/王教授/Desktop/contacts.txt","w");
		if(radd) {
			fprintf(radd,"%d",count-1);
			fclose(radd);
		}
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
		node *q = head;
		while(q) {
			FILE *radd;
			radd = fopen("C:/Users/王教授/Desktop/contacts.txt","a");
			if(radd) {
				fprintf(radd," %s %s",q->name,q->phone);
				fclose(radd);
			}
			q = q->next;
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
void show() {
	cout<<"------通讯录------"<<endl;
	cout<<"1.录入信息"<<endl;
	cout<<"2.添加成员"<<endl;
	cout<<"3.删除成员"<<endl;
	cout<<"4.查看成员信息"<<endl;
	cout<<"5.退出程序"<<endl;
}
int main() {
	while(1) {
		system("cls");
		node *head;
		show();
		int x;
		cout<<"请选择："<<endl;
		cin>>x;
		switch(x) {
				//录入信息
			case 1: {
				system("cls");
				head = init();
				head = add(head);
				cout<<"录入完成"<<endl;
				system("pause");
				break;
			}
			//添加信息
			case 2: {
				char name[MAXSIZE],phone[MAXSIZE];
				system("cls");
				head = init();
				head = add(head);
				cout<<"请输入您要添加的姓名"<<endl;
				cin>>name;
				cout<<"请输入您要添加的号吗"<<endl;
				cin>>phone;
				head = insert(head,name,phone);
				cout<<"添加完成"<<endl;
				system("pause");
				break;
			}
			case 3: {
				char name[MAXSIZE];
				system("cls");
				head = init();
				head = add(head);
				cout<<"请输入您要删除的姓名"<<endl;
				cin>>name;
				head = del(head,name);
				cout<<"删除完成"<<endl;
				system("pause");
				break;
			}
			case 4: {
				system("cls");
				head = init();
				head = add(head);
				display(head);
				system("pause");
				break;
			}
			case 5: {
				exit(1);
				break;
			}
		}
	}
	return 0;
}
