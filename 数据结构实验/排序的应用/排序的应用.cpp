#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#define M 10000
using namespace std;
typedef struct {
	char  card[20];	//����
	char  name[10];	//����
	char   dpm[50];	//ϵ��
	char ccode[20];	//���
} student;
typedef struct {
	student stu[M];
	int length;
} studentlist;
//��ʼ��
void init(studentlist *list) {
	FILE *rt;
	rt = fopen("c:/Users/������/Desktop/sort.txt","rb");
	if(rt) {
		fscanf(rt,"%d",&list->length);
		for(int i = 1; i <= list->length; i++) {
			fscanf(rt,"%s%s%s%s",list->stu[i].card,list->stu[i].name,list->stu[i].dpm,list->stu[i].ccode);
		}
	}
	fclose(rt);
}
//���ݿ��ŵĴ�С��������
void quicksort(studentlist *list,int low,int high) {
	int i,j;
	if(low < high) {
		list->stu[0] = list->stu[low];
		i = low;
		j = high;
		do {
			while(i < j && strcmp(list->stu[0].card,list->stu[j].card) == -1)
				j--;
			if(i < j) {
				list->stu[i] = list->stu[j];
				i++;
			}
			while(i < j && strcmp(list->stu[0].card,list->stu[j].card) == 1)
				i++;
			if(i < j) {
				list->stu[j] = list->stu[i];
				j--;
			}
		} while(i != j);
		list->stu[i] = list->stu[0];
		quicksort(list,low,i-1);
		quicksort(list,i+1,high);
	}
}
int findcard(studentlist list,char c[]) {
	int low = 1,high = list.length;
	while(low <= high) {
		int mid = (low + high)/2;
		if(strcmp(list.stu[mid].card,c) == 0) {
			return mid;
		} else {
			if(strcmp(list.stu[mid].card,c) == 1) {
				high = mid - 1;
			} else if (strcmp(list.stu[mid].card,c) == -1)
				low = mid + 1;
		}
	}
	return -1;
}
void show() {
	cout<<"-------------�����Ӧ��--------------"<<endl;
	cout<<"1.���������Ϣ"<<endl;
	cout<<"2.���ݿ��Ž�����������"<<endl;
	cout<<"3.��֪���Ų��Ҷ�Ӧ��ѧ����Ϣ"<<endl;
	cout<<"4.����ĳ��ѧ�����еĽ����¼"<<endl;
	cout<<"5.����ĳ��ϵ�����еĽ����¼" <<endl;
	cout<<"6.����ĳ�������еĽ����¼"<<endl;
	cout<<"7.�˳�����"<<endl;
	cout<<"��ܰ��ʾ��"<<endl;
	cout<<"������ѡ����1�͹���2Ŷ������"<<endl;
	cout<<"��ѡ����Ҫ�Ĺ���"<<endl;
}
int main() {
	studentlist list;
	init(&list);
	quicksort(&list,1,list.length);
	for(int i = 1; i <= list.length; i++)
		cout<<list.stu[i].card<<endl;
	int x;
	while(1) {
		system("cls");
		show();
		cin>>x;
		switch(x) {
			case 1: {
				system("cls");
				init(&list);
				cout<<"����ɹ�"<<endl;
				system("pause");
				break;
			}
			case 2: {
				system("cls");
				quicksort(&list,1,list.length);
				cout<<"����ɹ�"<<endl;
				system("pause");
				break;
			}
			case 3: {
				system("cls");
				char card[20];
				cout<<"�����뿨��"<<endl;
				cin>>card;
				while(findcard(list,card) == -1) {
					cout<<"������Ŀ�����������������"<<endl;
					cin>>card;
				}
				cout<<list.stu[findcard(list,card)].card<<"---"<<list.stu[findcard(list,card)].name
				    <<"---"<<list.stu[findcard(list,card)].dpm<<"---"<<list.stu[findcard(list,card)].ccode<<endl;
				system("pause");
				break;
			}
			case 4: {
				system("cls");
				char name[10];
				cout<<"������ѧ������"<<endl;
				cin>>name;
				for(int i = 1; i <= list.length; i++) {
					if(strcmp(name,list.stu[i].name) == 0)
						cout<<list.stu[i].card<<"---"<<list.stu[i].name
						    <<"---"<<list.stu[i].dpm<<"---"<<list.stu[i].ccode<<endl;
				}
				system("pause");
				break;
			}
			case 5: {
				system("cls");
				char dpm[50];
				cout<<"������ϵ��"<<endl;
				cin>>dpm;
				for(int i = 1; i <= list.length; i++) {
					if(strcmp(dpm,list.stu[i].dpm) == 0)
						cout<<list.stu[i].card<<"---"<<list.stu[i].name
						    <<"---"<<list.stu[i].dpm<<"---"<<list.stu[i].ccode<<endl;
				}
				system("pause");
				break;
			}
			case 6: {
				system("cls");
				char ccode[20];
				cout<<"��������"<<endl;
				cin>>ccode;
				for(int i = 1; i <= list.length; i++) {
					if(strcmp(ccode,list.stu[i].ccode) == 0)
						cout<<list.stu[i].card<<"---"<<list.stu[i].name
						    <<"---"<<list.stu[i].dpm<<"---"<<list.stu[i].ccode<<endl;
				}
				system("pause");
				break;
			}
			case 7: {
				exit(1); 
				break;
			}
		}
	}
	return 0;
}
