#include<bits/stdc++.h>
#define MAXSIZE 50 
using namespace std;
//�ֵ��� 
typedef struct tire_node {
	int count;		//��¼�ýڵ����ĵ��ʸ���
	char word[MAXSIZE];
	bool isStr;		//��Ǹýڵ��Ƿ񹹳���������
	struct tire_node *children[MAXSIZE];	//�����ӽڵ�
} tire;
//�൱�ڽ�����ͷ�ڵ���� 
tire *initTire() {	//��ʼ��
	tire *root;
	root = (tire *)malloc(sizeof(tire));
	root->count = 0;
	root->isStr = false;
	int i;
	for (i = 0; i < MAXSIZE; i++)
	{
		root->children[i] = NULL;
	}
	return root;
}
void tireInsert(tire **root, char *word) {
	tire *node = *root;
	int i = 0;
	int j;
	int id;
	while (word[i])
	{
		id = word[i] - 'a';
		if (!node->children[id])		//���û�ҵ���Ӧ���ַ� 
		{
			node->children[id] = new tire();	//���ٿռ�
			for (j = 0; j < MAXSIZE; j++)
			{
				node->children[id]->children[j] = NULL;
			}
			node->children[id]->count = 0;
			node->children[id]->isStr = false;
		}
		node = node->children[id];
		node->count++;
		i++;
	}
	node->isStr = true;
	strcpy(node->word,word);
}
//���ݵ���ǰ׺����ǰ׺���ڵĽڵ�λ�� 
tire * tireSearch(tire *root, char *word) {
	tire *node = root;
	int i = 0;
	while (word[i])
	{
		int id = word[i] - 'a';
		if (node->children[id])
		{
			node = node->children[id];
			i++;
		}
		//���û�ҵ������ؿսڵ� 
		else	 
		{
			return NULL;
		}
	}
	return node;
}
//BFS������ӡ������ǰ׺��ͼ����Ϣ
void printTire(tire *root,char *front) {
	int count = 1;
	tire *node = tireSearch(root, front);
	int i;
	if (!node)
	{
		cout << "δƥ�䵽����Ҫ����Ϣ������������" << endl;
	}
	else
	{
		tire *queue[MAXSIZE];
		int left = 0, right = 0;
		queue[right++] = node;
		//������в�Ϊ�� 
		while (left < right)
		{
			tire *p = queue[left++];
			//�����ǰ�ڵ��ʾ���������ĵ��ʾ���� 
			if (p->count != 0 && p->isStr)
			{
				cout << p->word<< endl;
			}
			//����ǰ�ڵ�ĺ��Ӷ�������� 
			for (i = 0; i < MAXSIZE; i++)
			{
				if (p->children[i])
				{
					queue[right++] = p->children[i];
				}
			}
		}
	}
}
int main(){
	tire *node;
	node = initTire();
	tireInsert(&node,"wangjiahao");
	tireInsert(&node,"wangli");
	tireInsert(&node,"wanggayhao");
	tireInsert(&node,"wangnima");
	tireInsert(&node,"zhangwanlin");
	tireInsert(&node,"zhangsan");
	char x[MAXSIZE];
	cout<<"����������ѯ������"<<endl;
	cin>>x;
	printTire(node,x);
	return 0;
} 
