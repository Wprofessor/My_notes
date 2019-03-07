//贪心加优先队列
#include<bits/stdc++.h>
const double MAXSIZE = 1000000;
using namespace std;
int main() {
	// 从小到大 
	priority_queue<int,vector<int>,greater<int> > p;
	int n;
	while(scanf("%d",&n) != EOF) {
		int m,f;
		for(int i = 0; i < m; i++) {
			cin>>m;
			int minsum = 0;
			for(int j = 0; j < m; j++) {
				cin>>f;
				p.push(f);
			}
			int x,y,sum = 0;
			while(p.size() >= 2){
				x = p.top();
				p.pop();
				y = p.top();
				p.pop();
				sum += x+y;
				p.push(x+y);
			}
			cout<<sum<<endl;
			p.pop();
		}
	}
	return 0;
}