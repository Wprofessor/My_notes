#include<bits/stdc++.h>
const int INF = -0x3f3f3f3f;
const int MAXSIZE = 256;
const int mod = 50000;
using namespace std;
int n,x,y;
string str;
vector<int> v;
map<int,int> map1;
stack<int> s;
int main() {
	getline(cin,str);	//在string中输入带有空格的字符串
	for(int i = str.size() - 1; i >= 0; i--) {
		if(str[i] != ' ' && str[i] >= '0' && str[i] <= '9') {
			s.push(str[i] - '0');
		}
	}
	string temp = "";
	for(int i = str.size() - 1; i >= 0; i--) {
		if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			temp += str.substr(i,i+1);
	}
	int sum;
	for(int i = 0; i < temp.size(); i++) {
		x = s.top();
		s.pop();
		y = s.top();
		s.pop();
		switch(temp[i]) {
			case '+':
				sum = x + y;
				s.push(sum);
				break;
			case '-':
				sum = x - y;
				s.push(sum);
				break;
			case '*':
				sum = x * y;
				s.push(sum);
				break;
			case '/':
				sum = x / y;
				s.push(sum);
				break;
		}
	}
	cout << s.top() << endl;
	s.pop();
	return 0;
}

