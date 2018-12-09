#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#define M 10000
using namespace std;
typedef struct {
	char  card[20];	//卡号
	char  name[10];	//姓名
	char   dpm[50];	//系别
	char ccode[20];	//班号
} student;
typedef struct {
	student stu[M];
	int length;
} studentlist;
//初始化
void init(studentlist *list) {
	FILE *rt;
	rt = fopen("c:/Users/王教授/Desktop/sort.txt","rb");
	if(rt) {
		fscanf(rt,"%d",&list->length);
		for(int i = 1; i <= list->length; i++) {
			fscanf(rt,"%s%s%s%s",list->stu[i].card,list->stu[i].name,list->stu[i].dpm,list->stu[i].ccode);
		}
	}
	fclose(rt);
}
//根据卡号的大小进行排序
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
	cout<<"-------------排序的应用--------------"<<endl;
	cout<<"1.导入借书信息"<<endl;
	cout<<"2.根据卡号进行升序排序"<<endl;
	cout<<"3.已知卡号查找对应的学生信息"<<endl;
	cout<<"4.查找某个学生所有的借书记录"<<endl;
	cout<<"5.查找某个系别所有的借书记录" <<endl;
	cout<<"6.查找某个班所有的借书记录"<<endl;
	cout<<"7.退出程序"<<endl;
	cout<<"温馨提示："<<endl;
	cout<<"建议先选择功能1和功能2哦！！！"<<endl;
	cout<<"请选择您要的功能"<<endl;
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
				cout<<"导入成功"<<endl;
				system("pause");
				break;
			}
			case 2: {
				system("cls");
				quicksort(&list,1,list.length);
				cout<<"排序成功"<<endl;
				system("pause");
				break;
			}
			case 3: {
				system("cls");
				char card[20];
				cout<<"请输入卡号"<<endl;
				cin>>card;
				while(findcard(list,card) == -1) {
					cout<<"您输入的卡号有误，请重新输入"<<endl;
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
				cout<<"请输入学生姓名"<<endl;
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
				cout<<"请输入系别"<<endl;
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
				cout<<"请输入班号"<<endl;
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
