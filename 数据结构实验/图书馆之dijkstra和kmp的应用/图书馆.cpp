#include<stdio.h>
#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;
#define FINITY 1000000
#define M 500
typedef int edgetype;
typedef char vertextype;
typedef int dist[M];
typedef int path[M];
typedef int dx[M];
typedef int dy[M];
typedef int node[M];
typedef struct {
	vertextype vexs[M][M];//顶点信息域
	edgetype  edges[M][M];//邻接矩阵
	node node;
	dx x;
	dy y;
	int n,e;             //顶点总数，边数
} Mgraph;

void creat(Mgraph *g) { //初始化
	int ri,li;
	FILE *rf;
	rf=fopen("C:/Users/王教授/Desktop/test.txt","rb");
	if(rf) {
		fscanf(rf,"%d%d",&g->n,&g->e);
		for(int i=1; i<=g->n; i++) {
			fscanf(rf,"%s%d%d%d",&g->vexs[i],&g->x[i],&g->y[i],&g->node[i]);
//			cout<<g->vexs[i]<<g->x[i]<<g->y[i]<<g->node[i]<<endl;
		}
		for(int i = 1; i <= g->n; i++) {
			for(int j = 1; j <= g->n; j++) {
				if(i == j)
					g->edges[i][j] = 0;
				else
					g->edges[i][j] = FINITY;
			}
		}
		for(int i = 1; i <= g->e; i++) {
			fscanf(rf,"%d%d",&ri,&li);
			g->edges[ri][li]=(int)sqrt((g->x[ri]-g->x[li])*(g->x[ri]-g->x[li])+(g->y[ri]-g->y[li])*(g->y[ri]-g->y[li]));
			g->edges[li][ri]=(int)sqrt((g->x[ri]-g->x[li])*(g->x[ri]-g->x[li])+(g->y[ri]-g->y[li])*(g->y[ri]-g->y[li]));
//			cout<<g->edges[ri][li]<<endl;
		}
		g->edges[8][37]=100;
		g->edges[37][8]=100;
		g->edges[9][38]=100;
		g->edges[38][9]=100;
		g->edges[10][39]=100;
		g->edges[39][10]=100;
		g->edges[11][40]=100;
		g->edges[40][11]=100;
		g->edges[12][41]=100;
		g->edges[41][12]=100;
		g->edges[13][42]=100;
		g->edges[42][13]=100;
		g->edges[23][43]=100;
		g->edges[43][23]=100;
		g->edges[24][44]=100;
		g->edges[44][24]=100;
		fclose(rf);
	} else
		g->n=0;
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

void get_next(char *t,int *next) {
	int i = 0,j = -1;
	next[0] = -1;                      //next数组第一个值永远是-1
	while(i < strlen(t)) {             //临界条件
		if(j == -1 || t[i] == t[j]) {
			i++;
			j++;
			next[i] = next[j] + 1;
		} else {
			j = next[j];			   //往前递归找next值
		}
	}
}

int KMP(char *s,char *t,int pos,int *next) {
	int i = pos;                       //根据你的要求自定义开始位置
	int j = 0;
	int len1 = strlen(s),len2 = strlen(t);
	while(i < len1 && j < len2 ) {
		if(s[i] == t[j] || j == -1) {
			i++;
			j++;
		} else {
			j = next[j];               //移动的距离就是所对应的next值
		}
	}
	if(j >= len2) {
		return 1;                      //匹配成功返回1
	} else {
		return 0;					   //匹配失败返回0
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
	path p;
	dist d;
	creat(&g);
	int V0 = -1;
	char t1[M],t2[M];
	int goal = -1;
	int next1[M],next2[M];
	cout<<"请输入您的当前位置"<<endl;
	cin>>t1;
	get_next(t1,next1);
	cout<<"请输入您的目标位置"<<endl;
	cin>>t2;
	get_next(t2,next2);
	for(int i = 1; i <= g.n; i++) {
		if(KMP(g.vexs[i],t1,0,next1)) {
			V0 = i;
			break;
		}
	}
	for(int i = 1; i <= g.n; i++) {
		if(KMP(g.vexs[i],t2,0,next2)) {
			goal = i;
			break;
		}
	}
//	cout<<"dfgdsg"<<endl;
	if(V0 != -1 && goal != -1) {
		dijkstra(&g,V0,p,d);
		print(&g,p,d,goal);
	} else
		cout<<"很抱歉，未找到结果，您可以换个词试试"<<endl;
	return 0;
}
