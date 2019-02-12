#include<bits/stdc++.h>
using namespace std;
#define MAXSIZE 1000000
int main() {
	int m,n,x;
	while(scanf("%d",&m) != EOF){
		set<int> a;
		set<int> b;
		vector<int> result(600);	//直接保存其他容器的元素需要开辟大小，如果插入则不需要 
		for(int i = 0;i < m;i++){
			cin>>x;
			a.insert(x);
		}
		cin>>n;
		for(int i = 0;i < n;i++) {
			cin>>x;
			b.insert(x);
		}
		vector<int>::iterator iter;
		iter = set_intersection(a.begin(),a.end(),b.begin(),b.end(),result.begin()); // 求交集
		result.resize(iter-result.begin());
		cout<<result.size()<<endl;
		a.clear();
		b.clear();
		result.clear(); 
	}
	return 0;
}