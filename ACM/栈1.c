/*
HDU - 1022 
STL栈的简单应用 
*/ 
#include<bits/stdc++.h>
using namespace std;
#define MAXSIZE 1000000
int main() {

	int n;
	char in[10],out[10];
	while(scanf("%d",&n) != EOF) {
		stack<char> s;
		int state[20];		//记录列车进出状态 
		cin>>in;
		cin>>out;
		int ok = 0;
		s.push(in[0]);
		state[ok++] = 1;
		int i = 0,j = 0;
		//memset(state,0,sizeof(state));
		while(i < n && j < n) {
			if(s.empty()) {
				s.push(in[++i]);
				state[ok++] = 1;
			} else {
                //若此时栈顶列车ID与O2相等 
				if(s.top() == out[j]) {		
					s.pop();
					state[ok++] = 0;
					j++;
				} else {
					s.push(in[++i]);
					state[ok++] = 1;
				}
			}
		}
		if(j == n) {
			cout<<"Yes."<<endl;
			for(int i = 0; i < n * 2; i++) {
				if(state[i] == 1)
					cout<<"in"<<endl;
				else
					cout<<"out"<<endl;
			}
			cout<<"FINISH"<<endl;
		} else {
			cout<<"No."<<endl;
			cout<<"FINISH"<<endl;
		}
	}
	return 0;
}