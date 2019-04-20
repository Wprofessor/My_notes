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
	vertextype vexs[M][M];//������Ϣ��
	edgetype  edges[M][M];//�ڽӾ���
	node node;
	dx x;
	dy y;
	int n,e;             //��������������
} Mgraph;

void creat(Mgraph *g) { //��ʼ��
	int ri,li;
	FILE *rf;
	rf=fopen("C:/Users/������/Desktop/test.txt","rb");
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
	bool final[M];//�ж��Ƿ�Ϊ��̾���
	int k;
	int v;
	//��ʼ��
	for(int i = 1; i <= g->n; i++) {
		final[i] = false;
		d[i] = g->edges[i][V0];
		//	cout<<d[i]<<endl;
		if(d[i] < FINITY && d[i] > 0) {
			p[i] = V0;//��Ĭ��ǰ����ΪV0
		} else
			p[i] = -1;
	}
	final[V0] = true; //V0�����Ϊ��̾���
	d[V0] = 0;
	for(int i = 2; i <= g->n; i++) {
		int min = FINITY;
		for(k = 1; k <= g->n; k++) {
			if(d[k] < min && !final[k]) {
				min = d[k];
				v=k;   //��¼��ǰ����̾���
			}
		}
		if(min == FINITY)
			break;     //������־
		final[v] = true;
		//ͨ��ǰ����֪����̾��룬���º���ľ���
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
	next[0] = -1;                      //next�����һ��ֵ��Զ��-1
	while(i < strlen(t)) {             //�ٽ�����
		if(j == -1 || t[i] == t[j]) {
			i++;
			j++;
			next[i] = next[j] + 1;
		} else {
			j = next[j];			   //��ǰ�ݹ���nextֵ
		}
	}
}

int KMP(char *s,char *t,int pos,int *next) {
	int i = pos;                       //�������Ҫ���Զ��忪ʼλ��
	int j = 0;
	int len1 = strlen(s),len2 = strlen(t);
	while(i < len1 && j < len2 ) {
		if(s[i] == t[j] || j == -1) {
			i++;
			j++;
		} else {
			j = next[j];               //�ƶ��ľ����������Ӧ��nextֵ
		}
	}
	if(j >= len2) {
		return 1;                      //ƥ��ɹ�����1
	} else {
		return 0;					   //ƥ��ʧ�ܷ���0
	}
}
void print(Mgraph *g,path p,dist d,int i) {
	int stk[M],pre,top=-1;  //��˳��ջ���������
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
	cout<<"���������ĵ�ǰλ��"<<endl;
	cin>>t1;
	get_next(t1,next1);
	cout<<"����������Ŀ��λ��"<<endl;
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
		cout<<"�ܱ�Ǹ��δ�ҵ�����������Ի���������"<<endl;
	return 0;
}
