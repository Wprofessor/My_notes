# HDU 1010
### 题意:根据地图,'S'为开始位置,'D'为门的位置,' . '为空地,'X'为墙,不能经过,
### 问:在指定的时间,是否能到达'门'的位置.
### 注意:路不可以重复经过,时间也要刚好是 t ,不能少.
### 解题思路，只能用DFS，用BFS是求最短距离的，与题意不符，而一般的DFS会超时，因此要进行剪枝，此题可以是奇偶剪枝，因为无论怎么走，当前位置到终点的步数与最短路的步数之差必然是偶数。

# AC代码
```
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
char map1[10][10];
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
int n,m,t;
int time;
int l,r;	//起点所在位置
//终点所在的位置
int sx,sy;
bool ok;
int judge(int x,int y) {
	if(x < 0 || x >= n || y < 0 || y >= m)
		return 0;
	return 1;
}
//求绝对值
int abs(int x) {
	return x > 0 ? x : (-x);
}
void DFS(int x,int y,int time) {
	if(ok)
		return ;
	if(judge(x,y) == 0)
		return ;
	if(x == sx && y == sy && time == t) {
		ok = true;
		return ;
	}
	int val = (t - time - (abs(x - sx) + abs(y - sy)));
	if(val < 0 || val & 1)	//如果偏离的道路是奇数（位运算） 
		return ;
	for(int i = 0; i <  4; i++) {
		int xx = x + dx[i];
		int yy = y + dy[i];
		if(judge(xx,yy) && map1[xx][yy] != 'X') {
			map1[xx][yy] = 'X';
			DFS(xx,yy,time+1);
			map1[xx][yy] = '.';
			if(ok)
				return ;
		}
	}

}
int main() {
	while(scanf("%d%d%d",&n,&m,&t) != EOF) {
		if(n == 0)
			break;
		int count = 0;
		for(int i = 0; i < n; i++) {
			cin>>map1[i];
			for(int j = 0; j < m; j++) {
				if(map1[i][j] == 'D') {
					sx = i;
					sy = j;
				}
				if(map1[i][j] == 'S') {
					l = i;
					r = j;
				}
				if(map1[i][j] == 'X')
					count++;
			}
		}
		if(m*n - count - 1 < t){
			cout<<"NO"<<endl;
			continue;
		}
		ok = false;
		time = 0;
		map1[l][r] = 'X';
		DFS(l,r,time);
		if(ok)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	return 0;
}
```