//暴力法解决最近点对问题
#include<bits/stdc++.h>
const double MAXSIZE = 1000000;
using namespace std;
//x轴y轴，分别为一一对应关系
vector<double>xt;
vector<double>yt;
double cal(double x1,double y1,double x2,double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
int main() {
	int n;
	while(cout<<"请输入点的个数:"<<endl && scanf("%d",&n) != EOF) {
		double x,y;
		for(int i = 0; i < n; i++) {
			cout<<"请输入点的坐标:"<<endl;
			cin>>x>>y;
			xt.push_back(x);
			yt.push_back(y);
		}
		double mincount = MAXSIZE;
		double x1,y1,x2,y2;
		for(int i = 0; i < xt.size()-1; i++) {
			for(int j = i + 1; j < xt.size(); j++) {
				if(mincount > cal(xt[i],yt[i],xt[j],yt[j])) {
					x1 = xt[i];
					y1 = yt[i];
					x2 = xt[j];
					y2 = xt[j];
					mincount = cal(xt[i],yt[i],xt[j],yt[j]);
				}
			}
		}
		cout<<"最近点对分别是："<<endl;
		cout<<"("<<x1<<","<<y1<<")"<<endl;
		cout<<"("<<x2<<","<<y2<<")"<<endl;
		cout<<"最小距离是："<<endl;
		cout<<mincount<<endl;
		xt.clear();
		yt.clear();
	}
	return 0;
}