//���η���ѭ��������
#include<bits/stdc++.h>
const int MAXSIZE = 100;
using namespace std;
int r[100][100];
int k,n;
//DFS������ 
void judge(int n) {
	if(n == 1)	//ֻ��һ֧���
		r[1][1] = 1;
	else {
		int m = n / 2;
		judge(m);
		//�����������
		for(int i = 1;i <= m;i++){
			for(int j = 1;j <= m;j++){
				r[i][j+m] = r[i][j] + m;	//����������
				r[i+m][j+m] = r[i][j];		//����������
				r[i+m][j] = r[i][j] + m;	//����������
			}
		}
	} 
}
void show(){
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			cout << setw(5) << r[i][j];		//������ 
		}
		cout << endl;
	}
}
int main() {
	cout << "һ����2��k�η�����Ա��������kֵ" << endl;
	while(cin >> k) {
		n = pow(2,k);
		judge(n);
		cout << "ѭ�����ճ̱�Ϊ��" <<endl; 
		show();
		system("pause");
		system("cls");
		cout << "һ����2��k�η�����Ա��������kֵ" << endl; 
	}
	return 0;
}
