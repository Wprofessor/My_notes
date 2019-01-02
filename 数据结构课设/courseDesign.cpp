#include <winsock.h>
#include <iostream>
#include <string.h>
#include<stdlib.h>
#include <mysql.h>
#include<time.h>
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning( disable : 4996 )	//防止time函数报错
#define MAXSIZE 50
using namespace std;
typedef struct b {			//图书信息表
	int number;				//序号
	char ISBN[20];			//书号
	char book_name[50];		//书名
	char spell[100];		//书名拼音
	char type[30];			//类别
	char writer[15];		//作者
	char intro[200];		//简介
	char is_or_no[10];      //是否在管
	int standing_stock;		//现存量
	int repertory;			//库存
	char remark[200];		//备注
	int popular;			//受欢迎程度
	struct b *next;
} book;
typedef struct {
	book bp[MAXSIZE];
	int length;
}bookpopular;
typedef struct {			//借阅表
	char ISBN[20];			//书号
	char student_ID[20];	//学生学号
	char boorow_time[30];	//借书日期
	char return_time[30];	//还书日期
	char isrenew[10];		//是否续借
	char remark[200];		//备注
}borrowing_table;
typedef struct {
	borrowing_table bt[MAXSIZE + 1];
	int length;
}borrow_sequence;
typedef struct s {			//学生信息表
	char student_ID[20];	//学生学号
	char password[30];		//登陆密码
	char student_name[10];	//学生姓名
	char student_sex[10];	//学生性别	
	char student_phone[20];	//学生电话
	char department[20];	//所在系
	char take_effect[30];	//学生生效时间
	char lose_efficay[30];	//学生失效时间
	int Arrearge;			//欠费金额
	int boorow_sum;			//累积借书总量
	char remark[200];		//备注
	borrowing_table borrow[MAXSIZE];
	int length;
	struct s *next;
}student;
typedef struct t {			//老师信息表
	char job_number[20];	//老师工作号
	char password[30];		//登陆密码
	char teacher_name[20];	//老师姓名
	char teacher_sex[10];	//老师性别
	char teacher_phone[20];	//老师电话
	char remark[200];		//备注
}teacher;
typedef struct {
	teacher te[MAXSIZE + 1];
	int length;
}teacher_sequence;
char *time()              /*时间函数*/
{
	char a[50], b[50], c[50];
	char d[20] = "0", e[20] = "0";
	struct tm *local;
	time_t t;
	t = time(NULL);
	local = localtime(&t);
	_itoa(local->tm_year + 1900, a, 10);
	_itoa(local->tm_mon + 1, b, 10);
	_itoa(local->tm_mday, c, 10);
	if (local->tm_mon + 1 >= 1 && local->tm_mon <= 9)
	{
		strcat_s(d, sizeof(d), b);
		strcpy_s(b, strlen(d) + 1, d);
	}
	if (local->tm_mday >= 1 && local->tm_mday <= 9)
	{
		strcat_s(e, sizeof(e), c);
		strcpy_s(c, strlen(e) + 1, e);
	}
	strcat_s(a, sizeof(a), b);
	strcat_s(a, sizeof(a), c);
	return a;
}
//学生老师密码注册登录
student* addstudent(student *head1) {            /*学生密码文件录入*/
	student *p;
	int n;
	FILE *rf;
	fopen_s(&rf, "C:\\Users\\王教授\\Desktop\\studentpassword.txt", "rb");
	if (rf) {
		fscanf_s(rf, "%d", &n);
		for (int i = 0; i < n; i++) {
			char account[20];
			memset(account, 0, sizeof(account));
			fscanf_s(rf, "%s", &account, sizeof(account));
			p = head1;
			for (int j = 0; j < n; j++)
			{
				if (strcmp(account, p->student_ID) == 0)
				{
					fscanf_s(rf, "%s", &p->password, sizeof(p->password));
					break;
				}
				p = p->next;
			}
		}
	}
	fclose(rf);
	return head1;
}
void addteacher(teacher_sequence *head2) {             /*老师密码文件录入*/
	int n;
	FILE *rf; int i;
	fopen_s(&rf, "C:\\Users\\王教授\\Desktop\\teacherpassword.txt", "rb");
	if (rf) {
		fscanf_s(rf, "%d", &n, sizeof(n));
		head2->length = n;
		for (int j = 1; j <= n; j++)
		{
			char account[20];
			memset(account, 0, sizeof(account));
			fscanf_s(rf, "%s", &account, sizeof(account));
			for (int i = 1; i <= n; i++) {
				if (strcmp(account, head2->te[i].job_number) == 0) {
					fscanf_s(rf, "%s", &head2->te[i].password, sizeof(head2->te[i].password));
					break;
				}
			}
		}
	}
	fclose(rf);
}
void teacherlanding(teacher_sequence *head2, char account[], char password[])        /*老师登陆*/
{
	int n;
	n = head2->length;
	teacher_sequence *p;
	p = head2;
	int count = 0, num = 0, low = 1, high = n, mid;
	while (low <= high)            /*二分查找*/
	{
		mid = (low + high) / 2;
		if (mid == 0)
		{
			break;
		}
		if (strcmp(p->te[mid].job_number, account) == 0)
		{
			count = 1; break;
		}
		else if (strcmp(p->te[mid].job_number, account) > 0)
			high = mid - 1;
		else
			low = mid + 1;
	}
	if (count == 0)
	{
		cout << "账号不存在！！" << endl;
		cout << "请注册账号！！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		for (int i = 1; i <= n; i++)
		{
			if (strcmp(p->te[i].password, password) == 0)
			{
				num = 1;
				break;
			}
		}
		if (num == 0)
		{
			cout << "密码错误！！" << endl;
			cout << "请重新输入密码！！" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			cout << "登陆成功！！" << endl;
		}
	}
}
void studentlanding(student *head1, char account[], char password[])              /*学生登陆*/
{
	student *p, *q;
	p = head1;
	q = head1;
	int count = 0, num = 0;
	for (; p; p = p->next)
	{
		if (strcmp(p->student_ID, account) == 0)
		{
			count = 1;
			break;
		}
	}
	if (count == 0)
	{
		cout << "账号不存在！！" << endl;
		cout << "请注册账号！！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		for (; q; q = q->next)
		{
			if (strcmp(q->password, password) == 0)
			{
				num = 1;
				break;
			}
		}
		if (num == 0)
		{
			cout << "密码错误！！" << endl;
			cout << "请重新输入密码！！" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			cout << "登陆成功！！" << endl;
		}
	}
}
teacher_sequence *charu(teacher_sequence *head2, char account[], char password[])
{
	teacher_sequence *p, *q, *end;
	char ch[10086];
	FILE *rf;
	int count;
	fopen_s(&rf, "C:\\Users\\王教授\\Desktop\\teacherpassword.txt", "rb");
	if (rf)
	{
		fscanf_s(rf, "%d", &count, sizeof(count));
		fclose(rf);
	}
	FILE *rt;
	fopen_s(&rt, "C:\\Users\\王教授\\Desktop\\teacherpassword.txt", "rb+");
	if (rt)
	{
		fprintf_s(rt, "%d", count + 1);
		fclose(rt);
	}
	p = head2;
	memset(ch, 0, sizeof(ch));
	strcat(ch, account);
	strcat(ch, " ");
	strcat(ch, password);
	FILE *ry;
	fopen_s(&ry, "C:\\Users\\王教授\\Desktop\\teacherpassword.txt", "a");
	if (ry) {
		fprintf_s(ry, " %s", ch);
		fclose(ry);
	}
	return head2;
}
student *charu2(student *head1, char account2[], char password2[])
{
	student *p, *q;
	char ch[10086];
	FILE *rf;
	int count;
	fopen_s(&rf, "C:\\Users\\王教授\\Desktop\\studentpassword.txt", "rb");
	if (rf)
	{
		fscanf_s(rf, "%d", &count, sizeof(count));
		fclose(rf);
	}
	FILE *rt;
	fopen_s(&rt, "C:\\Users\\王教授\\Desktop\\studentpassword.txt", "rb+");
	if (rt)
	{
		fprintf_s(rt, "%d", count + 1);
		fclose(rt);
	}
	p = head1;
	strcpy_s(ch, strlen(p->student_ID) + 1, p->student_ID);
	strcat(ch, " ");
	strcat(ch, p->password);
	FILE *ry;
	fopen_s(&ry, "C:\\Users\\王教授\\Desktop\\studentpassword.txt", "a");
	if (ry) {
		fprintf_s(ry, " %s", ch);
		fclose(ry);
	}
	return head1;
}
void teacherregistered(teacher_sequence *head2)         /*老师注册*/
{
	teacher_sequence *p;
	p = head2;
	int n;
	n = p->length;
	char account[20];
	cout << "注册账号：" << endl;
	cin >> account;
	int count = 0, num = 0, low = 1, high = n, mid;
	while (low <= high)            /*二分查找*/
	{
		mid = (low + high) / 2;
		if (mid == 0)
		{
			break;
		}
		if (strcmp(p->te[mid].job_number, account) == 0)
		{
			count = 1; break;
		}
		else if (strcmp(p->te[mid].job_number, account) > 0)
			high = mid - 1;
		else
			low = mid + 1;
	}
	if (count == 0)
	{
		strcpy_s(head2->te[head2->length + 1].job_number, strlen(account) + 1, account);
		cout << "注册密码：" << endl;
		cin >> head2->te[head2->length + 1].password;
		cout << "注册人姓名：" << endl;
		cin >> head2->te[head2->length + 1].teacher_name;
		cout << "注册人性别：" << endl;
		cin >> head2->te[head2->length + 1].teacher_sex;
		cout << "注册人电话：" << endl;
		cin >> head2->te[head2->length + 1].teacher_phone;
		cout << "注册人其他信息：" << endl;
		cin >> head2->te[head2->length + 1].remark;
		head2->length++;
		MYSQL mysql;
		string sqlstr;
		mysql_library_init(0, NULL, NULL);
		//初始化数据结构
		mysql_init(&mysql);
		//在连接数据库之前，设置额外的连接选项
		//可以设置的选项很多，这里设置字符集，否则无法处理中文
		mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
		//连接数据库
		mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
		//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
		cout << "数据库连接成功" << endl;
		system("pause");
		sqlstr = "INSERT INTO teacher VALUES('";
		sqlstr += head2->te[head2->length + 1].job_number;
		sqlstr += "','";
		sqlstr += head2->te[head2->length + 1].teacher_name;
		sqlstr += "','";
		sqlstr += head2->te[head2->length + 1].teacher_sex;
		sqlstr += "','";
		sqlstr += head2->te[head2->length + 1].teacher_phone;
		sqlstr += "','";
		sqlstr += head2->te[head2->length + 1].remark;
		sqlstr += "')";
		cout << head2->te[head2->length + 1].job_number << head2->te[head2->length + 1].teacher_name << head2->te[head2->length + 1].teacher_sex << endl;
		/*cout << sqlstr.c_str() << endl;
		if (mysql_query(&mysql, sqlstr.c_str()) == 0)
			cout << "注册成功！！" << endl;
		else
		{
			cout << "失败" << endl;
		}*/
		charu(head2, head2->te[head2->length].job_number, head2->te[head2->length].password);
		system("pause");
		system("cls");
	}
	else
	{
		cout << "注册账号已经存在，请重新注册！！" << endl;
	}
}
void studentregistered(student *head1)       /*学生注册*/
{
	student *p, *q;
	p = head1;
	char account[20];
	int count = 0;
	cout << "注册账号：" << endl;
	cin >> account;
	if (strlen(account) != 10)
	{
		cout << "您输入的帐号有误，请重新输入" << endl;
	}
	else {
		for (; p; p = p->next)
		{
			if (strcmp(p->student_ID, account) == 0)
			{
				count = 1;
				break;
			}
		}
		if (count == 0)
		{
			p = head1;
			while (p->next)
			{
				p = p->next;
			}
			q = (student *)malloc(sizeof(student));
			strcpy_s(q->student_ID, strlen(account) + 1, account);
			int d, i;
			d = atoi(q->student_ID);
			d = d / 100000000;
			i = d;
			d = d + 4;
			char e[20], j[20];
			_itoa(d, e, 10);
			_itoa(i, j, 10);
			char b[20] = "0901", c[20] = "20", h[20] = "20";
			strcat(c, e);
			strcat(c, b);
			strcat(h, j);
			strcat(h, b);
			strcpy_s(q->take_effect, strlen(h) + 1, h);
			strcpy_s(q->lose_efficay, strlen(c) + 1, c);
			char *k;
			k = time();
			if (strcmp(c, k) >= 0)
			{
				strcpy_s(q->student_ID, strlen(account) + 1, account);
				cout << "注册密码：" << endl;
				cin >> q->password;
				cout << "注册人姓名：" << endl;
				cin >> q->student_name;
				cout << "注册人性别：" << endl;
				cin >> q->student_sex;
				cout << "注册人电话：" << endl;
				cin >> q->student_phone;
				cout << "注册人系别：" << endl;
				cin >> q->department;
				cout << "注册人其他信息：" << endl;
				cin >> q->remark;
				q->Arrearge = 0;
				q->boorow_sum = 0;
				p->next = q;
				q->next = NULL;
				charu2(q, account, q->password);
				MYSQL mysql;
				string sqlstr;
				mysql_library_init(0, NULL, NULL);
				//初始化数据结构
				mysql_init(&mysql);
				//在连接数据库之前，设置额外的连接选项
				//可以设置的选项很多，这里设置字符集，否则无法处理中文
				mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
				//连接数据库
				mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
				//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
				cout << "数据库连接成功" << endl;
				system("pause");
				sqlstr = "INSERT INTO student VALUES('";
				sqlstr += q->student_ID;
				sqlstr += "','";
				sqlstr += q->student_name;
				sqlstr += "','";
				sqlstr += q->student_sex;
				sqlstr += "','";
				sqlstr += q->student_phone;
				sqlstr += "','";
				sqlstr += q->department;
				sqlstr += "','";
				sqlstr += q->take_effect;
				sqlstr += "','";
				sqlstr += q->lose_efficay;
				sqlstr += "',0,0,'";
				sqlstr += q->remark;
				sqlstr += "')";
				if(mysql_query(&mysql, sqlstr.c_str()) == 0)
				cout << "注册成功！！" << endl;
				else
				{
					cout << "失败" << endl;
				}
				system("pause");
				system("cls");
			}
			else
			{
				cout << "该学生ID已经失效！" << endl;
				system("pause");
				system("cls");
			}
		}
		else
		{
			cout << "注册账号已经存在，请重新注册！！" << endl;
		}
	}
}
//添加图书
void add_book(book *head)
{
	int count = 0;            /*标志是否查找到这本书在不在*/
	cout << "请输入要添加的书名：" << endl;
	char a[100];
	cin >> a;
	book *p, *q, *pre = NULL, *k, *pri = NULL, *h;
	p = head;
	k = head;
	h = head;
	while (p)
	{
		pre = p;
		if (strcmp(a, p->book_name) == 0)
		{
			count = 1;
			break;
		}
		p = p->next;
	}
	if (count == 1)
	{
		while (pre)
		{
			if (strcmp(pre->book_name, a) != 0)
			{
				break;
			}
			pri = pre;
			pre = pre->next;
		}
		q = (book *)malloc(sizeof(book));
		cout << "请输入该书的ISBN码：" << "(参考这类书籍ISBN码,比如：" << pri->ISBN << ")" << endl;
		cin >> q->ISBN;
		strcpy_s(q->book_name, strlen(pri->book_name) + 1, pri->book_name);
		strcpy_s(q->writer, strlen(pri->writer) + 1, pri->writer);
		strcpy_s(q->intro, strlen(pri->intro) + 1, pri->intro);
		strcpy_s(q->remark, strlen(pri->remark) + 1, pri->remark);
		q->standing_stock = pri->standing_stock;
		q->repertory = pri->repertory;
		q->next = pri->next;
		pri->next = q;
		while (k)
		{
			if (strcmp(k->book_name, a) == 0)
			{
				k->repertory++;
				k->standing_stock++;
			}
			k = k->next;
		}
		cout << "添加成功！" << endl;
	}
	else if (count == 0)
	{
		int nnum = 0;

		char newisbn[15], newwriter[15], newintro[200], newremark[200];
		cout << "图书馆无此类书籍，请输入相关信息" << endl;
		do {
			cout << "请输入书的ISBN码：" << endl;
			cin >> newisbn;
			for (; h; h = h->next)
			{
				if (strcmp(h->ISBN, newisbn) == 0)
				{
					nnum = 1;
					break;
				}
			}
			if (nnum == 0)
			{
				cout << "请输入书的作者：" << endl;
				cin >> newwriter;
				cout << "请输入书的简介：" << endl;
				cin >> newintro;
				cout << "请输入书的备注：" << endl;
				cin >> newremark;
				q = (book *)malloc(sizeof(book));
				strcpy_s(q->ISBN, strlen(newisbn) + 1, newisbn);
				strcpy_s(q->book_name, strlen(a) + 1, a);
				strcpy_s(q->writer, strlen(newwriter) + 1, newwriter);
				strcpy_s(q->intro, strlen(newintro) + 1, newintro);
				strcpy_s(q->remark, strlen(newremark) + 1, newremark);
				q->repertory = 0;
				q->repertory++;
				q->standing_stock = 0;
				q->standing_stock++;
				pre->next = q;
				q->next = NULL;
				cout << "添加成功！" << endl;
			}
			else
			{
				cout << "此ISBN码已被注册" << endl;
			}
		} while (nnum == 1);
	}
}
//修改图书信息
void modify_book(book *head)        /*修改图书信息*/
{
	char book_name[50];
	book *p, *pre = NULL;
	cout << "选择你要修改的图书名称：" << endl;
	cin >> book_name;
	p = head;
	int count = 0;
	while (p)
	{
		pre = p;
		if (strcmp(p->book_name, book_name) == 0)
		{
			count = 1;
			break;
		}
		p = p->next;
	}
	if (count == 1)
	{
		cout << "请选择要修改的信息序号：" << endl;
		cout << "1.该书的简介" << endl;
		cout << "2.该书的备注" << endl;
		int n;
		cin >> n;
		if (n == 1)
		{
			char intro[200];
			cout << "请输入新的简介：" << endl;
			cin >> intro;
			while (pre)
			{
				if (strcmp(pre->book_name, book_name) == 0)
				{
					strcpy_s(pre->intro, strlen(intro) + 1, intro);
				}
				pre = pre->next;
			}
		}
		else if (n == 2)
		{
			char remark[200];
			cout << "请输入新的备注：" << endl;
			cin >> remark;
			while (p)
			{
				if (strcmp(p->book_name, book_name) == 0)
				{
					strcpy_s(p->remark, strlen(remark) + 1, remark);
				}
				p = p->next;
			}
		}
	}
	else
	{
		cout << "此书不存在！！" << endl;
		cout << "按任意键返回主菜单！" << endl;
		system("pause");
	}
}
//字典树
typedef struct tire_node {
	int count;		//记录该节点代表的单词个数
	char word[MAXSIZE];
	bool isStr;		//标记该节点是否构成完整单词
	struct tire_node *children[MAXSIZE];	//各个子节点
} tire;
tire *initTire() {	//初始化
	tire *root;
	root = (tire *)malloc(sizeof(tire));
	root->count = 0;
	root->isStr = FALSE;
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
		if (!node->children[id])
		{
			node->children[id] = new tire();	//开辟空间
			for (j = 0; j < MAXSIZE; j++)
			{
				node->children[id]->children[j] = NULL;
			}
			node->children[id]->count = 0;
			node->children[id]->isStr = FALSE;
		}
		node = node->children[id];
		node->count++;
		i++;
	}
	node->isStr = TRUE;
	strcpy_s(node->word, strlen(word) + 1, word);
}
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
		else
		{
			return NULL;
		}
	}
	return node;
}
//通过书的完整拼音输出其全部信息
void printSpell(book *bo, char *sp, int *count) {
	book *p = bo;
	while (p)
	{
		if (strcmp(p->spell, sp) == 0)
		{
			p->number = (*count)++;
			printf("|%-6d%-15s%-20s%-13s%-12s%-10s%-5d%5d  |\n", p->number, p->ISBN, p->book_name, p->writer, p->type, p->is_or_no, p->repertory, p->standing_stock);
		}
		p = p->next;
	}
}
//BFS遍历打印出满足前缀的图书信息
void printTire(book *bo, tire *root, char *front) {
	int count = 1;
	tire *node = tireSearch(root, front);
	int i;
	if (!node)
	{
		cout << "未匹配到您需要的信息，请重新输入" << endl;
	}
	else
	{
		cout << endl;
		cout << "|---------------------------------------图书信息-----------------------------------------|" << endl;
		cout << "|序号  编号           书名                作者         类别    是否借出   馆藏量   现存量|" << endl;
		tire *queue[MAXSIZE];
		int left = 0, right = 0;
		queue[right++] = node;
		while (left < right)
		{
			tire *p = queue[left++];
			if (p->count != 0 && p->isStr)
			{
				printSpell(bo, p->word, &count);
				//cout << p->word << p->isStr << endl;
			}
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
//shell排序
/*void shellsort(char** strs, int n){	int len = 0;	int i, j, d;	char **s;	s = (char**)malloc(sizeof(char*)*MAXSIZE);	s[0] = (char*)malloc(sizeof(char) * 20);	i = 0;	while (i < n)	{		//cout << strs[i] << endl;		s[i + 1] = (char*)malloc(sizeof(char) * 20);		s[i + 1] = strs[i];		i++;	}	len = n;	s[i + 1] = (char*)malloc(sizeof(char) * 20);	s[i + 1] = '\0';	d = len / 2;	while (d >= 1)	{		for (i = d + 1; i <= len; i++)		{			s[0] = s[i];			j = i - d;			while (j > 0 && strcmp(s[0], s[j]) < 0)			{				s[j + d] = s[j];				j = j - d;			}			s[j + d] = s[0];		}		d = d / 2;	}	for (i = 1; i <= len; i++)	{		printf("%s\n", s[i]);		//cout << s[i] << endl;	}	system("pause");}*/
void MySql() {
	//必备的一个数据结构
	MYSQL mysql;
	string sqlstr;
	//初始化数据库
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	}
	else {
		cout << "mysql_library_init() failed" << endl;
		exit(-1);
	}
	system("pause");
	//初始化数据结构
	if (NULL != mysql_init(&mysql)) {
		cout << "mysql_init() succeed" << endl;
	}
	else {
		cout << "mysql_init() failed" << endl;
		exit(1);
	}
	system("pause");
	//在连接数据库之前，设置额外的连接选项
	//可以设置的选项很多，这里设置字符集，否则无法处理中文
	if (0 == mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	}
	else {
		cout << "mysql_options() failed" << endl;
		exit(-1);
	}
	system("pause");
	//连接数据库
	if (NULL
		!= mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0))
		//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
	{
		cout << "mysql_real_connect() succeed" << endl;
	}
	else {
		cout << "mysql_real_connect() failed" << endl;
		exit(-1);
	}
	system("pause");
	//图书信息表(book)
	//ISBN:书号,book_name:书名,class:类别,writer:作者,intro:简介,is_or_no:是否在管,remark:备注,standing_stock:现存量,repertory:库存,popular:受欢迎程度
	sqlstr = "create table if not exists book(ISBN VARCHAR(20),";
	sqlstr += "book_name VARCHAR(50)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "spell VARCHAR(100)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "class VARCHAR(30)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "writer VARCHAR(30)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "intro VARCHAR(1000)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "is_or_not VARCHAR(10)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "standing_stock INT,";
	sqlstr += "repertory INT,";
	sqlstr += "remark VARCHAR(200)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "popular INT,PRIMARY KEY(ISBN))";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() create book succeed" << endl;
	}
	else {
		cout << "mysql_query() create book failed" << endl;
		mysql_close(&mysql);
		exit(-1);
	}
	system("pause");

	//学生信息表(student)
	//student_ID:学生学号,student_name：学生姓名,student_sex:学生性别,student_phone:学生电话,department:所在系,take_effect:学生生效时 间
	//lose_efficay:学生失效时间,Arrearage:欠费金额,borrow_sum:累积借书总量,remark:备注
	sqlstr = "create table if not exists student(student_ID VARCHAR(20),";
	sqlstr += "student_name VARCHAR(10)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "student_sex VARCHAR(10)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "student_phone VARCHAR(20),";
	sqlstr += "department VARCHAR(20)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "take_effect VARCHAR(30)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "lose_efficay VARCHAR(30)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "Arrearge INT,";
	sqlstr += "borrow_sum INT,";
	sqlstr += "remark VARCHAR(200)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,PRIMARY KEY(student_ID))";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() create student succeed" << endl;
	}
	else {
		cout << "mysql_query() create student failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	system("pause");
	//老师信息表(teacher)
	//job_number:老师工作号,teacher_name:老师姓名,teacher_sex:老师性别,teacher_phone:老师电话,remark:备注
	sqlstr = "create table if not exists teacher(job_number VARCHAR(20),";
	sqlstr += "teacher_name VARCHAR(30)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "teacher_sex VARCHAR(10)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "teacher_phone VARCHAR(30),";
	sqlstr += "remark VARCHAR(200)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,PRIMARY KEY(job_number))";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() create teacher succeed" << endl;
	}
	else {
		cout << "mysql_query() create teacher failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	system("pause");
	////借阅表（borrowing_table）
	////ISBN:书号,student_ID:学生学号,borrow_time:借书日期,return_time:还书日期,isrenew:是否续借,remark:备注
	sqlstr = "create table if not exists borrowing_table(ISBN VARCHAR(20),";
	sqlstr += "student_ID VARCHAR(20),";
	sqlstr += "borrow_time VARCHAR(30)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "return_time VARCHAR(30)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "isrenew VARCHAR(10)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "remark VARCHAR(200)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,PRIMARY KEY(ISBN))";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() create borrowing_table succeed" << endl;
	}
	else {
		cout << "mysql_query() create borrowing_table failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	system("pause");

	//向表中插入数据
	sqlstr =
		"INSERT INTO book VALUES('9787544285147','恶意','eyi','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。','是',2,6,'借阅量大，需加购',4),";
	sqlstr += "('9787544285148','恶意','eyi','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。','否',2,6,'借阅量大，需加购',4),";
	sqlstr += "('9787544285149','恶意','eyi','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。','否',2,6,'借阅量大，需加购',4),";
	sqlstr += "('9787544285150','恶意','eyi','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。','否',2,6,'借阅量大，需加购',4),";
	sqlstr += "('9787544285151','恶意','eyi','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。','否',2,6,'借阅量大，需加购',4),";
	sqlstr += "('9787544285152','恶意','eyi','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。','是',2,6,'借阅量大，需加购',4),";
	sqlstr += "('9787020024759','围城','weicheng','文学','钱钟书','《围城》是中国现代文学史上一部风格独特的讽刺小说，被誉为“新儒林外史”。故事主要写抗战初期知识分子的群相。','否',3,5,'无',2),";
	sqlstr += "('9787020024760','围城','weicheng','文学','钱钟书','《围城》是中国现代文学史上一部风格独特的讽刺小说，被誉为“新儒林外史”。故事主要写抗战初期知识分子的群相。','否',3,5,'无',2),";
	sqlstr += "('9787020024761','围城','weicheng','文学','钱钟书','《围城》是中国现代文学史上一部风格独特的讽刺小说，被誉为“新儒林外史”。故事主要写抗战初期知识分子的群相。','是',3,5,'无',2),";
	sqlstr += "('9787020024762','围城','weicheng','文学','钱钟书','《围城》是中国现代文学史上一部风格独特的讽刺小说，被誉为“新儒林外史”。故事主要写抗战初期知识分子的群相。','是',3,5,'无',2),";
	sqlstr += "('9787020024763','围城','weicheng','文学','钱钟书','《围城》是中国现代文学史上一部风格独特的讽刺小说，被誉为“新儒林外史”。故事主要写抗战初期知识分子的群相。','是',3,5,'无',2),";
	sqlstr += "('9787020049295','平凡的世界','pingfandeshijie','文学','路遥','《平凡的世界》是一部现实主义小说，也是一部小说形式的家族史。作者浓缩料中国西北农村的历史变迁过程，在小说中全景式地表现了中国当代城乡的社会生活。在近十年的广阔背景下，通过复杂的矛盾纠葛，刻划社会格阶层众多普通人的形象','否',0,3,'一本严重损坏，需丢弃',3),";
	sqlstr += "('9787020049296','平凡的世界','pingfandeshijie','文学','路遥','《平凡的世界》是一部现实主义小说，也是一部小说形式的家族史。作者浓缩料中国西北农村的历史变迁过程，在小说中全景式地表现了中国当代城乡的社会生活。在近十年的广阔背景下，通过复杂的矛盾纠葛，刻划社会格阶层众多普通人的形象','否',0,3,'一本严重损坏，需丢弃',3),";
	sqlstr += "('9787020049297','平凡的世界','pingfandeshijie','文学','路遥','《平凡的世界》是一部现实主义小说，也是一部小说形式的家族史。作者浓缩料中国西北农村的历史变迁过程，在小说中全景式地表现了中国当代城乡的社会生活。在近十年的广阔背景下，通过复杂的矛盾纠葛，刻划社会格阶层众多普通人的形象','否',0,3,'一本严重损坏，需丢弃',3),";
	sqlstr += "('9787020026906','白鹿原','bailuyuan','文学','陈忠实','这是一部渭河平原五十年变迁的雄奇史诗，一轴中国农村斑斓多彩、触目惊心的长幅画卷。主人公六娶六丧，神秘的序曲暗示着不祥。一个家族两代子孙，为争夺白鹿原的统治代代斗争不已，上演了一幕幕惊心动魄的活剧。','否',1,3,'无',2),";
	sqlstr += "('9787020026907','白鹿原','bailuyuan','文学','陈忠实','这是一部渭河平原五十年变迁的雄奇史诗，一轴中国农村斑斓多彩、触目惊心的长幅画卷。主人公六娶六丧，神秘的序曲暗示着不祥。一个家族两代子孙，为争夺白鹿原的统治代代斗争不已，上演了一幕幕惊心动魄的活剧。','否',1,3,'无',2),";
	sqlstr += "('9787020026908','白鹿原','bailuyuan','文学','陈忠实','这是一部渭河平原五十年变迁的雄奇史诗，一轴中国农村斑斓多彩、触目惊心的长幅画卷。主人公六娶六丧，神秘的序曲暗示着不祥。一个家族两代子孙，为争夺白鹿原的统治代代斗争不已，上演了一幕幕惊心动魄的活剧。','是',1,3,'无',2),";
	sqlstr += "('9787549529322','看见','kanjian','历史','柴静','《看见》是著名记者和主持人柴静讲述央视十年历程的自传性作品，既是柴静个人的成长告白书，某种程度上亦可以视作中国十年变迁的备忘录','否',3,5,'无',2),";
	sqlstr += "('9787549529323','看见','kanjian','历史','柴静','《看见》是著名记者和主持人柴静讲述央视十年历程的自传性作品，既是柴静个人的成长告白书，某种程度上亦可以视作中国十年变迁的备忘录','否',3,5,'无',2),";
	sqlstr += "('9787549529324','看见','kanjian','历史','柴静','《看见》是著名记者和主持人柴静讲述央视十年历程的自传性作品，既是柴静个人的成长告白书，某种程度上亦可以视作中国十年变迁的备忘录','是',3,5,'无',2),";
	sqlstr += "('9787549529325','看见','kanjian','历史','柴静','《看见》是著名记者和主持人柴静讲述央视十年历程的自传性作品，既是柴静个人的成长告白书，某种程度上亦可以视作中国十年变迁的备忘录','是',3,5,'无',2),";
	sqlstr += "('9787549529326','看见','kanjian','历史','柴静','《看见》是著名记者和主持人柴静讲述央视十年历程的自传性作品，既是柴静个人的成长告白书，某种程度上亦可以视作中国十年变迁的备忘录','是',3,5,'无',2),";
	sqlstr += "('9787508645056','你的孤独，虽败犹荣','nidegudusuibaiyourong','爱情','刘同','孤独之所以迷茫，孤独之后是成长。这本书里记录了33种孤独感，希望能让你想起自己某种忘我无形的成长。最后。愿你比别人更不怕一个人独处，愿日后想起时你会被自己感动。','是',3,3,'无效',0),";
	sqlstr += "('9787508645057','你的孤独，虽败犹荣','nidegudusuibaiyourong','爱情','刘同','孤独之所以迷茫，孤独之后是成长。这本书里记录了33种孤独感，希望能让你想起自己某种忘我无形的成长。最后。愿你比别人更不怕一个人独处，愿日后想起时你会被自己感动。','是',3,3,'无效',0),";
	sqlstr += "('9787508645058','你的孤独，虽败犹荣','nidegudusuibaiyourong','爱情','刘同','孤独之所以迷茫，孤独之后是成长。这本书里记录了33种孤独感，希望能让你想起自己某种忘我无形的成长。最后。愿你比别人更不怕一个人独处，愿日后想起时你会被自己感动。','是',3,3,'无效',0)";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() insert 1data succeed" << endl;
	}
	else {
		cout << "mysql_query() insert 1data failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	sqlstr = "INSERT INTO student VALUES('1705064109','蔺笑扬','女','18834166336','生物医学工程','20170901','20210701',0,3,'无'),";
	sqlstr += "('1509024219','任静','女','13303590256','工商管理','20150901','20190701',0,3,'无'),";
	sqlstr += "('1613004747','庞琦','男','18103485619','软件工程','20160901','20200701',0,2,'无'),";
	sqlstr += "('1802094127','刘嵩','男','18406582150','机械类','20180901','20220701',0,0,'无'),";
	sqlstr += "('1410024336','王媛','女','13466992580','英语','20150901','20190701',0,2,'学生信息过期，需注销'),";
	sqlstr += "('1704034143','薛晨曦','男','13835999499','制药工程','20170901','20210701',0,3,'无')";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() insert 2data succeed" << endl;
	}
	else {
		cout << "mysql_query() insert 2data failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	sqlstr = "INSERT INTO teacher VALUES('01025','许静','女','15524877534','无'),";
	sqlstr += "('04103','何茂林','男','17633417821','无'),";
	sqlstr += "('07081','柴天平','男','13603593363','无'),";
	sqlstr += "('16045','胡晓萍','女','13994858711','无'),";
	sqlstr += "('10016','李素云','女','18636369763','无')";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() insert 3data succeed" << endl;
	}
	else {
		cout << "mysql_query() insert 3data failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	sqlstr = "INSERT INTO borrowing_table VALUES('9787020049295','1509024219','20181001','20181013','否','无'),";
	sqlstr += "('9787020026906','1509024219','20181115','20181224','是','无'),";
	sqlstr += "('9787020026907','1509024219','20181115','20181224','是','无'),";
	sqlstr += "('9787020049296','1705064109','20181127','20190105','是','无'),";
	sqlstr += "('9787544285148','1613004747','20181208','20190106','否','无'),";
	sqlstr += "('9787020024759','1613004747','20181208','20190106','否','无'),";
	sqlstr += "('9787020049297','1704034143','20181210','20190108','否','无'),";
	sqlstr += "('9787549529322','1704034143','20181210','20190108','否','无'),";
	sqlstr += "('9787544285149','1509024219','20181214','20190112','否','无'),";
	sqlstr += "('9787549529323','1410024336','20170302','20170316','否','无'),";
	sqlstr += "('9787020024760','1410024336','20160516','20160523','否','无'),";
	sqlstr += "('9787544285150','1705064109','20181220','20190118','否','无'),";
	sqlstr += "('9787544285151','1704034143','20181010','20181108','否','无')";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() insert 4data succeed" << endl;
	}
	else {
		cout << "mysql_query() insert 4data failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	cout << "数据库创建成功" << endl;
	mysql_close(&mysql);
	system("pause");
}
//学生信息链表初始化
student * StudentLink() {
	return NULL;
}
//图书信息链表初始化
book * BookLink() {
	return NULL;
}
void initData(book **bo, student **st, teacher_sequence *t, borrow_sequence *bs, tire **root, bookpopular *bp) {
	//必备的一个数据结构
	MYSQL mysql;
	string sqlstr;
	//初始化数据库
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	}
	else {
		cout << "mysql_library_init() failed" << endl;
		exit(-1);
	}
	system("pause");
	//初始化数据结构
	if (NULL != mysql_init(&mysql)) {
		cout << "mysql_init() succeed" << endl;
	}
	else {
		cout << "mysql_init() failed" << endl;
		exit(1);
	}
	system("pause");
	//在连接数据库之前，设置额外的连接选项
	//可以设置的选项很多，这里设置字符集，否则无法处理中文
	if (0 == mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	}
	else {
		cout << "mysql_options() failed" << endl;
		exit(-1);
	}
	system("pause");
	//连接数据库
	if (NULL
		!= mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0))
		//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
	{
		cout << "mysql_real_connect() succeed" << endl;
	}
	else {
		cout << "mysql_real_connect() failed" << endl;
		exit(-1);
	}
	system("pause");
	//初始化字典树
	*root = initTire();
	MYSQL_RES *result;
	MYSQL_FIELD *field;
	MYSQL_ROW row;
	//初始化图书信息表
	sqlstr = "SELECT * FROM book";
	mysql_query(&mysql, sqlstr.c_str());
	int numfields = 0;	//统计结果集中的字段数
	int numRows = 0;	//统计结果集中的行数
	result = mysql_store_result(&mysql);		//将查询的全部结果读取到客户端
	numfields = mysql_num_fields(result);
	numRows = mysql_num_rows(result);
	//while (field = mysql_fetch_field(result))	//返回结果集中的列信息(字段)
	//{
	//	cout << field->name << "---";
	//	
	//}
	//cout << endl;
	if (result)
	{
		book *p;
		int i = 1;
		bp->length = 0;
		while (row = mysql_fetch_row(result))	//返回结果集中行的记录
		{
			//图书推荐表
			strcpy_s(bp->bp[i].ISBN, strlen(row[0]) + 1, row[0]);
			strcpy_s(bp->bp[i].book_name, strlen(row[1]) + 1, row[1]);
			strcpy_s(bp->bp[i].spell, strlen(row[2]) + 1, row[2]);
			strcpy_s(bp->bp[i].type, strlen(row[3]) + 1, row[3]);
			strcpy_s(bp->bp[i].writer, strlen(row[4]) + 1, row[4]);
			strcpy_s(bp->bp[i].intro, strlen(row[5]) + 1, row[5]);
			strcpy_s(bp->bp[i].is_or_no, strlen(row[6]) + 1, row[6]);
			bp->bp[i].standing_stock = atoi(row[7]);	//将字符串转换为int
			bp->bp[i].repertory = atoi(row[8]);
			strcpy_s(bp->bp[i].remark, strlen(row[9]) + 1, row[9]);
			bp->bp[i++].popular = atoi(row[10]);
			bp->length++;
			//book表
			p = (book *)malloc(sizeof(book));
			/*memset(p->ISBN, 0, sizeof(p->ISBN));
			memset(p->book_name,0,sizeof(p->book_name));
			memset(p->type,0,sizeof(p->type));
			memset(p->writer,0,sizeof(p->writer));
			memset(p->intro,0,sizeof(p->intro));
			memset(p->remark,0,sizeof(p->remark));*/
			strcpy_s(p->ISBN, strlen(row[0]) + 1, row[0]);
			strcpy_s(p->book_name, strlen(row[1]) + 1, row[1]);
			strcpy_s(p->spell, strlen(row[2]) + 1, row[2]);
			tireInsert(root, row[2]);			//创建字典树
			strcpy_s(p->type, strlen(row[3]) + 1, row[3]);
			strcpy_s(p->writer, strlen(row[4]) + 1, row[4]);
			strcpy_s(p->intro, strlen(row[5]) + 1, row[5]);
			strcpy_s(p->is_or_no, strlen(row[6]) + 1, row[6]);
			p->standing_stock = atoi(row[7]);	//将字符串转换为int
			p->repertory = atoi(row[8]);
			strcpy_s(p->remark, strlen(row[9]) + 1, row[9]);
			p->popular = atoi(row[10]);
			if (!(*bo))
			{
				(*bo) = p;
				(*bo)->next = NULL;
			}
			else
			{
				//将新节点插入到表头
				p->next = (*bo);
				(*bo) = p;
			}
		}
	}
	mysql_free_result(result);	//释放result空间
	//初始化借阅表
	borrowing_table b[MAXSIZE][MAXSIZE];
	sqlstr = "SELECT * FROM borrowing_table";
	mysql_query(&mysql, sqlstr.c_str());
	result = mysql_store_result(&mysql);		//将查询的全部结果读取到客户端
	numfields = mysql_num_fields(result);
	numRows = mysql_num_rows(result);
	if (result)
	{
		int i, j;

		//先初始化为空
		for (i = 0; i < MAXSIZE; i++)
		{
			for (j = 0; j < MAXSIZE; j++)
			{
				strcpy_s(b[i][j].student_ID, "");
			}
		}
		while (row = mysql_fetch_row(result))
		{

			for (i = 1, j = 1; i < MAXSIZE; i++)
			{
				if (strcmp(row[1], b[i][j].student_ID) == 0) {
					while (strcmp(row[1], b[i][j].student_ID) == 0)
					{
						j++;
					}
					strcpy_s(b[i][j].ISBN, strlen(row[0]) + 1, row[0]);
					strcpy_s(b[i][j].student_ID, strlen(row[1]) + 1, row[1]);
					strcpy_s(b[i][j].boorow_time, strlen(row[2]) + 1, row[2]);
					strcpy_s(b[i][j].return_time, strlen(row[3]) + 1, row[3]);
					strcpy_s(b[i][j].isrenew, strlen(row[4]) + 1, row[4]);
					strcpy_s(b[i][j].remark, strlen(row[5]) + 1, row[5]);
					break;
				}
				else if (strcmp(b[i][j].student_ID, "") == 0)
				{
					strcpy_s(b[i][j].ISBN, strlen(row[0]) + 1, row[0]);
					strcpy_s(b[i][j].student_ID, strlen(row[1]) + 1, row[1]);
					strcpy_s(b[i][j].boorow_time, strlen(row[2]) + 1, row[2]);
					strcpy_s(b[i][j].return_time, strlen(row[3]) + 1, row[3]);
					strcpy_s(b[i][j].isrenew, strlen(row[4]) + 1, row[4]);
					strcpy_s(b[i][j].remark, strlen(row[5]) + 1, row[5]);
					break;
				}

			}
		}
	}
	mysql_free_result(result);	//释放result空间
	//初始化学生表
	sqlstr = "SELECT * FROM student";
	mysql_query(&mysql, sqlstr.c_str());
	result = mysql_store_result(&mysql);		//将查询的全部结果读取到客户端
	numfields = mysql_num_fields(result);
	numRows = mysql_num_rows(result);
	if (result) {
		student *q;
		int i;
		while (row = mysql_fetch_row(result))
		{
			int j = 1;
			q = (student *)malloc(sizeof(student));
			q->length = 0;
			strcpy_s(q->student_ID, strlen(row[0]) + 1, row[0]);
			for (i = 1; i < MAXSIZE; i++)
			{
				if (strcmp(b[i][j].student_ID, q->student_ID) == 0)
				{
					while (strcmp(b[i][j].student_ID, "") != 0)
					{
						q->borrow[q->length++] = b[i][j++];
					}
					break;
				}
			}
			strcpy_s(q->student_name, strlen(row[1]) + 1, row[1]);
			strcpy_s(q->student_sex, strlen(row[2]) + 1, row[2]);
			strcpy_s(q->student_phone, strlen(row[3]) + 1, row[3]);
			strcpy_s(q->department, strlen(row[4]) + 1, row[4]);
			strcpy_s(q->take_effect, strlen(row[5]) + 1, row[5]);
			strcpy_s(q->lose_efficay, strlen(row[6]) + 1, row[6]);
			q->Arrearge = atoi(row[7]);		//将字符串转换为整型
			q->boorow_sum = atoi(row[8]);
			strcpy_s(q->remark, strlen(row[9]) + 1, row[9]);
			if (!(*st))
			{
				(*st) = q;
				(*st)->next = NULL;
			}
			else
			{
				q->next = (*st);
				(*st) = q;
			}
		}
	}
	mysql_free_result(result);	//释放result空间
	//初始化borrow_sequence
	bs->length = 0;
	student *q;
	q = (*st);
	while (q)
	{
		int i;
		for (i = 0; i < q->length; i++)
		{
			bs->length++;
			bs->bt[bs->length] = q->borrow[i];
		}
		q = q->next;
	}
	//初始化老师表
	sqlstr = "SELECT * FROM teacher";
	mysql_query(&mysql, sqlstr.c_str());
	result = mysql_store_result(&mysql);		//将查询的全部结果读取到客户端
	numfields = mysql_num_fields(result);
	numRows = mysql_num_rows(result);

	if (result)
	{
		t->length = 0;
		int i = 1;
		while (row = mysql_fetch_row(result))
		{
			strcpy_s(t->te[i].job_number, strlen(row[0]) + 1, row[0]);
			strcpy_s(t->te[i].teacher_name, strlen(row[1]) + 1, row[1]);
			strcpy_s(t->te[i].teacher_sex, strlen(row[2]) + 1, row[2]);
			strcpy_s(t->te[i].teacher_phone, strlen(row[3]) + 1, row[3]);
			strcpy_s(t->te[i++].remark, strlen(row[4]) + 1, row[4]);
			t->length++;
		}
	}
	mysql_free_result(result);	//释放result空间
	mysql_close(&mysql);
	//system("pause");
}
//输出所有图书信息
void displaybook(book *bo)
{
	int count = 1;
	book *p;

	cout << endl;
	cout << "|---------------------------------------图书信息-----------------------------------------|" << endl;
	cout << "|序号  编号           书名                作者         类别    是否借出   馆藏量   现存量|" << endl;
	p = bo;
	while (p)
	{
		p->number = count++;
		printf("|%-6d%-15s%-20s%-13s%-12s%-10s%-5d%5d  |\n", p->number, p->ISBN, p->book_name, p->writer, p->type, p->is_or_no, p->repertory, p->standing_stock);
		p = p->next;
	}

}
//展示书的详细信息
void displaydetailed(book **bo) {
	cout << "请选择您想深入了解书信息的序号:" << endl;
	int number;
	cin >> number;
	book *pre = *bo;
	char com[MAXSIZE];
	while (pre)
	{
		if (pre->number == number)
		{
			cout << "这本书的简介为：" << endl;
			cout << pre->intro << endl;
			pre->popular++;
			strcpy_s(com, strlen(pre->book_name) + 1, pre->book_name);
		}
		//让所有书名相同的书的受欢迎程度都加1
		if (strcmp(pre->book_name, com) == 0 && pre->number != number)
		{
			pre->popular++;
		}
		cout << "popular = " << pre->popular << endl;
		pre = pre->next;

	}
}
//输出学生信息
void displaystudent(student  *st) {
	student *p;
	p = st;
	while (p)
	{
		cout << p->student_ID << "---" << p->student_name << "---" << p->student_sex << "---" << p->student_phone << "---" << p->department << "---" << p->Arrearge << endl;
		p = p->next;
	}
}
//输出老师信息表
void displayteacher(teacher_sequence *t) {
	int i;
	printf("-----------------------------------教师信息表---------------------------------\n");
	printf("||     工作号            姓名               性别              电话          ||\n");
	for (i = 1; i <= t->length; i++)
	{
		printf("||     %-5s          %-7s                %-2s            %-11s      ||\n", t->te[i].job_number, t->te[i].teacher_name, t->te[i].teacher_sex, t->te[i].teacher_phone);
	}
}
//输出借阅信息表
void displayborrow(borrow_sequence *bs) {
	int i;
	printf("|----------------------------图书借阅信息--------------------|\n");
	printf("|编号  书名        作者        类别     借书学生学号|\n");
	for (i = 1; i <= bs->length; i++)
	{
		cout << bs->bt[i].ISBN << "--" << bs->bt[i].student_ID << endl;
	}
}
//根据书籍类别查询图书信息
void SeeBook(book *bo, char *type) {
	book *p = bo;
	cout << endl;
	cout << "|------------------------------------图书信息--------------------------------------|" << endl;
	cout << "|编号           书名                作者         类别    是否借出   馆藏量   现存量|" << endl;
	while (p)
	{
		if (strcmp(p->type, type) == 0)
		{
			printf("|%-15s%-20s%-13s%-12s%-10s%-5d%5d  |\n", p->ISBN, p->book_name, p->writer, p->type, p->is_or_no, p->repertory, p->standing_stock);
		}
		p = p->next;
	}

}
//根据学号查看借阅信息
void SeeBorrow(student *st, char id[]) {
	student * p;
	int i;
	p = st;
	while (p)
	{
		if (strcmp(p->student_ID, id) == 0)
		{

			for (i = 0; i < p->length; i++)
			{
				cout << p->borrow[i].ISBN << "---" << p->borrow[i].boorow_time << "---" << p->borrow[i].return_time << endl;
			}
		}
		p = p->next;
	}
}

//计算两个时间间隔的函数
int runnian(int y, int m, int d) {
	int day;
	day = 0;
	if ((y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0))) {
		if (m == 1)
			day = d;
		else if (m == 2)
			day = d + 31;
		else if (m == 3)
			day = d + 31 + 29;
		else if (m == 4)
			day = d + 31 + 29 + 31;
		else if (m == 5)
			day = d + 31 + 29 + 31 + 30;
		else if (m == 6)
			day = d + 31 + 29 + 31 + 30 + 31;
		else if (m == 7)
			day = d + 31 + 29 + 31 + 30 + 31 + 30;
		else if (m == 8)
			day = d + 31 + 29 + 31 + 30 + 31 + 30 + 31;
		else if (m == 9)
			day = d + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31;
		else if (m == 10)
			day = d + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30;
		else if (m == 11)
			day = d + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
		else if (m == 12)
			day = d + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
	}
	else {
		// printf("no\n");

		if (m == 1)
			day = d;
		else if (m == 2)
			day = d + 31;
		else if (m == 3)
			day = d + 31 + 28;
		else if (m == 4)
			day = d + 31 + 28 + 31;
		else if (m == 5)
			day = d + 31 + 28 + 31 + 30;
		else if (m == 6)
			day = d + 31 + 28 + 31 + 30 + 31;
		else if (m == 7)
			day = d + 31 + 28 + 31 + 30 + 31 + 30;
		else if (m == 8)
			day = d + 31 + 28 + 31 + 30 + 31 + 30 + 31;
		else if (m == 9)
			day = d + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31;
		else if (m == 10)
			day = d + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30;
		else if (m == 11)
			day = d + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
		else if (m == 12)
			day = d + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
	}
	return day;
}
int change(char s1[], char s2[]) {
	int year1, year2, month1, month2, day1, day2;
	year1 = ((int)(s1[0] - 48)) * 1000 + ((int)(s1[1] - 48)) * 100 + ((int)(s1[2] - 48)) * 10 + ((int)(s1[3] - 48));
	year2 = ((int)(s2[0] - 48)) * 1000 + ((int)(s2[1] - 48)) * 100 + ((int)(s2[2] - 48)) * 10 + ((int)(s2[3] - 48));
	month1 = ((int)(s1[4] - 48)) * 10 + ((int)(s1[5] - 48));
	month2 = ((int)(s2[4] - 48)) * 10 + ((int)(s2[5] - 48));
	day1 = ((int)(s1[6] - 48)) * 10 + (int)(s1[7] - 48);
	day2 = ((int)(s2[6] - 48)) * 10 + (int)(s2[7] - 48);
	int d1, d2, days = 0;;
	//年份相等时
	if (year1 == year2) {
		d1 = runnian(year1, month1, day1);
		d2 = runnian(year2, month2, day2);
		if (d1 >= d2) days = d1 - d2;
		else days = d2 - d1;
	}
	//年份不等时
	else {
		d1 = runnian(year1, month1, day1);
		d2 = runnian(year2, month2, day2);
		if (year1 < year2) {
			if ((year1 % 400 == 0) || ((year1 % 4 == 0) && (year1 % 100 != 0)))
				d1 = 366 - d1;
			else
				d1 = 365 - d1;
			days = d1 + d2;
		}
		else if (year2 < year1) {
			if ((year2 % 400 == 0) || ((year2 % 4 == 0) && (year2 % 100 != 0)))
				d2 = 366 - d2;
			else
				d2 = 365 - d2;
			days = d1 + d2;
		}
	}
	if (year1 > year2) {
		int temp = year1;
		year1 = year2;
		year2 = temp;
	}
	for (int i = year1 + 1; i < year2; i++) {
		if ((i % 400 == 0) || ((i % 4 == 0) && (i % 100 != 0)))
			days = days + 366;
		else
			days = days + 365;
	}
	return days;
}
//根据当日日期更新学生欠费情况
void updataArrearge(student *st) {
	MYSQL mysql;
	string sqlstr;
	mysql_library_init(0, NULL, NULL);
	//初始化数据结构
	mysql_init(&mysql);
	//在连接数据库之前，设置额外的连接选项
	//可以设置的选项很多，这里设置字符集，否则无法处理中文
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//连接数据库
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
	cout << "数据库连接成功" << endl;
	system("pause");
	student *p;
	string temp;
	int i;
	p = st;
	while (p)
	{
		int sum = 0;
		if (p->length != 0)
		{
			for (i = 0; i < p->length; i++)
			{
				char str[MAXSIZE];
				strcpy_s(str, strlen(time()) + 1, time());
				if (strcmp(p->borrow[i].return_time, str) == -1)
				{
					p->Arrearge += change(p->borrow[i].return_time, str);
				}
				sqlstr = "update student set Arrearge = ";
				char ss[30];
				sqlstr += itoa(p->Arrearge, ss, 10);
				sqlstr += " where student_ID = '";
				sqlstr += p->student_ID;
				sqlstr += "'";
				cout << sqlstr.c_str() << endl;
				mysql_query(&mysql, sqlstr.c_str());
				cout << "学生欠费金额更新成功" << endl;

			}
		}
		p = p->next;
	}
	mysql_close(&mysql);
}
void mergepopular(bookpopular *tabs, bookpopular *tabg, int u, int m, int v)
{
	int i, j, k, t;
	i = u;
	j = m + 1;
	k = u;
	while (i <= m && j <= v)
	{
		if (tabs->bp[i].popular <= tabs->bp[j].popular)
		{
			tabg->bp[k] = tabs->bp[i];
			i++;
		}
		else
		{
			tabg->bp[k] = tabs->bp[j];
			j++;
		}
		k++;
	}
	if (i <= m)
	{
		for (t = i; t <= m; t++)
		{
			tabg->bp[k + t - i] = tabs->bp[t];
		}
	}
	else
	{
		for (t = j; t <= v; t++)
		{
			tabg->bp[k + t - j] = tabs->bp[t];
		}
	}
}
//一趟归并算法，将tabs中长度为len的连续函数有序段归并成长度为2*len的有序段  存入tabg中
void  mergepasspopular(bookpopular *tabs, bookpopular *tabg, int len)
{
	int i, j, n;
	n = tabg->length = tabs->length;
	i = 1;
	while (i <= n - 2 * len + 1)  //将以i为起点，长度为len的相邻两个有序段一次进行归并
	{
		mergepopular(tabs, tabg, i, i + len - 1, i + 2 * len - 1);
		i = i + 2 * len;
	}
	if (i + len - 1 < n)
	{
		mergepopular(tabs, tabg, i, i + len - 1, n);   //一次归并
	}
	else
	{
		for (j = i; j <= n; j++)
		{
			tabg->bp[j] = tabs->bp[j];
		}
	}
}
//对书籍受欢迎程度进行排序
void mergesortpopular(bookpopular *tab)
{
	int len;
	bookpopular  temp;
	len = 1;
	while (len < tab->length)
	{
		mergepasspopular(tab, &temp, len);
		len = 2 * len;
		mergepasspopular(&temp, tab, len);
		len = 2 * len;
	}
}
//图书推荐函数
void display_popular(bookpopular *bp) {
	mergesortpopular(bp);
	int i;
	book save[MAXSIZE];
	int top = 0;
	cout << endl;
	cout << "|-----------------------------------图书推荐榜-------------------------------------|" << endl;
	cout << "|编号           书名                作者         类别    是否借出   馆藏量   现存量|" << endl;
	for (i = bp->length; i >= 1; i--)
	{
		if (bp->bp[i].repertory == 1)
		{
			save[top++] = bp->bp[i];
		}

		else if (strcmp(bp->bp[i].book_name, bp->bp[i - 1].book_name) != 0)
		{
			save[top++] = bp->bp[i];
		}
		//printf("|%-6d%-15s%-20s%-13s%-12s%-10s%-5d%5d  |\n", bp->bp[i].number, bp->bp[i].ISBN, bp->bp[i].book_name, bp->bp[i].writer, bp->bp[i].type, bp->bp[i].is_or_no, bp->bp[i].repertory, bp->bp[i].standing_stock);
	}
	for (i = 0; i < top; i++)
	{
		printf("|%-15s%-20s%-13s%-12s%-10s%-5d%5d  |\n", save[i].ISBN, save[i].book_name, save[i].writer, save[i].type, save[i].is_or_no, save[i].repertory, save[i].standing_stock);
	}
}
//堆排序算法对老师信息进行排序
void siftTeacher(teacher_sequence *t, int k, int m) {		//筛选算法
	int i, j, finished;
	i = k;
	j = 2 * i;
	t->te[0] = t->te[k];
	finished = 0;
	while ((j <= m) && !finished)
	{
		if (j < m && strcmp(t->te[j + 1].job_number, t->te[j].job_number) == 1)
		{
			j++;
		}
		if (strcmp(t->te[0].job_number, t->te[j].job_number) == 1)
		{
			finished = 1;
		}
		else
		{
			t->te[i] = t->te[j];
			i = j;
			j = 2 * i;
		}
	}
	t->te[i] = t->te[0];
}
void heapsortTeacher(teacher_sequence *t) {
	int i;
	//对所有元素建堆
	for (i = t->length / 2; i >= 1; i--)
	{
		siftTeacher(t, i, t->length);
	}
	for (i = t->length; i >= 2; i--)		//将最小的元素和最后一个交换
	{
		t->te[0] = t->te[i];
		t->te[i] = t->te[1];
		t->te[1] = t->te[0];
		siftTeacher(t, 1, i - 1);
	}
}
//堆排序算法根据索引号对借阅表排序
void siftBorrow(borrow_sequence *bs, int k, int m) {		//筛选算法
	int i, j, finished;
	i = k;
	j = 2 * i;
	bs->bt[0] = bs->bt[k];
	finished = 0;
	while ((j <= m) && !finished)
	{
		if (j < m && strcmp(bs->bt[j + 1].ISBN, bs->bt[j].ISBN) == 1)
		{
			j++;
		}
		if (strcmp(bs->bt[0].ISBN, bs->bt[j].ISBN) == 1)
		{
			finished = 1;
		}
		else
		{
			bs->bt[i] = bs->bt[j];
			i = j;
			j = 2 * i;
		}
	}
	bs->bt[i] = bs->bt[0];
}
void heapsortBorrow(borrow_sequence *bs) {
	int i;
	//对所有元素建堆
	for (i = bs->length / 2; i >= 1; i--)
	{
		siftBorrow(bs, i, bs->length);
	}
	for (i = bs->length; i >= 2; i--)		//将最小的元素和最后一个交换
	{
		bs->bt[0] = bs->bt[i];
		bs->bt[i] = bs->bt[1];
		bs->bt[1] = bs->bt[0];
		siftBorrow(bs, 1, i - 1);
	}
}
//一次归并算法，将有序段tabs[u...m]和tabs[m+1...v]合并成有序段tabg[u...v]
void merge(borrow_sequence *tabs, borrow_sequence *tabg, int u, int m, int v)
{
	int i, j, k, t;
	i = u;
	j = m + 1;
	k = u;
	while (i <= m && j <= v)
	{
		if (strcmp(tabs->bt[i].boorow_time, tabs->bt[j].boorow_time) <= 0)
		{
			tabg->bt[k] = tabs->bt[i];
			i++;
		}
		else
		{
			tabg->bt[k] = tabs->bt[j];
			j++;
		}
		k++;
	}
	if (i <= m)
	{
		for (t = i; t <= m; t++)
		{
			tabg->bt[k + t - i] = tabs->bt[t];
		}
	}
	else
	{
		for (t = j; t <= v; t++)
		{
			tabg->bt[k + t - j] = tabs->bt[t];
		}
	}
}
//一趟归并算法，将tabs中长度为len的连续函数有序段归并成长度为2*len的有序段  存入tabg中
void  mergepass(borrow_sequence *tabs, borrow_sequence *tabg, int len)
{
	int i, j, n;
	n = tabg->length = tabs->length;
	i = 1;
	while (i <= n - 2 * len + 1)  //将以i为起点，长度为len的相邻两个有序段一次进行归并
	{
		merge(tabs, tabg, i, i + len - 1, i + 2 * len - 1);
		i = i + 2 * len;
	}
	if (i + len - 1 < n)
	{
		merge(tabs, tabg, i, i + len - 1, n);   //一次归并
	}
	else
	{
		for (j = i; j <= n; j++)
		{
			tabg->bt[j] = tabs->bt[j];
		}
	}
}
void mergesort(borrow_sequence *tab)
{
	int len;
	borrow_sequence  temp;
	len = 1;
	while (len < tab->length)
	{
		mergepass(tab, &temp, len);
		len = 2 * len;
		mergepass(&temp, tab, len);
		len = 2 * len;
	}
}
void updataMYSQLbook(book *bo) {
	MYSQL mysql;
	string sqlstr;
	mysql_library_init(0, NULL, NULL);
	//初始化数据结构
	mysql_init(&mysql);
	//在连接数据库之前，设置额外的连接选项
	//可以设置的选项很多，这里设置字符集，否则无法处理中文
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//连接数据库
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
	cout << "数据库连接成功" << endl;
	system("pause");
	book *p = bo;
	while (p)
	{
		sqlstr = "update book set popular = ";
		char ss[MAXSIZE];
		sqlstr += itoa(p->popular, ss, 10);		//将字符串转换为数字
		cout << ss << "---" << endl;
		sqlstr += " where ISBN = '";
		sqlstr += p->ISBN;
		sqlstr += "'";
		mysql_query(&mysql, sqlstr.c_str());
		p = p->next;
	}
	cout << "图书受欢迎成都更新成功！！！" << endl;
	mysql_close(&mysql);
}
//根据类型显示图书信息 ,此处进行顺序检索，
void  display_book_type(book *head, char book_type[])
{
	printf("以下是%s类型图书的搜索结果：\n", book_type);
	//	printf("%20s%30s%30s%15s%50s%30s%20s%30s", "书号", "书名", "类别", "作者", "简介", "现存", "库存", "备注");
	book *p = head;
	while (p)
	{
		if (strcmp(p->type, book_type) == 0)
		{
			printf("%s   %s   %s  %s  %s  %d  %d  %s  %s\n", p->ISBN, p->book_name, p->type, p->writer, p->intro, p->standing_stock, p->repertory, p->remark, p->is_or_no);
			p = p->next;
		}
		else
		{
			p = p->next;
		}
	}
}
//借书刷新库存，参数为头节点  和 所借书名
book * refresh(book * head, char borrowed_name[30])
{
	book *p = head;
	while (p)
	{
		if (strcmp(borrowed_name, p->book_name) == 0)
		{
			p->standing_stock--;
		}
		p = p->next;
	}
	return head;
}
//还书时间函数
char *returnbooktime()              /*时间函数*/
{
	char a[50], b[50], c[50];
	char d[20] = "0", e[20] = "0";
	struct tm *local;
	time_t t;
	t = time(NULL);
	local = localtime(&t);
	_itoa(local->tm_year + 1900, a, 10);
	_itoa(local->tm_mon + 2, b, 10);
	_itoa(local->tm_mday, c, 10);
	if (local->tm_mon + 1 >= 1 && local->tm_mon <= 9)
	{
		strcat_s(d, sizeof(d), b);
		strcpy_s(b, strlen(d) + 1, d);
	}
	if (local->tm_mday >= 1 && local->tm_mday <= 9)
	{
		strcat_s(e, sizeof(e), c);
		strcpy_s(c, strlen(e) + 1, e);
	}
	strcat_s(a, sizeof(a), b);
	strcat_s(a, sizeof(a), c);
	return a;
}
//借书完成 刷新 学生信息表  参数为借书学生学号，学生信息表指针，所借书号
student * refresh_student(char borrowed_stu_ID[20], student * stu_head, char borrowed_ISBN[30])
{

	student * p = stu_head;
	while (p&&strcmp(p->student_ID, borrowed_stu_ID) != 0)
	{
		cout << "emmm" << endl;
		p = p->next;
	}
	//借阅总数加一
	p->boorow_sum++;

	//学生的借阅信息表
	int t = p->boorow_sum - 1;
	strcpy_s(p->borrow[t].ISBN, 30, borrowed_ISBN);
	strcpy_s(p->borrow[t].isrenew, 10, "否");
	strcpy_s(p->borrow[t].student_ID, 20, borrowed_stu_ID);

	//借书日期
	char str[MAXSIZE];
	strcpy_s(str, strlen(time()) + 1, time());
	strcpy_s(p->borrow[t].boorow_time, 30, str);
	//还书日期
	strcpy_s(str, strlen(returnbooktime()) + 1, returnbooktime());
	strcpy_s(p->borrow[t].return_time, 30, str);
	return stu_head;
}
//输入借书号进行借书
void input_num(book *head, student *stu)
{
	printf("请输入你想借图书的书号：\n");
	char temp_num[20];
	scanf_s("%s", temp_num, 20);
	book *p;
	p = head;
	while (strcmp(p->ISBN, temp_num) != 0)
	{
		p = p->next;
	}
	if (!p)
	{
		printf("没有该图书，请重新输入:\n");
		input_num(head, stu);
	}
	else
	{
		if (strcmp(p->is_or_no, "是") == 0)
		{
			printf("查找成功，正在为您借书......\n");

			char temp_ID[20];
			char temp_key[30];
			printf("学号： ");
			scanf_s("%s", temp_ID, 20);
			printf("密码： ");
			scanf_s("%s", temp_key, 30);

			//如果验证成功，执行以下程序,此处测试为定值  或者  将登陆的信息传进来就行
			if (strcmp(temp_ID, "1410024336") == 0 && strcmp(temp_key, "1") == 0)
			{
				printf("借书成功!\n");
				strcpy_s(p->is_or_no, 10, "否");

				//此处刷新图书库存
				char borrowed_book_name[30];
				strcpy_s(borrowed_book_name, 20, p->book_name);

				head = refresh(head, borrowed_book_name);
				//display(new_head);

				//此处刷新学生信息表,参数：学生学号，学生表指针，所借图书号，
				//student * stu;
				stu = refresh_student(temp_ID, stu, temp_num);
			}
		}
		else
		{
			printf("您所选书籍已经被借走，请重新进行选择!\n");
			input_num(head, stu);
		}
	}
}
//借书
void borrow_book(book *bo, tire *root, student *stu)
{
	printf("******************************兄dei,请进行以下选择!!!************************\n");
	printf("**                  1.我知道自己想借什么书                                 **\n");
	printf("**                  2.我有点方(□),只知道想借那类型的书                    **\n");
	printf("**                  3.我目前方的雅痞，我想查看所有的书                     **\n");
	printf("*****************************************************************************\n");

	int t;
	scanf_s("%d", &t, 1);
	if (t == 1)
	{

		/****************以下应进行修改 ***************
		book *head = 你读取一下;
		******此处调用根据书名显示的图书信息的函数**************
		***********************************************/
		char s[MAXSIZE];
		cout << "请输入您想借的书的拼音" << endl;
		cin >> s;
		printTire(bo, root, s);
		input_num(bo, stu);

	}
	else if (t == 2)
	{
		char temp_book_type[30];
		printf("请输入你想借哪类型的书:\n");
		scanf_s("%s", temp_book_type, 30);


		/*************此处应修改，读取图书信息表的头结点*******

		book *head = 你读取一下;
		display_book_type(head,temp_book_type);

		****************************************************/
		book *head = bo;
		display_book_type(head, temp_book_type);
		input_num(bo, stu);

		//input_num(head);


	}
	else if (t == 3)
	{
		displaybook(bo);
		input_num(bo, stu);
	}
	else
	{
		printf("输入错误，请重新进行选择");
		borrow_book(bo, root, stu);
	}
}
//快速排序
void quicksort(borrow_sequence *head3, int left, int right)
{
	borrow_sequence *p;
	p = head3;
	int i, j;
	if (left < right)
	{
		i = left; j = right;
		p->bt[0] = p->bt[i];
		do {
			while (strcmp(p->bt[j].student_ID, p->bt[0].student_ID) > 0 && i < j)
				j--;
			if (i < j)
			{
				p->bt[i] = p->bt[j];
				i++;
			}
			while (strcmp(p->bt[i].student_ID, p->bt[0].student_ID) < 0 && i < j)
				i++;
			if (i < j)
			{
				p->bt[j] = p->bt[i];
				j--;
			}
		} while (i != j);
		p->bt[i] = p->bt[0];
		quicksort(head3, left, i - 1);
		quicksort(head3, i + 1, right);
	}
}
//根据图书名称进行删除
book * delete_book(book *head)
{
	printf("请输入你要删除的书名:\n");
	char delete_book_name[50];
	scanf_s("%s", delete_book_name, 50);
	book *pre = NULL, *p;

	if (!(head))
	{
		printf("图书信息表为空，无法进行删除！请重新输入：\n");
		delete_book(head);
	}

	//链表遍历判断输入的书是否可以删除
	p = head;  //p为正在处理的结点

	while (p&&strcmp(p->book_name, delete_book_name) != 0)  //找到该书后停止
	{
		pre = p;
		p = p->next;
	}
	if (!p)  //p为空，表示没有此书，无法进行删除
	{
		printf("抱歉!未在图书信息表找到该书！请重新输入：\n");
		delete_book(head);
	}
	else
	{
		if ((p->repertory == p->standing_stock) && strcmp(p->remark, "无效") == 0)  //在管量=库存量，并且图书备注为"无效"，表示可以进行删除
		{
			printf("已找到该图书,正在为您删除  loading......\n");

			while (p)     //p不为空，则一直循环，防止同名书漏删
			{
				if (!pre)   //要删除第一个结点
				{
					head = head->next;
				}
				else
				{
					pre->next = p->next;
					p = p->next;

				}
				while (p&&strcmp(p->book_name, delete_book_name) != 0)
				{
					pre = p;
					p = p->next;
				}
			}
			printf("删除成功！\n");
			return  head;
		}

		else
		{
			printf("您输入的图书为有效书籍，不能进行删除!,请重新输入：\n");
			delete_book(head);
		}
	}
	return  head;
}
//还书完成刷新图书信息表
book * returned_book(book *book_head, char return_book_ID[20])
{
	book *p = book_head;

	//记录还书的书名
	char  temp_name[50];
	//将该书改为在管
	while (p)
	{
		if (strcmp(return_book_ID, p->ISBN) == 0)
		{
			strcpy_s(p->is_or_no, 10, "是");
			strcpy_s(temp_name, 50, p->book_name);
		}
		p = p->next;
	}
	book *q = book_head;
	//将同名书的在管量都+1;
	while (q)
	{
		if (strcmp(temp_name, q->book_name) == 0)
		{
			q->standing_stock++;
		}
		q = q->next;
	}
	return book_head;
}

//还书完成刷新学生信息和借阅信息表  参数：还书学生学号， 学生信息表指针，还书书号
student * returned_student(char returned_stu_ID[20], student * stu_head, char returned_ISBN[30])
{
	student * p = stu_head;
	while (p&&strcmp(returned_stu_ID, p->student_ID) != 0)
	{
		p = p->next;
	}
	int i = 0;
	//学生借阅信息顺序表查找该书
	while (i < p->boorow_sum && strcmp(p->borrow[i].ISBN, returned_ISBN) != 0)
	{
		i++;
	}
	if (p->Arrearge > 0)
	{
		printf("您已超期借书，需要支付相应的费用！\n");
		printf("此处默认已经支付费用.\n");
	}
	for (; i < p->boorow_sum; i++)
	{
		p->borrow[i] = p->borrow[i + 1];
	}
	p->boorow_sum--;
	printf("还书成功!\n");
	return stu_head;
}
//还书
void return_book(student *st,book *bo)
{
	printf("您好，请输入你的学号和密码：\n");
	char temp_ID[20];
	char temp_key[30];

	//跟借书一样，获取学号   再次调用学生登陆函数进行匹配，此处为定值
	printf("学号： ");
	scanf_s("%s", temp_ID, 20);
	printf("密码： ");
	scanf_s("%s", temp_key, 30);
	if (strcmp(temp_ID, "1410024336") == 0 && strcmp(temp_key, "1") == 0)
	{
		//若匹配成功，输出借书情况
		printf("以下为你目前所有的借书情况：\n");

		//展示学生借书情况
		SeeBorrow(st, temp_ID);

		printf("\n请输入你要还书的书号：\n");
		char temp_return_book[20];
		scanf_s("%s", temp_return_book, 20);
		returned_book(bo, temp_return_book);
		returned_student(temp_ID, st, temp_return_book);
	}

}
int main() {
	//MySql();
	book *bo;
	teacher_sequence t;
	student *st;
	borrow_sequence bs;
	tire *root;
	bookpopular bp;
	st = StudentLink();
	bo = BookLink();
	initData(&bo, &st, &t, &bs, &root, &bp);
	st = addstudent(st);
	addteacher(&t);
	//studentregistered(st);
	teacherregistered(&t);
	//bo = delete_book(bo);
	//borrow_book(bo,root,st);

	//updataArrearge(st);
	//displaystudent(st);
	/*char id[] = "1509024219";
	SeeBorrow(st, id);
	*/
	/*heapsortTeacher(&t);
	displayteacher(&t);*/
	//heapsortBorrow(&bs);
	//mergesort(&bs);
	/*quicksort(&bs, 1, bs.length);
	displayborrow(&bs);*/
	//updataMYSQLbook();
	char x[] = "e";
	//SeeBook(bo, x);
	//cout << tireSearch(root, x)->isStr << "----" << endl;
	//printSpell(bo, x);
	//printTire(bo, root, x);
	//borrow_book(bo);
	//displaydetailed(&bo);
	//updataMYSQLbook(bo);
	//display_popular(&bp);
	//add_book(bo);
	/*return_book(st, bo);
	displaybook(bo);*/
	system("pause");
	return 0;
}