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
typedef int floyddist[M][M];  	//����
typedef int floydpath[M][M]; 	//·��
typedef struct {
	vertextype vexs[M][M];//������Ϣ��
	edgetype  edges[M][M];//�ڽӾ���
	int n,e;             //��������������
} Mgraph;
void creat(Mgraph *g) {
	FILE *rt;
	rt = fopen("C:/Users/������/Desktop/ͼ��Ӧ��.txt","rb");
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
void  Floyd(Mgraph g,floydpath p,floyddist d) {
	//��ʼ��
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
	//�������ÿ�Զ�������̾���
	//����ÿ�ֿ��ܵ����
	for(int k = 1; k <= g.n; k++)
		for(int i = 1; i <= g.n; i++) {
			for(int j = 1; j <= g.n; j++) {
				if(d[i][j] > (d[i][k] + d[k][j])) {		//��������ʽ����
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = k;	//�޸�ǰ������
				}
			}
		}
}
void dijkstraprint(Mgraph *g,path p,dist d,int i) {
	int stk[M],pre,top=-1;  //��˳��ջ���������
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
	cout<<"----------ͼ��Ӧ��-----------"<<endl;
	cout<<"1.�����ڽӾ���"<<endl;
	cout<<"2.��dijkstra�㷨��Դ���·"<<endl;
	cout<<"3.��Floyd�㷨�����ж���Ե����·��"<<endl;
	cout<<"4.�˳�����"<<endl;
	cout<<"��ܰ��ʾ��"<<endl;
	cout<<"��������״�ʹ�ñ����򣬽���ѡ��1��Ŷ������"<<endl;
	cout<<"ѡ��Դ��ʱҪע���Ǵ�1��ʼŶ������"<<endl; 
	cout<<"��ѡ������Ҫ�Ĺ��ܣ�"<<endl;
}
int main() {
	int m;
	while(1) {
		system("cls");
		show();
		cin>>m;
		Mgraph g;
		dist d1;		//p1��p2�ֱ����dijkstra��floyd
		floyddist d2;
		path p1;
		floydpath p2;
		switch(m) {
			case 1: {
				system("cls");
				creat(&g);
				cout<<"�����ɹ�"<<endl;
				system("pause");
				break;
			}
			case 2: {
				system("cls");
				int x,y;
				cout<<"������Դ��"<<endl;
				cin>>x;
				dijkstra(&g,x,p1,d1);
				cout<<"���������뵽��ĵط�"<<endl;
				cin>>y;
				cout<<"�������·���ǣ�"<<endl;
				dijkstraprint(&g,p1,d1,y);
				system("pause");
				break;
			}
			case 3: {
				system("cls");
				int x,y;
				Floyd(g,p2,d2);
				cout<<"�����������ڵĵط���Ҫȥ�ĵط����:"<<endl;
				cin>>x>>y;
				cout<<"�������·���ǣ�"<<endl;
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
