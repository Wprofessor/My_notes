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
			cout << "������Ԫ�صĸ���"  << endl;
			cin >> x;
			cout << "������ÿ��Ԫ�ص�ֵ����Ҫ�ظ�Ŷ��" << endl;
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
	cout << "�����Ľ��Ϊ" << endl; 
	t.showV();
	int k;
	cout << "��������Ҫ�ҵ�Ԫ��ֵ" << endl;
	while(cin >> k) 
	{

		if(t.getIndex(k) != -1) 
		{
			cout << "��Ҫ�ҵ�Ԫ��λ��Ϊ��"  << t.getIndex(k)+1 << endl;
		} 
		else
			cout << "�ܱ�Ǹ��û�ҵ���" << endl;
	}
	return 0;
}
