#include<bits/stdc++.h>
const int MAXSIZE = 1000050;
using namespace std;
int r[MAXSIZE],t[MAXSIZE];
int n,x,val,k,le,ri;
//快排的思想 
int searchk(int left,int right) {
	r[0] = r[left];
	int i = left,j = right;
	while(i < j) {
		while(r[j] <= r[0] && i < j)
			j--;
		r[i] = r[j];
		while(i < j && r[i] >= r[0] )
			i++;
		r[j] = r[i];
	}
	r[i] = r[0];
	return i;
}
void quicksort(int left,int right,int k) {
	int ok = searchk(left,right);

	if(k == ok) {
		cout << r[k] <<endl;
		return ;
	}
	if(ok > k) {
		quicksort(left,ok-1,k);
	} else {
		quicksort(ok+1,right,k);
	}
}
int main() {
	while(cin >> n) {
		for(int i = 1; i <= n; i++) {
			cin >> x;
			t[i] = x;
		}
		cin >> val;
		for(int i = 0; i < val; i++) {
			cin >> le >> ri >> k;
			int ok = 1;
			for(int j = le; j <= ri; j++) {
				r[ok++] = t[j];
			}
			quicksort(1,ri-le+1,k);
		}
	}
	return 0;
}
