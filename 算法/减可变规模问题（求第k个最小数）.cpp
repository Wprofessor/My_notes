//���ɱ��ģ����
//��һ��n�������б�ĵ�k����СԪ�ص�����
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
		cout << "��k����СԪ��Ϊ��" << r[k] <<endl;
		return ;
	}
	if(ok > k) {
		quicksort(left,ok-1,k);
	} else {
		quicksort(ok+1,right,k);
	}
}
int main() {
	cout << "��ֱ�����Ԫ�ظ���n����Ҫ���k��ֵ:" << endl;
	while(cin >> n >> k) {
		cout << "��������n��Ԫ��:" << endl;
		for(int i = 1; i <= n; i++) {
			cin >> x;
			r[i] = x;
		}
		quicksort(1,n,k);
		system("pause");
		system("cls");
		cout << "��ֱ�����Ԫ�ظ���n����Ҫ���k��ֵ:" << endl;
	}
	return 0;
}

