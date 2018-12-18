#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000+10;
int target[maxn];
//输入一组数，判读能否以该顺序完成调度 
int main() {
	int n;
	while(scanf("%d",&n)!=EOF) {
		stack<int> s;
	for(int i = 1;i <= n;i++)
	cin>>target[i];
	int ok = 1,A = 1,B = 1; 	//A是车厢序号，B是已经驶进的车辆数 
	while(B <= n)  {
		if(A == target[B]){
			A++;
			B++;
		}
		else if(!s.empty() && s.top() == target[B]){
			s.pop();
			B++;
		}
		else if (A <= n)
		s.push(A++);
		else {
			ok = 0;
			break;
		}
	}
	if (ok)
	cout<<1<<endl;
	else
	cout<<0<<endl;
	}
	return 0;
}
