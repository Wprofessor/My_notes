#include<bits/stdc++.h>
#include<iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXSIZE = 100009;
const int mod = 50000;
int n,k;
int hi[MAXSIZE],wi[MAXSIZE];
bool check(int ans){
	int ok = 0;
	for(int i = 0;i < n;i++){
		ok += ((hi[i]/ans) * (wi[i]/ans));
	}
	if(ok < k)
	return false;
	return true;
}
int main()
{
	while(cin >> n >> k){
		for(int i = 0;i < n;i++){
			cin >> hi[i] >> wi[i];	
		}
		int l = 0,r = 100000;
		int mid;
		int ok;
		while(l <= r){
			mid = (l+r)/2;
			if(check(mid)){
			ok = mid;
			l = mid + 1;
			}else
			r = mid - 1;
		}
		cout << ok << endl;
	}
    return 0;
}
