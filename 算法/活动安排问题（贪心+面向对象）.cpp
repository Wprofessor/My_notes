#include<bits/stdc++.h>
using namespace std;
const int MAXSIZE = 100;
class Arrange {
	private:
		string name;
		int start;
		int end;
	public:
		Arrange() {
			cout << "请输入活动名称，开始时间和结束时间" << endl;
			cin >> name >> start >> end;
		}
		string getName() {
			return name;
		} 
		int getStart(){
			return start;
		}
		int getEnd(){
			return end;
		}
		friend bool cmp(Arrange x,Arrange y);
};
bool cmp(Arrange x,Arrange y) {
	if(x.end == y.end)
		return x.start > y.start;
	return x.end < y.end;
}
int main() {
	int n;
	cout << "请输入活动总数:" << endl;
	while(cin >> n) {
		Arrange act[n];
		sort(act,act+n,cmp);
		cout << "最优活动安排是：" << endl;
		cout << act[0].getName() << " ";
		int ok = 0;
		for(int i = 1; i < n; i++) {
			if(act[i].getStart() >= act[ok].getEnd()) {
				cout << act[i].getName() << " ";
				ok = i;
			}
		}
		cout << endl;
	}
	return 0;
}
