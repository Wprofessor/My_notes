#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define FINITY 1000000
#define M 500
using namespace std;
typedef int edgetype;
typedef char vertextype;
typedef int dist[M];
typedef int path[M];
typedef struct {
	vertextype vexs[M][M];//顶点信息域
	edgetype  edges[M][M];//邻接矩阵
	int n,e;             //顶点总数，边数
} Mgraph;
void creat(Mgraph *g) {
	FILE *rt;
	rt = fopen("C:/Users/王教授/Desktop/图的应用.txt","rb");
	if(rt) {
		fscanf(rt,"%d%d",&g->n,&g->e);
		for(int i = 0;i < g->n;i++) {
			fscanf(rt,"%s",&g->vexs[i]);
		}
		for(int i = 0;i < g->e;i++) {
			for(int j = 0;j < g->e;j++) {
				g->edges[i][j] = FINITY;
				if(i == j)
				g->edges[i][j] = 0;
			}
		}
		int x,y;
		for(int i = 0;i < g->e;i++) {
			fscanf(rt,"%d%d",&x,&y);
			fscanf(rt,"%d",&g->edges[x][y]);
			g->edges[y][x] = g->edges[x][y];
		}
		fclose(rt);
	}
}
void dijkstra(Mgraph *g,int V0,path p,dist d) {
	bool final[M];//判断是否为最短距离
	int k;
	int v;
	//初始化
	for(int i = 1; i <= g->n; i++) {
		final[i] = false;
		d[i] = g->edges[i][V0];
		//	cout<<d[i]<<endl;
		if(d[i] < FINITY && d[i] > 0) {
			p[i] = V0;//先默认前驱都为V0
		} else
			p[i] = -1;
	}
	final[V0] = true; //V0本身就为最短距离
	d[V0] = 0;
	for(int i = 2; i <= g->n; i++) {
		int min = FINITY;
		for(k = 1; k <= g->n; k++) {
			if(d[k] < min && !final[k]) {
				min = d[k];
				v=k;   //记录当前的最短距离
			}
		}
		if(min == FINITY)
			break;     //结束标志
		final[v] = true;
		//通过前面已知的最短距离，更新后面的距离
		for(int j = 1; j <= g->n; j++) {
			if(!final[j]&&(min+g->edges[v][j] < d[j])) {
				p[j] = v;
				d[j] = min+g->edges[v][j];
//				cout<<"---"<<p[j]<<endl;
			}

		}
	}

}
void print(Mgraph *g,path p,dist d,int i) {
	int stk[M],pre,top=-1;  //用顺序栈来进行输出
//	for(int i=1;i<=g->n;i++){
//		cout<<"juli"<<i<<"---"<<d[i]<<endl;
	stk[++top]=i;
	//	cout<<top<<endl;
	pre=p[i];
	while(pre!=-1) {
		stk[++top]=pre;
		pre=p[pre];
	}
	while(top>=0) {
		printf(" %s",g->vexs[stk[top--]]);
	}
	cout<<endl;
//	}
}
int main() {

	Mgraph g;
	dist d;
	path p;
	creat(&g);
	dijkstra(&g,0,p,d);
	print(&g,p,d,2);
	cout<<"emmm"<<endl;
	return 0;
}
