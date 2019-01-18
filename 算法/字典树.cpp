#include<bits/stdc++.h>
#define MAXSIZE 50 
using namespace std;
//字典树 
typedef struct tire_node {
	int count;		//记录该节点代表的单词个数
	char word[MAXSIZE];
	bool isStr;		//标记该节点是否构成完整单词
	struct tire_node *children[MAXSIZE];	//各个子节点
} tire;
//相当于建立带头节点的树 
tire *initTire() {	//初始化
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
		if (!node->children[id])		//如果没找到相应的字符 
		{
			node->children[id] = new tire();	//开辟空间
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
//根据单词前缀查找前缀所在的节点位置 
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
		//如果没找到，返回空节点 
		else	 
		{
			return NULL;
		}
	}
	return node;
}
//BFS遍历打印出满足前缀的图书信息
void printTire(tire *root,char *front) {
	int count = 1;
	tire *node = tireSearch(root, front);
	int i;
	if (!node)
	{
		cout << "未匹配到您需要的信息，请重新输入" << endl;
	}
	else
	{
		tire *queue[MAXSIZE];
		int left = 0, right = 0;
		queue[right++] = node;
		//如果队列不为空 
		while (left < right)
		{
			tire *p = queue[left++];
			//如果当前节点表示的是完整的单词就输出 
			if (p->count != 0 && p->isStr)
			{
				cout << p->word<< endl;
			}
			//将当前节点的孩子都加入队列 
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
	cout<<"请输入您查询的名字"<<endl;
	cin>>x;
	printTire(node,x);
	return 0;
} 
