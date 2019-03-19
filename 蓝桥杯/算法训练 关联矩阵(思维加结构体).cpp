#include<bits/stdc++.h>
const int INF = 99999999;
const int MAXSIZE = 1200;
using namespace std;
int d[MAXSIZE][MAXSIZE];
int n,m;
struct edge {
	int x,y;
} ed[MAXSIZE];
int main() {
	while(cin >> n >> m) {
		memset(d,0,sizeof(d));
		int ok = 1;
		int x,y;
		for(int i = 1; i <= m; i++) {
			cin >> x >> y;
			ed[ok].x = x;
			ed[ok++].y = y;
		}
		for(int i = 1;i <= n;i++){
			for(int j = 1;j < ok;j++){
				if(ed[j].x != i && ed[j].y != i)
				d[i][j] = 0;
				else if(ed[j].x == i)
				d[i][j] = 1;
				else
				d[i][j] = -1;
			}
		}
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				cout << d[i][j] ;
				if(j < m)
				cout << " ";
			} 
			cout << endl;
		}
	}
	return 0;
}
