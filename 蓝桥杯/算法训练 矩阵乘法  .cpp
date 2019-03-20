#include<bits/stdc++.h>
const int INF = -0x3f3f3f3f;
const int MAXSIZE = 250;
const int mod = 50000;
using namespace std;
int m,s,n;
vector<int> v;
int a[MAXSIZE][MAXSIZE],b[MAXSIZE][MAXSIZE],c[MAXSIZE][MAXSIZE];
int main() {
	while(cin >> m >> s >> n) {
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < s; j++) {
				cin >> a[i][j];
			}
		}
		for(int i = 0; i < s; i++) {
			for(int j = 0; j < n; j++) {
				cin >> b[i][j];
			}
		}
		memset(c,0,sizeof(c));
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				for(int k = 0;k < s;k++){
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		for(int i = 0;i < m;i++){
			for(int j = 0;j < n;j++){
				cout << c[i][j];
				if(j < n-1)
				cout << " ";
			}
			cout << endl;
		}
	}
	return 0;
}

