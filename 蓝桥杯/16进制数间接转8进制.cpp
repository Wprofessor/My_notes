//���������16����λ����������Ƚ�16����ת��2���ƣ��ٽ�2����ת��8����
//һλ16���Ƶ���4λ�����ƣ�һλ8���Ƶ���3λ������ 
#include<bits/stdc++.h>
using namespace std;
int save[1000];
string str;
void display(string str) {
	string s2 = "";
	for(int i = 0;i < str.size();i++){
		switch(str[i]){
			case '0': s2 += "0000";break;
			case '1': s2 += "0001";break;
			case '2': s2 += "0010";break;
			case '3': s2 += "0011";break;
			case '4': s2 += "0100";break;
			case '5': s2 += "0101";break;
			case '6': s2 += "0110";break;
			case '7': s2 += "0111";break;
			case '8': s2 += "1000";break;
			case '9': s2 += "1001";break;
			case 'A': s2 += "1010";break;
			case 'B': s2 += "1011";break;
			case 'C': s2 += "1100";break;
			case 'D': s2 += "1101";break;
			case 'E': s2 += "1110";break;
			case 'F': s2 += "1111";break;
		}
	}
	if(s2.size() % 3 == 1)
	s2 = "00" + s2;
	else if(s2.size() % 3 == 2)
	s2 = "0" + s2;
	for(int i = 0;i < s2.size();i += 3){
		int num = (s2[i] - '0') * 4 + (s2[i+1] - '0') * 2 + (s2[i+2] - '0');
		if(i == 0 && num == 0)
		continue;
		cout << num;
	}
	cout << endl;
}

int main() {
	int n;
	while(cin >> n) {
		for(int i = 0;i < n;i++){
			cin >> str;
			display(str);
		}
	}
	return 0;
}

