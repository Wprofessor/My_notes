#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000+10;
int target[maxn];
//����һ�������ж��ܷ��Ը�˳����ɵ��� 
int main() {
	int n;
	while(scanf("%d",&n)!=EOF) {
		stack<int> s;
	for(int i = 1;i <= n;i++)
	cin>>target[i];
	int ok = 1,A = 1,B = 1; 	//A�ǳ�����ţ�B���Ѿ�ʻ���ĳ����� 
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
