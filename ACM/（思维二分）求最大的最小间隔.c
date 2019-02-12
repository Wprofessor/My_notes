#include<bits/stdc++.h>
using namespace std;
#define MAXSIZE 1000000
vector<int> v;
//判断这个间隔是否成立
bool judge(int h,int count) {
	int num = 1;
	int val = v[0];
	for(int i = 1; i < v.size(); i++) {
		if((v[i] - val) >= h) {
			val = v[i];
			num++;
		}
	}
	if(num >= count)
		return true;
	return false;
}
int main() {
	int m,n;
	while(scanf("%d%d",&m,&n) != EOF) {
		int x;
		for(int i = 0; i < m; i++) {
			cin>>x;
			v.push_back(x);
		}
		sort(v.begin(),v.begin() + v.size());
		if(m == n) {
			int min = v[0];
			for(int i = 1; i < v.size(); i++) {
				if((v[i] - v[i-1]) < min)
					min = (v[i] - v[i-1]);
				cout<<min<<endl;
			}
		} else {
			int low = 1,high = v[v.size()-1]-v[0];
			int mid;
			int ok = 0;
			//用二分法在第一个和最后一个畜栏之间的距离寻找最恰当的距离
			while(low <= high) {
				mid = (low+high)/2;
				if(judge(mid,n)) {
					ok = mid;
					low = mid+1;
				} else
					high = mid-1;
			}
			cout<<ok<<endl;
		}
		v.clear();
	}
	return 0;
}