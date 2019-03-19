#include<bits/stdc++.h>
const int MAXSIZE = 100050;
using namespace std;
vector<vector<int> > v;
//dp[i][0]表示不取i结点的结果,dp[i][1]表示取i结点的结果
int dp[MAXSIZE][2];
//node表示当前节点,pre表示前驱节点
void DFS(int node,int pre) {
	for(int i = 0;i < v[node].size();i++){
		int temp = v[node][i];
		if(temp != pre){
			DFS(temp,node);
			dp[node][0] += max(dp[temp][0],dp[temp][1]);
			dp[node][1] += dp[temp][0]; 
		}
	}
}
int main() {
	int n;
	while(cin >> n) {
		int x,y;
		for(int i = 1; i <= n; i++) {
			cin >> dp[i][1]; 
		}
		v.resize(n+1);
		for(int i = 1;i <= n-1; i++){
			cin >> x >> y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
		DFS(1,0);
		cout << max(dp[1][0],dp[1][1]) <<endl;
	}
	return 0;
}
