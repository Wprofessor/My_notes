//分治法求循环赛问题
#include<bits/stdc++.h>
const int MAXSIZE = 100;
using namespace std;
int r[100][100];
int k,n;
//DFS填充矩阵 
void judge(int n) {
	if(n == 1)	//只有一支球队
		r[1][1] = 1;
	else {
		int m = n / 2;
		judge(m);
		//根据左上球队
		for(int i = 1;i <= m;i++){
			for(int j = 1;j <= m;j++){
				r[i][j+m] = r[i][j] + m;	//填充右上球队
				r[i+m][j+m] = r[i][j];		//填充右下球队
				r[i+m][j] = r[i][j] + m;	//填充左下球队
			}
		}
	} 
}
void show(){
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			cout << setw(5) << r[i][j];		//输出填充 
		}
		cout << endl;
	}
}
int main() {
	cout << "一共有2的k次方个成员，请输入k值" << endl;
	while(cin >> k) {
		n = pow(2,k);
		judge(n);
		cout << "循环赛日程表为：" <<endl; 
		show();
		system("pause");
		system("cls");
		cout << "一共有2的k次方个成员，请输入k值" << endl; 
	}
	return 0;
}
