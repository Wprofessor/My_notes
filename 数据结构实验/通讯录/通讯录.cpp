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
//¼��
node* add(node *head) {
	node *p,*q;
	p = head;
	int n;
	//�ļ���ȡ
	FILE *rf;
	rf = fopen("C:/Users/������/Desktop/contacts.txt","rb");
	if(rf) {
		fscanf(rf,"%d",&n);
		for(int i = 0; i < n; i++) {
			q = (node*)malloc(sizeof(node));
			fscanf(rf,"%s%s",&q->name,&q->phone);
			if(!p) {
				p = q;
				p->next = NULL;  //ͷ�ڵ��Ѿ��ı�
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
	rf = fopen("C:/Users/������/Desktop/contacts.txt","rb");
	if(rf) {
		fscanf(rf,"%d",&count);
		fclose(rf);
	}
	FILE *rt;
	rt = fopen("C:/Users/������/Desktop/contacts.txt","r+");
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
		p->next = NULL;  //ͷ�ڵ��Ѿ��ı�
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
	radd = fopen("C:/Users/������/Desktop/contacts.txt","a");
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
		cout<<"ɾ�����˲�����"<<endl;
		return head;
	} else {
		FILE *rf;
		int count;
		rf = fopen("C:/Users/������/Desktop/contacts.txt","rb");
		if(rf) {
			fscanf(rf,"%d",&count);
			fclose(rf);
		}
		FILE *radd;
		radd = fopen("C:/Users/������/Desktop/contacts.txt","w");
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
			radd = fopen("C:/Users/������/Desktop/contacts.txt","a");
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
	cout<<"------ͨѶ¼------"<<endl;
	cout<<"1.¼����Ϣ"<<endl;
	cout<<"2.��ӳ�Ա"<<endl;
	cout<<"3.ɾ����Ա"<<endl;
	cout<<"4.�鿴��Ա��Ϣ"<<endl;
	cout<<"5.�˳�����"<<endl;
}
int main() {
	while(1) {
		node *head;
		show();
		int x;
		cout<<"��ѡ��"<<endl;
		cin>>x;
		switch(x) {
				//¼����Ϣ
			case 1: {
				system("cls");
				head = init();
				head = add(head);
				cout<<"¼�����"<<endl;
				system("pause");
				break;
			}
			//�����Ϣ
			case 2: {
				char name[MAXSIZE],phone[MAXSIZE];
				system("cls");
				head = init();
				head = add(head);
				cout<<"��������Ҫ��ӵ�����"<<endl;
				cin>>name;
				cout<<"��������Ҫ��ӵĺ���"<<endl;
				cin>>phone;
				head = insert(head,name,phone);
				cout<<"������"<<endl;
				system("pause");
				break;
			}
			case 3: {
				char name[MAXSIZE];
				system("cls");
				head = init();
				head = add(head);
				cout<<"��������Ҫɾ��������"<<endl;
				cin>>name;
				head = del(head,name);
				cout<<"ɾ�����"<<endl;
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
