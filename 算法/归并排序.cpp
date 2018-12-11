#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define MAXSIZE 100
typedef int keytype;
using namespace std;
typedef struct {
	keytype key;
	int other;
} recordtype;
typedef struct {
	recordtype r[MAXSIZE];
	int length;
} table;
//将有序段tabs[u,m]和tabs[m+1,v]合并成tabg[u,v]
void merge(table *tabs,table *tabg,int u,int m,int v) {
	int i,j,k;
	i = u;
	j = m+1;
	k = u;
	while(i <= m && j <= v) {  //将两段有序元素表中较小的依次放入tabg中
		if(tabs->r[i].key <= tabs->r[j].key) {
			tabg->r[k] = tabs->r[i];
			i++;
		} else {
			tabg->r[k] = tabs->r[j];
			j++;
		}
		k++;
	}
	if(i <= m) {
		for(int t = i; t <= m; t++) {
			tabg->r[k+t-i] = tabs->r[t];
		}
	} else {
		for(int t = j; t <= v; t++) {
			tabg->r[k+t-j] = tabs->r[t];
		}
	}
}
//将tabs中长度为len的连续有序段使用merge()归并为2*len存入tabg中
void mergepass (table *tabs,table *tabg,int len) {
	int i,n;
	n = tabg->length = tabs->length;
	//从下标1开始 
	i = 1;
	while(i <= n - len*2 +1) {
		merge(tabs,tabg,i,i+len-1,i+2*len-1);
		i += 2*len;
	}
	if(i+len-1 < n) {
		//对剩下的长度不都为len的有序段进行归并
		merge(tabs,tabg,i,i+len-1,n);
	} else {
		for(int j = i; j <= n; j++) {
			tabg->r[j] = tabs->r[j];
		}
	}
}
//归并排序
void mergesort(table *tab) {
	int len = 1;
	table temp;  //中间变量
	while(len < tab->length) {
		mergepass(tab,&temp,len);       //一趟归并，结果存放在temp中
		len *= 2;
		mergepass(&temp,tab,len);		//结果在tab中
		len *= 2;
	}
}
int main() {
	table tab;
	tab.length = 5;
	tab.r[5].key = 5;
	tab.r[1].key = 8;
	tab.r[2].key = 0;
	tab.r[3].key = 4;
	tab.r[4].key = 3;
	mergesort(&tab);
	for(int i = 1;i <= tab.length;i++) {
		cout<<tab.r[i].key<<endl;
	}
	return 0;
}
