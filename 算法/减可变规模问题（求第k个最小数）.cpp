//减可变规模问题
//求一个n个数的列表的第k个最小元素的问题
#include<bits/stdc++.h>
const int MAXSIZE = 100;
using namespace std;
int r[MAXSIZE];
int n,k,x;
int searchk(int left,int right) {
	r[0] = r[left];
	int i = left,j = right;
	while(i < j) {
		while(r[j] >= r[0] && i < j)
			j--;
		if(i < j)
			r[i] = r[j];
		while(i < j && r[i] <= r[0] )
			i++;
		if(i < j)
			r[j] = r[i];
	}
	r[i] = r[0];
	return i;
}
void quicksort(int left,int right,int k) {
	int ok = searchk(left,right);
	if(k == ok) {
		cout << "第k个最小元素为：" << r[k] <<endl;
		return ;
	}
	if(ok > k) {
		quicksort(left,ok-1,k);
	} else {
		quicksort(ok+1,right,k);
	}
}
int main() {
	cout << "请分别输入元素个数n和所要求的k的值:" << endl;
	while(cin >> n >> k) {
		cout << "请输入这n个元素:" << endl;
		for(int i = 1; i <= n; i++) {
			cin >> x;
			r[i] = x;
		}
		quicksort(1,n,k);
		system("pause");
		system("cls");
		cout << "请分别输入元素个数n和所要求的k的值:" << endl;
	}
	return 0;
}

