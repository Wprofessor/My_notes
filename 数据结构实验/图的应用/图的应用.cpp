#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define FINITY 100000
#define M 50
using namespace std;
typedef int edgetype;
typedef char vertextype;
typedef int dist[M];
typedef int path[M];
typedef int floyddist[M][M];  	//距离
typedef int floydpath[M][M]; 	//路径
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
		for(int i = 1; i <= g->n; i++) {
			fscanf(rt,"%s",&g->vexs[i]);
		}
		for(int i = 1; i <= g->e; i++) {
			for(int j = 0; j < g->e; j++) {
				g->edges[i][j] = FINITY;
				if(i == j)
					g->edges[i][j] = 0;
			}
		}
		int x,y;
		for(int i = 1; i <= g->e; i++) {
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
void  Floyd(Mgraph g,floydpath p,floyddist d) {
	//初始化
	for(int i = 1; i <= g.n; i++) {
		for(int j = 1; j <= g.n; j++) {
			d[i][j] = g.edges[i][j];
			if(i != j && d[i][i < FINITY]) {
				p[i][j] = i;
			} else {
				p[i][j] = -1;
			}
		}
	}
	//暴力求得每对顶点间的最短距离
	//遍历每种可能的情况
	for(int k = 1; k <= g.n; k++)
		for(int i = 1; i <= g.n; i++) {
			for(int j = 1; j <= g.n; j++) {
				if(d[i][j] > (d[i][k] + d[k][j])) {		//类似于链式法则
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = k;	//修改前驱顶点
				}
			}
		}
}
void dijkstraprint(Mgraph *g,path p,dist d,int i) {
	int stk[M],pre,top=-1;  //用顺序栈来进行输出
//	for(int j=1;j<=g->n;j++)
//		cout<<"juli"<<j<<"---"<<d[j]<<endl;
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

}
void Floydprint(Mgraph g,floydpath p,int x,int y) {
	cout<<g.vexs[x]<<"--->";
	while(p[x][y] != -1 && p[x][y] != x) {
		cout<<g.vexs[p[x][y]]<<"--->";
		x = p[x][y];
	}
	cout<<g.vexs[y]<<endl;
}
void show() {
	cout<<"----------图的应用-----------"<<endl;
	cout<<"1.创建邻接矩阵"<<endl;
	cout<<"2.用dijkstra算法求单源最短路"<<endl;
	cout<<"3.用Floyd算法求所有顶点对的最短路径"<<endl;
	cout<<"4.退出程序"<<endl;
	cout<<"温馨提示："<<endl;
	cout<<"如果您是首次使用本程序，建议选则（1）哦！！！"<<endl;
	cout<<"选择源点时要注意是从1开始哦！！！"<<endl; 
	cout<<"请选择您需要的功能："<<endl;
}
int main() {
	int m;
	while(1) {
		system("cls");
		show();
		cin>>m;
		Mgraph g;
		dist d1;		//p1、p2分别代表dijkstra和floyd
		floyddist d2;
		path p1;
		floydpath p2;
		switch(m) {
			case 1: {
				system("cls");
				creat(&g);
				cout<<"创建成功"<<endl;
				system("pause");
				break;
			}
			case 2: {
				system("cls");
				int x,y;
				cout<<"请输入源点"<<endl;
				cin>>x;
				dijkstra(&g,x,p1,d1);
				cout<<"请输入您想到达的地方"<<endl;
				cin>>y;
				cout<<"您的最佳路径是："<<endl;
				dijkstraprint(&g,p1,d1,y);
				system("pause");
				break;
			}
			case 3: {
				system("cls");
				int x,y;
				Floyd(g,p2,d2);
				cout<<"请输入您所在的地方和要去的地方序号:"<<endl;
				cin>>x>>y;
				cout<<"您的最佳路径是："<<endl;
				Floydprint(g,p2,x,y);
				system("pause");
				break;
			}
			case 4: {
				exit(1);
				break;
			}
		}
	}
	return 0;
}
