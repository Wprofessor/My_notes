#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
char map1[5][5];
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
int tag[5][5];
int n;
int MAX;
int judge(int x,int y) {
	if(map1[x][y] == 'X')
		return 0;
	if(tag[x][y] == 1)
		return 0;
	//判断列能不能放炮台
	for(int i = y; i >= 0; i--) {
		if(tag[i][y] == 1)
			return 0;
		if(map1[i][y] == 'X')
			break;
	}
	for(int i = y+1; i < n; i++) {
		if(tag[i][y] == 1)
			return 0;
		if(map1[i][y] == 'X')
			break;
	}
	//判断行能不能放炮台
	for(int i = x; i >= 0; i--) {
		if(tag[x][i] == 1)
			return 0;
		if(map1[x][i] == 'X')
			break;
	}
	for(int i = x+1; i < n; i++) {
		if(tag[x][i] == 1)
			return 0;
		if(map1[x][i] == 'X')
			break;
	}
	return 1;
}
void DFS(int ok) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(judge(i,j)) {
				tag[i][j] = 1;
				DFS(ok+1);
				tag[i][j] = 0;
			}
		}
	}
	if(MAX < ok)
		MAX = ok;
	return ;
}
int main() {
	while(scanf("%d",&n) != EOF) {
		MAX = 0;
		memset(tag,0,sizeof(tag));
		if(n == 0)
			break;
		for(int i = 0; i < n; i++) {
			cin>>map1[i];
		}
		DFS(0);
		cout<<MAX<<endl;
	}
	return 0;
}