#include<stdio.h>
#include<iostream>
using namespace std;
long long int kind(int x,int y) {
	long long int sum[100];
	sum[1] = 1;
	sum[2] = 2;
	for(int i = 3;i < 80;i++)
	sum[i] = sum[i-1]+sum[i-2];
	return sum[y-x];
}
int main() {
	int n,x,y;
	while(scanf("%d",&n) != EOF) {
		for(int i = 0; i < n; i++) {
			cin>>x>>y;
			//printf("%lld\n",kind(x,y));
			cout<<kind(x,y)<<endl;
		}
	}
	return 0;
}