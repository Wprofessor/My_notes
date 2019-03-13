#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int c,n,m,t;
char map1[2][10][10];
int d[2][10][10];	//距离起始点的最短距离
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
int sz,sx,sy;	//起始点
int gz,gx,gy;	//终点
struct node {
	int x;
	int y;
	int z;
};
bool ok;	//标记骑士会不会死 
void BFS() {
	queue<node> que;
	//	初始化最短距离
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < n; j++) {
			for(int k = 0; k < m; k++) {
				d[i][j][k] = INF;
			}
		}
	}
	d[sz][sx][sy] = 0;
	node no;
	no.z = sz;
	no.x = sx;
	no.y = sy;
	que.push(no);
	while(que.size()) {
		node temp = que.front();
		que.pop();
		if(temp.z == gz && temp.x == gx && temp.y == gy)
			break;
		for(int i = 0; i < 4; i++) {
			int nx = temp.x + dx[i];
			int ny = temp.y + dy[i];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && d[temp.z][nx][ny] == INF && map1[temp.z][nx][ny] != '*') {
				node ent;
				if(map1[temp.z][nx][ny] == '#') {	//如果是时空穿梭机
					ent.z =  (temp.z == 0 ? 1 : 0);
					d[ent.z][nx][ny] = d[temp.z][temp.x ][temp.y];
					if(map1[ent.z][nx][ny] == '*'){
						ok = false;
						return ;
					}
					ent.x = nx;
					ent.y = ny;
					que.push(ent);
				} else {
					d[temp.z][nx][ny] = d[temp.z][temp.x ][temp.y] + 1;
					ent.z = temp.z;
					ent.x = nx;
					ent.y = ny;
					que.push(ent);
				}
			}

		}
	}
}
int main() {
	while(scanf("%d",&c) != EOF) {
		for(int i = 0; i < c; i++) {
			ok = true;
			cin>>n>>m>>t;
			for(int j = 0; j < 2; j++) {
				for(int k = 0; k < n; k++) {
					cin>>map1[j][k];
					for(int l = 0; l < m; l++) {
						if(map1[j][k][l] == 'S') {
							sz = j;
							sx = k;
							sy = l;
						}
						if(map1[j][k][l] == 'P') {
							gz = j;
							gx = k;
							gy = l;
						}
					}
				}
			}
		}
		BFS();
		if(d[gz][gx][gy] <= t)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	return 0;
}
