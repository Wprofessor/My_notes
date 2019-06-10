#include<bits/stdc++.h>
const int INF = 0x3f3f3f3f;
const int MAXSIZE = 505;
const int mod = 50000;
using namespace std;
int n,m;
char map1[MAXSIZE][MAXSIZE];
int d[MAXSIZE][MAXSIZE];
int dx[] = {1,0,0,-1};
int dy[] = {0,-1,1,0};
char dirt[] = "DLRU";
struct node {
	int x,y;
	string str;
};
string str = "";
void BFS() {
	node t;
	queue<node > p;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			d[i][j] = INF;
		}
	}
	d[1][1] = 0;
	node pa;
	pa.x = 1;
	pa.y = 1;
	pa.str = "";
	p.push(pa);
	while(p.size()) {
		pa = p.front();
		p.pop();
		if(pa.x == n && pa.y == m) {
			cout << d[n][m] << endl;
			cout << pa.str << endl;

			break;
		}
		for(int i = 0; i <= 4; i++) {
			node t;
			t.x = pa.x + dx[i];
			t.y = pa.y + dy[i];
			if(t.x >= 1 && t.x <= n && t.y >= 1 && t.y <= m && d[t.x][t.y] == INF && map1[t.x][t.y] != '1') {
				t.str = pa.str + dirt[i];
			//	cout << t.str << "---" << dirt[i] << "(" << t.x << "," << t.y << ")" << endl;
				d[t.x][t.y] = d[pa.x][pa.y] + 1;
				p.push(t);
			}
		}
	}
}
int main() {
	while(cin >> n >> m) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				cin >> map1[i][j];
			}
		}
		BFS();

	}
	return 0;
}
