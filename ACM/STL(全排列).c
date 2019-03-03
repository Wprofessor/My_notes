 
#include<bits/stdc++.h>
using namespace std;
vector<int> arr;
int main() {
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 0;i < n;i++){
			arr.push_back(i+1);
		}
		int ok = 1;
		//next_permutation:由小到大全排列
		//prev_permutation：由大到小全排列 
		while(next_permutation(arr.begin(),arr.end())){
			if(ok == m-1){
				for(int i = 0;i < n;i++){
					cout<<arr[i];
					if(i < n-1)
					cout<<" ";
				}
				cout<<endl;
				arr.clear();
				break;
			}
			ok++;
		}
	}
	return 0;
}