#include<bits/stdc++.h>
const int INF = -0x3f3f3f3f;
const int MAXSIZE = 256;
const int mod = 50000;
using namespace std;
int n,m;
vector<int> v;
map<int,int> map1;
stack<int> s;
int r[MAXSIZE][MAXSIZE];
int sum(){
	for(int i = n-1;i >= 1;i--){
		for(int j = 0;j <= i;j++){
			r[i][j] += max(r[i+1][j],r[i+1][j+1]);
		} 
	}
	return r[1][1];
}
int main() {
	while(cin >> n ) {
		memset(r,0,sizeof(r));
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= i;j++){
				cin >> r[i][j];
			}
		}
		cout << sum() << endl;
	}
	return 0;
}

