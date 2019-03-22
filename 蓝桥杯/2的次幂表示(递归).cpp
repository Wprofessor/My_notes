#include<bits/stdc++.h>
const int INF = -0x3f3f3f3f;
const int MAXSIZE = 256;
const int mod = 50000;
using namespace std;
int n,x,y;
vector<int> v;
map<int,int> map1;
stack<int> s;


string transf(int n) {
	int r[MAXSIZE];		//定义为局部变量
	int num = 0;
	int ok = 0;
	while(n) {
		if(n%2 == 1)
			r[num++] = ok;
		ok++;
		n /= 2;
	}
	string str = "";
	for(int i = num - 1; i >= 0; i--) {
		if(r[i] == 0)
			str += "2(0)";
		else if(r[i] == 1)
			str += "2";
		else if(r[i] == 2)
			str += "2(2)";
		else {
			str += "2(";
			str += transf(r[i]);
			str += ")";
		}
		if(i != 0)
			str += "+";
	}
	return str;
}
int main() {
	while(cin >> n) {
		cout << transf(n) << endl;
	}
	return 0;
}

