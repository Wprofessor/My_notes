#include<bits/stdc++.h>
using namespace std;
int num[10];
int n;
void display(int n) {
	for(int i = 0; i < 10; i++)
		num[i] = i;
	//注意第一位不能为0 
	for(int i = 1; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			if((n - (num[i] + num[j]) * 2 >= 0) && n - (num[i] + num[j]) * 2 <= 9)
				cout << num[i] << num[j] << n - (num[i] + num[j]) * 2 << num[j] << num[i] << endl;
		}
	}
	for(int i = 1; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
		for(int k = 0;k < 10;k++)
			if((num[i] + num[j] + num[k]) * 2 == n)
			cout << num[i] << num[j] << num[k] << num[k] << num[j] << num[i] << endl;
		}
	}
}

int main() {
	while(cin >> n) {
		display(n);
	}
	return 0;
}
