//穷竭搜索 
#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
vector<int> data;
bool judge(vector<int>data,int sum,int i,int count) {
	if(sum == 0)
	return true;
	if(i == count)
	return false;
	bool result =  judge(data,sum,i+1,count) || judge(data,sum-data[i],i+1,count);
	return result;
}
int main() {
	int n,x;
	while(scanf("%d",&n) != EOF) {
		for(int i = 0; i < n; i++) {
			cin>>x;
			data.push_back(x);
		}
		int ok = n;
		cin>>n;
		for(int i = 0; i < n; i++) {
			cin>>x;
			if(judge(data,x,0,ok))
				cout<<"yes"<<endl;
			else
				cout<<"no"<<endl;
		}
	}
	return 0;
}