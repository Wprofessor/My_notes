#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define MAXSIZE 1000000+10
using namespace std;
bool vis[MAXSIZE];
int prime[MAXSIZE],n;
//ËØÊý´ò±í
void getprime() {
	memset(vis,true,sizeof(vis));
	int num = 1;
	for(int i = 2; i <= n; i++) {
		if(vis[i])
			prime[num++] = i;
		for(int j = 1; j <= num && i*prime[j] < n; j++) {
			vis[i*prime[j]] = false;
			if(i % prime[j] == 0)
				break;
		}
	}
}
int main() {
	cin>>n;
	getprime();
	if(vis[n-1])
	cout<<1<<endl;
	return 0;
}
