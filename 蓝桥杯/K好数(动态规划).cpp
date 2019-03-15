#include<bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
int dp[100][100];
int main() {
	int K,L;
	while(cin>>K>>L) {
		memset(dp,0,sizeof(dp));
		for(int i = 1; i < K; i++) {
			dp[L][i] = 1;
		}
		for(int i = L - 1; i > 0; i--) {
			for(int j = 0; j < K; j++) {
				int sum = 0;
				for(int r = 0; r < K; r++) {
					if(r - j == 1 || r - j == -1)
						continue;
					sum  = (sum + dp[i+1][r]) % mod;
				}
				dp[i][j] = sum;
			}
		}
		int sum = 0;
		for(int i = 0;i < K;i++){
			sum = (sum + dp[1][i]) % mod;
		}
		cout<<sum<<endl;
	}
	return 0;
}
