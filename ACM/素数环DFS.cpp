#include<bits/stdc++.h>
using namespace std;
int n;
int tag[20],save[20];
// ÅĞ¶ÏxÊÇ·ñÊÇËØÊı 
int prime(int x) {
	for(int i = 2; i <= int(sqrt(x)); i++) {
		if(x % i == 0)
			return 0;
	}
	return 1;
}
void DFS(int x){
	if(x == n && prime(1 + save[n-1])){
		for(int i = 0;i < n;i++){
			cout<<save[i];
			if(i < n-1)
			cout<<" ";
		}
		cout<<endl; 
	}
	for(int i = 2;i <= n;i++){
		if(tag[i] == 0 && prime(save[x-1] + i)){
			tag[i] = 1;
			save[x] = i;
			DFS(x+1);
			tag[i] = 0;
		}
	}
}
int main() {
	int ok = 1;
	while(scanf("%d",&n) != EOF) {
		memset(tag,0,sizeof(tag));
		memset(save,0,sizeof(save));
		save[0] = 1;
		cout<<"Case "<<ok++<<":"<<endl;
		DFS(1);
		cout<<endl;
	}
	return 0;
}
