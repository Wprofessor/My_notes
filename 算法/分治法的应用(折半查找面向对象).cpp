#include<bits/stdc++.h>
using namespace std;
class Bisearch 
{
	private:
		vector<int> v;
	public:
		Bisearch() 
		{
			int x,y;
			cout << "请输入元素的个数"  << endl;
			cin >> x;
			cout << "请输入每个元素的值，不要重复哦！" << endl;
			for(int i = 0; i < x; i++) 
			{
				cin >> y;
				this->v.push_back(y);
			}
		}
		void SetV() 
		{
			sort(this->v.begin(),this->v.end());
		}
		void showV()
		{
			for(int i = 0;i < this->v.size();i++)
			{
				cout << this->v[i] << " ";
			}
			cout << endl;
		}
		int getIndex(int k) 
		{
			int l = 0,r = this->v.size()-1;
			int mid;
			while(l <= r) 
			{
				mid = (l + r) / 2;
				if(this->v[mid] == k)
					return mid;
				else if(this->v[mid] > k)
					r = mid -1 ;
				else
					l = mid + 1;
			}
			return -1;
		}
};
int main() 
{
	Bisearch t;
	t.SetV();
	cout << "排序后的结果为" << endl; 
	t.showV();
	int k;
	cout << "请输入您要找的元素值" << endl;
	while(cin >> k) 
	{

		if(t.getIndex(k) != -1) 
		{
			cout << "您要找的元素位置为："  << t.getIndex(k)+1 << endl;
		} 
		else
			cout << "很抱歉，没找到！" << endl;
	}
	return 0;
}
