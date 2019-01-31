# HDU - 1004 
```
#include<bits/stdc++.h>
using namespace std;
#define MAXSIZE 1000000
int main() {
	int n;
	while(scanf("%d",&n) != EOF) {
		if(n == 0)
		break;
		string color;
		map<string,int> m;
		for(int i = 0; i < n; i++) {
			cin>>color;
			m[color]++;
		}
		map<string ,int>::iterator iter;
		int max = -1;
		string temp;
		for(iter = m.begin(); iter != m.end(); iter++) {
			if((*iter).second > max) {
				max = (*iter).second;
				temp = (*iter).first;
			}
		}
		cout<<temp<<endl;
		m.clear();
	}
	return 0;
}
```
# HDU-1075
```
#include<bits/stdc++.h>
using namespace std;
#define MAXSIZE 1000000
int main() {
	string s;
	map<string,string> m;
	cin>>s;
	string a,b;
	while(cin>>a && a != "END") {
		cin>>b;
		m[b] = a;
	}
	getchar();
	char alpha;
	char ad[3050];
	int ok = 0;
	cin>>s;
	getchar();
	while(scanf("%c",&alpha)) {
		if(isalpha(alpha))
			ad[ok++] = alpha;
		else {

			ad[ok] = '\0';
			ok = 0;
			if(strcmp(ad,"END") == 0)
				break;
			if(m.find(ad) != m.end()) {
			//	cout<<"--------"<<endl;
				cout<<m[ad];
			} else
				cout<<ad;
			//cout<<m[ad]<<"-----------"<<endl;
			cout<<alpha;
		}
	}

	return 0;
}
```