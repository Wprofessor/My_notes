#include<bits/stdc++.h>
using namespace std;
#define MAXSIZE 1000000
int main() {
	int m;
	while(scanf("%d",&m) != EOF) {
		string a;
		string b;
		set<string> v;
		set<string>::iterator iter;
		for(int i = 0; i < m; i++) {
			cin>>a;
			cin>>b;
			if(a == "insert")
				v.insert(b);
			else {
				iter = v.find(b);
				if(iter != v.end())
					cout<<"yes"<<endl;
				else
					cout<<"no"<<endl;
			}
		}
		v.clear();
	}
	return 0;
}