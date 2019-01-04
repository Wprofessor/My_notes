#include <winsock.h>
#include <iostream>
#include <string.h>
#include<stdlib.h>
#include <mysql.h>
#include<time.h>
#include<conio.h>
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning( disable : 4996 )	//��ֹtime��������
#define MAXSIZE 50
using namespace std;
typedef struct b {			//ͼ����Ϣ��
	int number;				//���
	char ISBN[20];			//���
	char book_name[50];		//����
	char spell[100];		//����ƴ��
	char type[30];			//���
	char writer[15];		//����
	char intro[200];		//���
	char is_or_no[10];      //�Ƿ��ڹ�
	int standing_stock;		//�ִ���
	int repertory;			//���
	char remark[200];		//��ע
	int popular;			//�ܻ�ӭ�̶�
	struct b *next;
} book;
typedef struct {
	book bp[MAXSIZE];
	int length;
}bookpopular;
typedef struct {			//���ı�
	char ISBN[20];			//���
	char student_ID[20];	//ѧ��ѧ��
	char boorow_time[30];	//��������
	char return_time[30];	//��������
	char isrenew[10];		//�Ƿ�����
	char remark[200];		//��ע
}borrowing_table;
typedef struct {
	borrowing_table bt[MAXSIZE + 1];
	int length;
}borrow_sequence;
typedef struct s {			//ѧ����Ϣ��
	char student_ID[20];	//ѧ��ѧ��
	char password[30];		//��½����
	char student_name[10];	//ѧ������
	char student_sex[10];	//ѧ���Ա�	
	char student_phone[20];	//ѧ���绰
	char department[20];	//����ϵ
	char take_effect[30];	//ѧ����Чʱ��
	char lose_efficay[30];	//ѧ��ʧЧʱ��
	int Arrearge;			//Ƿ�ѽ��
	int boorow_sum;			//�ۻ���������
	char remark[200];		//��ע
	borrowing_table borrow[MAXSIZE];
	int length;
	struct s *next;
}student;
typedef struct t {			//��ʦ��Ϣ��
	char job_number[20];	//��ʦ������
	char password[30];		//��½����
	char teacher_name[20];	//��ʦ����
	char teacher_sex[10];	//��ʦ�Ա�
	char teacher_phone[20];	//��ʦ�绰
	char remark[200];		//��ע
}teacher;
typedef struct {
	teacher te[MAXSIZE + 1];
	int length;
}teacher_sequence;
//�ֵ��� 
typedef struct tire_node {
	int count;		//��¼�ýڵ����ĵ��ʸ���
	char word[MAXSIZE];
	bool isStr;		//��Ǹýڵ��Ƿ񹹳���������
	struct tire_node *children[MAXSIZE];	//�����ӽڵ�
} tire;
tire *initTire() {	//��ʼ��
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
			node->children[id] = new tire();	//���ٿռ�
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
//ͨ���������ƴ�������ȫ����Ϣ
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
void student_menu(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID);
//BFS������ӡ������ǰ׺��ͼ����Ϣ
void printTire(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID, char *front) {
	system("cls");
	int count = 1;
	tire *node = tireSearch(root, front);
	int i;
	if (!node)
	{
		cout << "δƥ�䵽����Ҫ����Ϣ������������" << endl;
	}
	else
	{
		cout << endl;
		cout << "|---------------------------------------ͼ����Ϣ-----------------------------------------|" << endl;
		cout << "|���  ���           ����                ����         ���    �Ƿ���   �ݲ���   �ִ���|" << endl;
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
	printf("�������������һ��\n");
	while (_getch())
	student_menu(bo, t, st, bs, root, bp, student_ID);
}

/*ԭӱ*/
//�����߼�
//���˵�
void menu(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp);
void menu_switch(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, int n);

//��Ա��¼
void member(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp);

//void student_menu_id(student *st, char *student_ID, char *student_name);
void student_menu_switch(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, int n, char *student_ID);

void print_student_information(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID);

/*������*/
//����Ա��¼
void teacher_register(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp);
//void teacher_menu_id();
void teacher_menu(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp);
void teacher_menu_switch(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, int n);
char *time()              /*ʱ�亯��*/
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
//ѧ����ʦ����ע���¼
student* addstudent(student *head1) {            /*ѧ�������ļ�¼��*/
	student *p;
	int n;
	FILE *rf;
	fopen_s(&rf, "C:\\Users\\������\\Desktop\\studentpassword.txt", "rb");
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
void addteacher(teacher_sequence *head2) {             /*��ʦ�����ļ�¼��*/
	int n;
	FILE *rf; int i;
	fopen_s(&rf, "C:\\Users\\������\\Desktop\\teacherpassword.txt", "rb");
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
teacher_sequence *charu(teacher_sequence *head2, char account[], char password[])
{
	teacher_sequence *p, *q, *end;
	char ch[10086];
	FILE *rf;
	int count;
	fopen_s(&rf, "C:\\Users\\������\\Desktop\\teacherpassword.txt", "rb");
	if (rf)
	{
		fscanf_s(rf, "%d", &count, sizeof(count));
		fclose(rf);
	}
	FILE *rt;
	fopen_s(&rt, "C:\\Users\\������\\Desktop\\teacherpassword.txt", "rb+");
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
	fopen_s(&ry, "C:\\Users\\������\\Desktop\\teacherpassword.txt", "a");
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
	fopen_s(&rf, "C:\\Users\\������\\Desktop\\studentpassword.txt", "rb");
	if (rf)
	{
		fscanf_s(rf, "%d", &count, sizeof(count));
		fclose(rf);
	}
	FILE *rt;
	fopen_s(&rt, "C:\\Users\\������\\Desktop\\studentpassword.txt", "rb+");
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
	fopen_s(&ry, "C:\\Users\\������\\Desktop\\studentpassword.txt", "a");
	if (ry) {
		fprintf_s(ry, " %s", ch);
		fclose(ry);
	}
	return head1;
}
void studentregistered(book *bo, teacher_sequence t, student *head1, borrow_sequence bs, tire *root, bookpopular bp)       /*ѧ��ע��*/
{
	student *p, *q;
	p = head1;
	char account[20];
	int count = 0;
	cout << "ע���˺ţ�" << endl;
	cin >> account;
	if (strlen(account) != 10)
	{
		cout << "��������ʺ���������������" << endl;
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
				cout << "ע�����룺" << endl;
				cin >> q->password;
				cout << "ע����������" << endl;
				cin >> q->student_name;
				cout << "ע�����Ա�" << endl;
				cin >> q->student_sex;
				cout << "ע���˵绰��" << endl;
				cin >> q->student_phone;
				cout << "ע����ϵ��" << endl;
				cin >> q->department;
				cout << "ע����������Ϣ��" << endl;
				cin >> q->remark;
				q->Arrearge = 0;
				q->boorow_sum = 0;
				p->next = q;
				q->next = NULL;
				charu2(q, account, q->password);
				MYSQL mysql;
				string sqlstr;
				mysql_library_init(0, NULL, NULL);
				//��ʼ�����ݽṹ
				mysql_init(&mysql);
				//���������ݿ�֮ǰ�����ö��������ѡ��
				//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
				mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
				//�������ݿ�
				mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
				//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
				cout << "���ݿ����ӳɹ�" << endl;
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
				if (mysql_query(&mysql, sqlstr.c_str()) == 0)
					cout << "ע��ɹ�����" << endl;
				else
				{
					cout << "ʧ��" << endl;
				}
				system("pause");
				system("cls");
				member(bo, t, head1, bs, root, bp);
			}
			else
			{
				cout << "��ѧ��ID�Ѿ�ʧЧ��" << endl;
				system("pause");
				system("cls");
			}
		}
		else
		{
			cout << "ע���˺��Ѿ����ڣ�������ע�ᣡ��" << endl;
		}
	}
	printf("�������������һ��\n");
	while (_getch())
	{
		menu(bo, t, head1, bs, root, bp);
	}
}
void teacherlanding(book *bo, teacher_sequence head2, student *head1, borrow_sequence bs, tire *root, bookpopular bp, char account[], char password[])        /*��ʦ��½*/
{
	int n;
	n = head2.length;
	teacher_sequence *p;
	p = &head2;
	int count = 0, num = 0, low = 1, high = n, mid;
	while (low <= high)            /*���ֲ���*/
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
		cout << "�˺Ų����ڣ���" << endl;
		cout << "��ע���˺ţ���" << endl;
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
			cout << "������󣡣�" << endl;
			cout << "�������������룡��" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			cout << "��½�ɹ�����" << endl;
		}
	}
}
void studentlanding(book *bo, teacher_sequence t, student *head1, borrow_sequence bs, tire *root, bookpopular bp, char account[], char password[])              /*ѧ����½*/
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
		cout << "�˺Ų����ڣ���" << endl;
		cout << "��ע���˺ţ���" << endl;
		system("pause");
		system("cls");
		studentregistered(bo, t, head1, bs, root, bp);
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
			cout << "������󣡣�" << endl;
			cout << "�������������룡��" << endl;
			system("pause");
			system("cls");
			member(bo, t, head1, bs, root, bp);
		}
		else
		{
			cout << "��½�ɹ�����" << endl;
			system("pause");
			system("cls");
			student_menu(bo, t, head1, bs, root, bp, account);
		}
	}
}

void teacherregistered(teacher_sequence *head2)         /*��ʦע��*/
{
	teacher_sequence *p;
	p = head2;
	int n;
	n = p->length;
	char account[20];
	cout << "ע���˺ţ�" << endl;
	cin >> account;
	int count = 0, num = 0, low = 1, high = n, mid;
	while (low <= high)            /*���ֲ���*/
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
		cout << "ע�����룺" << endl;
		cin >> head2->te[head2->length + 1].password;
		cout << "ע����������" << endl;
		cin >> head2->te[head2->length + 1].teacher_name;
		cout << "ע�����Ա�" << endl;
		cin >> head2->te[head2->length + 1].teacher_sex;
		cout << "ע���˵绰��" << endl;
		cin >> head2->te[head2->length + 1].teacher_phone;
		cout << "ע����������Ϣ��" << endl;
		cin >> head2->te[head2->length + 1].remark;
		head2->length++;
		MYSQL mysql;
		string sqlstr;
		mysql_library_init(0, NULL, NULL);
		//��ʼ�����ݽṹ
		mysql_init(&mysql);
		//���������ݿ�֮ǰ�����ö��������ѡ��
		//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
		mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
		//�������ݿ�
		mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
		//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
		cout << "���ݿ����ӳɹ�" << endl;
		system("pause");
		sqlstr = "INSERT INTO teacher VALUES('";
		sqlstr += head2->te[head2->length].job_number;
		sqlstr += "','";
		sqlstr += head2->te[head2->length].teacher_name;
		sqlstr += "','";
		sqlstr += head2->te[head2->length].teacher_sex;
		sqlstr += "','";
		sqlstr += head2->te[head2->length].teacher_phone;
		sqlstr += "','";
		sqlstr += head2->te[head2->length].remark;
		sqlstr += "')";
		cout << sqlstr.c_str() << endl;
		if (mysql_query(&mysql, sqlstr.c_str()) == 0)
			cout << "ע��ɹ�����" << endl;
		else
		{
			cout << "ʧ��" << endl;
		}
		charu(head2, head2->te[head2->length].job_number, head2->te[head2->length].password);
		system("pause");
		system("cls");
	}
	else
	{
		cout << "ע���˺��Ѿ����ڣ�������ע�ᣡ��" << endl;
	}
}
/*������*/
//���ͼ��
void add_book(book *head, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp)
{
	MYSQL mysql;
	string sqlstr;
	mysql_library_init(0, NULL, NULL);
	//��ʼ�����ݽṹ
	mysql_init(&mysql);
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	cout << "���ݿ����ӳɹ�" << endl;
	system("pause");
	int count = 0;            /*��־�Ƿ���ҵ��Ȿ���ڲ���*/
	cout << "������Ҫ��ӵ�������" << endl;
	char a[100];
	cin >> a;
	book *p, *q, *pre = NULL, *k, *pri = NULL, *h;
	p = head;
	k = head;
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
		cout << "����������ISBN�룺" << "(�ο������鼮ISBN��,���磺" << pri->ISBN << ")" << endl;
		cin >> q->ISBN;
		int ok = 0;
		book *wjh = head;
		while (wjh) {
			if (strcmp(wjh->ISBN, q->ISBN) == 0) {
				ok = 1;
				break;
			}
			wjh = wjh->next;
		}
		while (ok)
		{
			cout << "������ı����Ѵ��ڣ����������룺" << endl;
			cin >> q->ISBN;
			ok = 0;
			book *wjh = head;
			while (wjh) {
				if (strcmp(wjh->ISBN, q->ISBN) == 0) {
					ok = 1;
					break;
				}
				wjh = wjh->next;
			}
		}
		strcpy_s(q->book_name, strlen(pri->book_name) + 1, pri->book_name);
		strcpy_s(q->spell, strlen(pri->spell) + 1, pri->spell);
		strcpy_s(q->type, strlen(pri->type) + 1, pri->type);
		strcpy_s(q->writer, strlen(pri->writer) + 1, pri->writer);
		strcpy_s(q->intro, strlen(pri->intro) + 1, pri->intro);
		strcpy_s(q->remark, strlen(pri->remark) + 1, pri->remark);
		q->standing_stock = pri->standing_stock;
		q->repertory = pri->repertory;
		q->popular = pri->popular;
		strcpy_s(q->is_or_no, strlen("��") + 1, "��");
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
		sqlstr = "INSERT INTO book VALUES('";
		sqlstr += q->ISBN;
		sqlstr += "','";
		sqlstr += q->book_name;
		sqlstr += "','";
		sqlstr += q->spell;
		sqlstr += "','";
		sqlstr += q->type;
		sqlstr += "','";
		sqlstr += q->writer;
		sqlstr += "','";
		sqlstr += q->intro;
		sqlstr += "','";
		sqlstr += q->is_or_no;
		sqlstr += "',";
		char ss[MAXSIZE];
		sqlstr += itoa(q->standing_stock, ss, 10);
		sqlstr += ",";
		sqlstr += itoa(q->repertory, ss, 10);
		sqlstr += ",'";
		sqlstr += q->remark;
		sqlstr += "',";
		sqlstr += itoa(q->popular, ss, 10);
		sqlstr += ")";
		mysql_query(&mysql, sqlstr.c_str());
		sqlstr = "update book set standing_stock = ";
		sqlstr += itoa(q->standing_stock, ss, 10);
		sqlstr += ",repertory = ";
		sqlstr += itoa(q->repertory, ss, 10);
		sqlstr += " where book_name = '";
		sqlstr += q->book_name;
		sqlstr += "'";
		mysql_query(&mysql, sqlstr.c_str());
		cout << "��ӳɹ���" << endl;
	}
	else if (count == 0)
	{
		int nnum;
		char newisbn[15], newspell[20], newtype[20], newwriter[15], newintro[200], newremark[200];
		cout << "ͼ����޴����鼮�������������Ϣ" << endl;
		do {
			nnum = 0;
			cout << "���������ISBN�룺" << endl;
			cin >> newisbn;
			h = head;
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
				cout << "����������ƴ����" << endl;
				cin >> newspell;
				cout << "������������" << endl;
				cin >> newtype;
				cout << "������������ߣ�" << endl;
				cin >> newwriter;
				cout << "��������ļ�飺" << endl;
				cin >> newintro;
				cout << "��������ı�ע��" << endl;
				cin >> newremark;
				q = (book *)malloc(sizeof(book));
				strcpy_s(q->spell, strlen(newspell) + 1, newspell);
				strcpy_s(q->type, strlen(newtype) + 1, newtype);
				strcpy_s(q->ISBN, strlen(newisbn) + 1, newisbn);
				strcpy_s(q->book_name, strlen(a) + 1, a);
				strcpy_s(q->writer, strlen(newwriter) + 1, newwriter);
				strcpy_s(q->intro, strlen(newintro) + 1, newintro);
				strcpy_s(q->remark, strlen(newremark) + 1, newremark);
				strcpy_s(q->is_or_no, strlen("��") + 1, "��");
				q->popular = 0;
				q->repertory = 0;
				q->repertory++;
				q->standing_stock = 0;
				q->standing_stock++;
				sqlstr = "INSERT INTO book VALUES('";
				sqlstr += q->ISBN;
				sqlstr += "','";
				sqlstr += q->book_name;
				sqlstr += "','";
				sqlstr += q->spell;
				sqlstr += "','";
				sqlstr += q->type;
				sqlstr += "','";
				sqlstr += q->writer;
				sqlstr += "','";
				sqlstr += q->intro;
				sqlstr += "','";
				sqlstr += q->is_or_no;
				sqlstr += "',";
				char ss[MAXSIZE];
				sqlstr += itoa(q->standing_stock, ss, 10);
				sqlstr += ",";
				sqlstr += itoa(q->repertory, ss, 10);
				sqlstr += ",'";
				sqlstr += q->remark;
				sqlstr += "',";
				sqlstr += itoa(q->popular, ss, 10);
				sqlstr += ")";
				mysql_query(&mysql, sqlstr.c_str());
				pre->next = q;
				q->next = NULL;
				cout << "��ӳɹ���" << endl;
			}
			else
			{
				cout << "��ISBN���ѱ�ע��" << endl;
			}
		} while (nnum == 1);
	}
	mysql_close(&mysql);
	printf("�������������һ��\n");
	while (_getch())
		teacher_menu(head, t, st, bs, root, bp);
}
//�޸�ͼ����Ϣ
void modify_book(book *head, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp)        /*�޸�ͼ����Ϣ*/
{
	char book_name[50];
	book *p, *pre = NULL;
	cout << "ѡ����Ҫ�޸ĵ�ͼ�����ƣ�" << endl;
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
		cout << "��ѡ��Ҫ�޸ĵ���Ϣ��ţ�" << endl;
		cout << "1.����ļ��" << endl;
		cout << "2.����ı�ע" << endl;
		int n;
		cin >> n;
		if (n == 1)
		{
			char intro[200];
			cout << "�������µļ�飺" << endl;
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
			cout << "�������µı�ע��" << endl;
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
		cout << "���鲻���ڣ���" << endl;
		system("pause");
		printf("�������������һ��\n");
		while (_getch())
			teacher_menu(head, t, st, bs, root, bp);
	}
	printf("�������������һ��\n");
	while (_getch())
		teacher_menu(head, t, st, bs, root, bp);
}

/*ԭӱ*/
//shell����
/*void shellsort(char** strs, int n){	int len = 0;	int i, j, d;	char **s;	s = (char**)malloc(sizeof(char*)*MAXSIZE);	s[0] = (char*)malloc(sizeof(char) * 20);	i = 0;	while (i < n)	{		//cout << strs[i] << endl;		s[i + 1] = (char*)malloc(sizeof(char) * 20);		s[i + 1] = strs[i];		i++;	}	len = n;	s[i + 1] = (char*)malloc(sizeof(char) * 20);	s[i + 1] = '\0';	d = len / 2;	while (d >= 1)	{		for (i = d + 1; i <= len; i++)		{			s[0] = s[i];			j = i - d;			while (j > 0 && strcmp(s[0], s[j]) < 0)			{				s[j + d] = s[j];				j = j - d;			}			s[j + d] = s[0];		}		d = d / 2;	}	for (i = 1; i <= len; i++)	{		printf("%s\n", s[i]);		//cout << s[i] << endl;	}	system("pause");}*/
void MySql() {
	//�ر���һ�����ݽṹ
	MYSQL mysql;
	string sqlstr;
	//��ʼ�����ݿ�
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	}
	else {
		cout << "mysql_library_init() failed" << endl;
		exit(-1);
	}
	system("pause");
	//��ʼ�����ݽṹ
	if (NULL != mysql_init(&mysql)) {
		cout << "mysql_init() succeed" << endl;
	}
	else {
		cout << "mysql_init() failed" << endl;
		exit(1);
	}
	system("pause");
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	if (0 == mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	}
	else {
		cout << "mysql_options() failed" << endl;
		exit(-1);
	}
	system("pause");
	//�������ݿ�
	if (NULL
		!= mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0))
		//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	{
		cout << "mysql_real_connect() succeed" << endl;
	}
	else {
		cout << "mysql_real_connect() failed" << endl;
		exit(-1);
	}
	system("pause");
	//ͼ����Ϣ��(book)
	//ISBN:���,book_name:����,class:���,writer:����,intro:���,is_or_no:�Ƿ��ڹ�,remark:��ע,standing_stock:�ִ���,repertory:���,popular:�ܻ�ӭ�̶�
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
		system("pause");
		exit(-1);
	}
	system("pause");

	//ѧ����Ϣ��(student)
	//student_ID:ѧ��ѧ��,student_name��ѧ������,student_sex:ѧ���Ա�,student_phone:ѧ���绰,department:����ϵ,take_effect:ѧ����Чʱ ��
	//lose_efficay:ѧ��ʧЧʱ��,Arrearage:Ƿ�ѽ��,borrow_sum:�ۻ���������,remark:��ע
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
	//��ʦ��Ϣ��(teacher)
	//job_number:��ʦ������,teacher_name:��ʦ����,teacher_sex:��ʦ�Ա�,teacher_phone:��ʦ�绰,remark:��ע
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
	////���ı�borrowing_table��
	////ISBN:���,student_ID:ѧ��ѧ��,borrow_time:��������,return_time:��������,isrenew:�Ƿ�����,remark:��ע
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

	//����в�������
	sqlstr =
		"INSERT INTO book VALUES('9787544285147','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�',4),";
	sqlstr += "('9787544285148','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�',4),";
	sqlstr += "('9787544285149','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�',4),";
	sqlstr += "('9787544285150','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�',4),";
	sqlstr += "('9787544285151','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�',4),";
	sqlstr += "('9787544285152','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�',4),";
	sqlstr += "('9787020024759','Χ��','weicheng','��ѧ','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ','��',3,5,'��',2),";
	sqlstr += "('9787020024760','Χ��','weicheng','��ѧ','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ','��',3,5,'��',2),";
	sqlstr += "('9787020024761','Χ��','weicheng','��ѧ','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ','��',3,5,'��',2),";
	sqlstr += "('9787020024762','Χ��','weicheng','��ѧ','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ','��',3,5,'��',2),";
	sqlstr += "('9787020024763','Χ��','weicheng','��ѧ','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ','��',3,5,'��',2),";
	sqlstr += "('9787020049295','ƽ��������','pingfandeshijie','��ѧ','·ң','��ƽ�������硷��һ����ʵ����С˵��Ҳ��һ��С˵��ʽ�ļ���ʷ������Ũ�����й�����ũ�����ʷ��Ǩ���̣���С˵��ȫ��ʽ�ر������й�����������������ڽ�ʮ��Ĺ��������£�ͨ�����ӵ�ì�ܾ��𣬿̻�����ײ��ڶ���ͨ�˵�����','��',0,3,'һ�������𻵣��趪��',3),";
	sqlstr += "('9787020049296','ƽ��������','pingfandeshijie','��ѧ','·ң','��ƽ�������硷��һ����ʵ����С˵��Ҳ��һ��С˵��ʽ�ļ���ʷ������Ũ�����й�����ũ�����ʷ��Ǩ���̣���С˵��ȫ��ʽ�ر������й�����������������ڽ�ʮ��Ĺ��������£�ͨ�����ӵ�ì�ܾ��𣬿̻�����ײ��ڶ���ͨ�˵�����','��',0,3,'һ�������𻵣��趪��',3),";
	sqlstr += "('9787020049297','ƽ��������','pingfandeshijie','��ѧ','·ң','��ƽ�������硷��һ����ʵ����С˵��Ҳ��һ��С˵��ʽ�ļ���ʷ������Ũ�����й�����ũ�����ʷ��Ǩ���̣���С˵��ȫ��ʽ�ر������й�����������������ڽ�ʮ��Ĺ��������£�ͨ�����ӵ�ì�ܾ��𣬿̻�����ײ��ڶ���ͨ�˵�����','��',0,3,'һ�������𻵣��趪��',3),";
	sqlstr += "('9787020026906','��¹ԭ','bailuyuan','��ѧ','����ʵ','����һ��μ��ƽԭ��ʮ���Ǩ������ʷʫ��һ���й�ũ���쵶�ʡ���Ŀ���ĵĳ����������˹���Ȣ��ɥ�����ص�������ʾ�Ų��顣һ�������������Ϊ�����¹ԭ��ͳ�δ����������ѣ�������һĻĻ���Ķ��ǵĻ�硣','��',1,3,'��',2),";
	sqlstr += "('9787020026907','��¹ԭ','bailuyuan','��ѧ','����ʵ','����һ��μ��ƽԭ��ʮ���Ǩ������ʷʫ��һ���й�ũ���쵶�ʡ���Ŀ���ĵĳ����������˹���Ȣ��ɥ�����ص�������ʾ�Ų��顣һ�������������Ϊ�����¹ԭ��ͳ�δ����������ѣ�������һĻĻ���Ķ��ǵĻ�硣','��',1,3,'��',2),";
	sqlstr += "('9787020026908','��¹ԭ','bailuyuan','��ѧ','����ʵ','����һ��μ��ƽԭ��ʮ���Ǩ������ʷʫ��һ���й�ũ���쵶�ʡ���Ŀ���ĵĳ����������˹���Ȣ��ɥ�����ص�������ʾ�Ų��顣һ�������������Ϊ�����¹ԭ��ͳ�δ����������ѣ�������һĻĻ���Ķ��ǵĻ�硣','��',1,3,'��',2),";
	sqlstr += "('9787549529322','����','kanjian','��ʷ','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼','��',3,5,'��',2),";
	sqlstr += "('9787549529323','����','kanjian','��ʷ','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼','��',3,5,'��',2),";
	sqlstr += "('9787549529324','����','kanjian','��ʷ','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼','��',3,5,'��',2),";
	sqlstr += "('9787549529325','����','kanjian','��ʷ','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼','��',3,5,'��',2),";
	sqlstr += "('9787549529326','����','kanjian','��ʷ','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼','��',3,5,'��',2),";
	sqlstr += "('9787508645056','��Ĺ¶����������','nidegudusuibaiyourong','����','��ͬ','�¶�֮������ã���¶�֮���ǳɳ����Ȿ�����¼��33�ֹ¶��У�ϣ�������������Լ�ĳ���������εĳɳ������Ը��ȱ��˸�����һ���˶�����Ը�պ�����ʱ��ᱻ�Լ��ж���','��',3,3,'��Ч',0),";
	sqlstr += "('9787508645057','��Ĺ¶����������','nidegudusuibaiyourong','����','��ͬ','�¶�֮������ã���¶�֮���ǳɳ����Ȿ�����¼��33�ֹ¶��У�ϣ�������������Լ�ĳ���������εĳɳ������Ը��ȱ��˸�����һ���˶�����Ը�պ�����ʱ��ᱻ�Լ��ж���','��',3,3,'��Ч',0),";
	sqlstr += "('9787508645058','��Ĺ¶����������','nidegudusuibaiyourong','����','��ͬ','�¶�֮������ã���¶�֮���ǳɳ����Ȿ�����¼��33�ֹ¶��У�ϣ�������������Լ�ĳ���������εĳɳ������Ը��ȱ��˸�����һ���˶�����Ը�պ�����ʱ��ᱻ�Լ��ж���','��',3,3,'��Ч',0)";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() insert 1data succeed" << endl;
	}
	else {
		cout << "mysql_query() insert 1data failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	sqlstr = "INSERT INTO student VALUES('1705064109','��Ц��','Ů','18834166336','����ҽѧ����','20170901','20210701',0,3,'��'),";
	sqlstr += "('1509024219','�ξ�','Ů','13303590256','���̹���','20150901','20190701',0,3,'��'),";
	sqlstr += "('1613004747','����','��','18103485619','�������','20160901','20200701',0,2,'��'),";
	sqlstr += "('1802094127','����','��','18406582150','��е��','20180901','20220701',0,0,'��'),";
	sqlstr += "('1410024336','����','Ů','13466992580','Ӣ��','20150901','20190701',0,2,'ѧ����Ϣ���ڣ���ע��'),";
	sqlstr += "('1704034143','Ѧ����','��','13835999499','��ҩ����','20170901','20210701',0,3,'��')";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() insert 2data succeed" << endl;
	}
	else {
		cout << "mysql_query() insert 2data failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	sqlstr = "INSERT INTO teacher VALUES('01025','��','Ů','15524877534','��'),";
	sqlstr += "('04103','��ï��','��','17633417821','��'),";
	sqlstr += "('07081','����ƽ','��','13603593363','��'),";
	sqlstr += "('16045','����Ƽ','Ů','13994858711','��'),";
	sqlstr += "('10016','������','Ů','18636369763','��')";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() insert 3data succeed" << endl;
	}
	else {
		cout << "mysql_query() insert 3data failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	sqlstr = "INSERT INTO borrowing_table VALUES('9787020049295','1509024219','20181001','20181013','��','��'),";
	sqlstr += "('9787020026906','1509024219','20181115','20181224','��','��'),";
	sqlstr += "('9787020026907','1509024219','20181115','20181224','��','��'),";
	sqlstr += "('9787020049296','1705064109','20181127','20190105','��','��'),";
	sqlstr += "('9787544285148','1613004747','20181208','20190106','��','��'),";
	sqlstr += "('9787020024759','1613004747','20181208','20190106','��','��'),";
	sqlstr += "('9787020049297','1704034143','20181210','20190108','��','��'),";
	sqlstr += "('9787549529322','1704034143','20181210','20190108','��','��'),";
	sqlstr += "('9787544285149','1509024219','20181214','20190112','��','��'),";
	sqlstr += "('9787549529323','1410024336','20170302','20170316','��','��'),";
	sqlstr += "('9787020024760','1410024336','20160516','20160523','��','��'),";
	sqlstr += "('9787544285150','1705064109','20181220','20190118','��','��'),";
	sqlstr += "('9787544285151','1704034143','20181010','20181108','��','��')";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() insert 4data succeed" << endl;
	}
	else {
		cout << "mysql_query() insert 4data failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	cout << "���ݿⴴ���ɹ�" << endl;
	mysql_close(&mysql);
	system("pause");
}
//ѧ����Ϣ�����ʼ��
student * StudentLink() {
	return NULL;
}
//ͼ����Ϣ�����ʼ��
book * BookLink() {
	return NULL;
}
void initData(book **bo, student **st, teacher_sequence *t, borrow_sequence *bs, tire **root, bookpopular *bp) {
	//�ر���һ�����ݽṹ
	MYSQL mysql;
	string sqlstr;
	//��ʼ�����ݿ�
	mysql_library_init(0, NULL, NULL);
	//��ʼ�����ݽṹ
	mysql_init(&mysql);
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
//��ʼ���ֵ���
	*root = initTire();
	MYSQL_RES *result;
	MYSQL_FIELD *field;
	MYSQL_ROW row;
	//��ʼ��ͼ����Ϣ��
	sqlstr = "SELECT * FROM book";
	mysql_query(&mysql, sqlstr.c_str());
	int numfields = 0;	//ͳ�ƽ�����е��ֶ���
	int numRows = 0;	//ͳ�ƽ�����е�����
	result = mysql_store_result(&mysql);		//����ѯ��ȫ�������ȡ���ͻ���
	numfields = mysql_num_fields(result);
	numRows = mysql_num_rows(result);
	//while (field = mysql_fetch_field(result))	//���ؽ�����е�����Ϣ(�ֶ�)
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
		while (row = mysql_fetch_row(result))	//���ؽ�������еļ�¼
		{
			//ͼ���Ƽ���
			strcpy_s(bp->bp[i].ISBN, strlen(row[0]) + 1, row[0]);
			strcpy_s(bp->bp[i].book_name, strlen(row[1]) + 1, row[1]);
			strcpy_s(bp->bp[i].spell, strlen(row[2]) + 1, row[2]);
			strcpy_s(bp->bp[i].type, strlen(row[3]) + 1, row[3]);
			strcpy_s(bp->bp[i].writer, strlen(row[4]) + 1, row[4]);
			strcpy_s(bp->bp[i].intro, strlen(row[5]) + 1, row[5]);
			strcpy_s(bp->bp[i].is_or_no, strlen(row[6]) + 1, row[6]);
			bp->bp[i].standing_stock = atoi(row[7]);	//���ַ���ת��Ϊint
			bp->bp[i].repertory = atoi(row[8]);
			strcpy_s(bp->bp[i].remark, strlen(row[9]) + 1, row[9]);
			bp->bp[i++].popular = atoi(row[10]);
			bp->length++;
			//book��
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
			tireInsert(root, row[2]);			//�����ֵ���
			strcpy_s(p->type, strlen(row[3]) + 1, row[3]);
			strcpy_s(p->writer, strlen(row[4]) + 1, row[4]);
			strcpy_s(p->intro, strlen(row[5]) + 1, row[5]);
			strcpy_s(p->is_or_no, strlen(row[6]) + 1, row[6]);
			p->standing_stock = atoi(row[7]);	//���ַ���ת��Ϊint
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
				//���½ڵ���뵽��ͷ
				p->next = (*bo);
				(*bo) = p;
			}
		}
	}
	mysql_free_result(result);	//�ͷ�result�ռ�
	//��ʼ�����ı�
	borrowing_table b[MAXSIZE][MAXSIZE];
	sqlstr = "SELECT * FROM borrowing_table";
	mysql_query(&mysql, sqlstr.c_str());
	result = mysql_store_result(&mysql);		//����ѯ��ȫ�������ȡ���ͻ���
	numfields = mysql_num_fields(result);
	numRows = mysql_num_rows(result);
	if (result)
	{
		int i, j;

		//�ȳ�ʼ��Ϊ��
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
	mysql_free_result(result);	//�ͷ�result�ռ�
	//��ʼ��ѧ����
	sqlstr = "SELECT * FROM student";
	mysql_query(&mysql, sqlstr.c_str());
	result = mysql_store_result(&mysql);		//����ѯ��ȫ�������ȡ���ͻ���
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
			q->Arrearge = atoi(row[7]);		//���ַ���ת��Ϊ����
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
	mysql_free_result(result);	//�ͷ�result�ռ�
	//��ʼ��borrow_sequence
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
	//��ʼ����ʦ��
	sqlstr = "SELECT * FROM teacher";
	mysql_query(&mysql, sqlstr.c_str());
	result = mysql_store_result(&mysql);		//����ѯ��ȫ�������ȡ���ͻ���
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
	mysql_free_result(result);	//�ͷ�result�ռ�
	mysql_close(&mysql);
	//system("pause");
}
//�������ͼ����Ϣ
void displaybook(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID)
{
	int count = 1;
	book *p;

	cout << endl;
	cout << "|---------------------------------------ͼ����Ϣ-----------------------------------------|" << endl;
	cout << "|���  ���           ����                ����         ���    �Ƿ���   �ݲ���   �ִ���|" << endl;
	p = bo;
	while (p)
	{
		p->number = count++;
		printf("|%-6d%-15s%-20s%-13s%-12s%-10s%-5d%5d  |\n", p->number, p->ISBN, p->book_name, p->writer, p->type, p->is_or_no, p->repertory, p->standing_stock);
		p = p->next;
	}
	printf("�������������һ��\n");
	while (_getch())
	student_menu(bo, t, st, bs, root, bp, student_ID);
}
//չʾ�����ϸ��Ϣ
void displaydetailed(book **bo) {
	cout << "��ѡ�����������˽�����Ϣ�����:" << endl;
	int number;
	cin >> number;
	book *pre = *bo;
	char com[MAXSIZE];
	while (pre)
	{
		if (pre->number == number)
		{
			cout << "�Ȿ��ļ��Ϊ��" << endl;
			cout << pre->intro << endl;
			pre->popular++;
			strcpy_s(com, strlen(pre->book_name) + 1, pre->book_name);
		}
		//������������ͬ������ܻ�ӭ�̶ȶ���1
		if (strcmp(pre->book_name, com) == 0 && pre->number != number)
		{
			pre->popular++;
		}
		pre = pre->next;

	}
}
//���ѧ����Ϣ
void displaystudent(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp) {
	system("cls");
	student *p = st;
	printf("|------------------------------------------------------------------------ѧ����Ϣ��-------------------------------------------------------------------|\n");
	printf("|ѧ��ѧ��        ѧ������        ѧ���Ա�     ѧ���绰      ����ϵ��      ѧ����Чʱ��      ѧ��ʧЧʱ��       Ƿ�ѽ��         �ۼƽ�����        ��ע|\n");
	while (p)
	{
		printf("%-20s%-15s%-10s%-15s%-15s%-20s%-18s%-16d%-17d%-10s\n", p->student_ID,p->student_name,p->student_sex,p->student_phone,p->department,p->take_effect,p->lose_efficay,p->Arrearge,p->boorow_sum,p->remark);
		p = p->next;
	}

	printf("�������������һ��\n");
	while (_getch())
		teacher_menu(bo, t, st, bs, root, bp);
}
//�����ʦ��Ϣ��
void displayteacher(teacher_sequence *t) {
	int i;
	printf("-----------------------------------��ʦ��Ϣ��---------------------------------\n");
	printf("||     ������            ����               �Ա�              �绰          ||\n");
	for (i = 1; i <= t->length; i++)
	{
		printf("||     %-5s          %-7s                %-2s            %-11s      ||\n", t->te[i].job_number, t->te[i].teacher_name, t->te[i].teacher_sex, t->te[i].teacher_phone);
	}
}
//����ѧ�Ų���ѧ���Ľ�����Ϣ
void showstudentborrow(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID) {
	system("cls");
	student *p = st;
	int i;
	printf("|--------------------------------------ͼ�������Ϣ------------------------------------|\n");
	printf("|���                ѧ��ѧ��         ��������         ��������     �Ƿ�����       ��ע|\n");
	while (p)
	{
		if (strcmp(p->student_ID, student_ID) == 0)
		{
			for (i = 0; i < p->length; i++)
			{
				printf("%-20s%-18s%-17s%-15s%-14s%-10s\n", p->borrow[i].ISBN, p->borrow[i].student_ID, p->borrow[i].boorow_time, p->borrow[i].return_time, p->borrow[i].isrenew, p->borrow[i].remark);
			}
			break;
		}
		p = p->next;
	}
	printf("�������������һ��\n");
	while (_getch())
	student_menu(bo, t, st, bs, root, bp, student_ID);
}
/*��С��*/
//һ�ι鲢�㷨���������tabs[u...m]��tabs[m+1...v]�ϲ��������tabg[u...v]
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
//һ�˹鲢�㷨����tabs�г���Ϊlen��������������ι鲢�ɳ���Ϊ2*len�������  ����tabg��
void  mergepass(borrow_sequence *tabs, borrow_sequence *tabg, int len)
{
	int i, j, n;
	n = tabg->length = tabs->length;
	i = 1;
	while (i <= n - 2 * len + 1)  //����iΪ��㣬����Ϊlen���������������һ�ν��й鲢
	{
		merge(tabs, tabg, i, i + len - 1, i + 2 * len - 1);
		i = i + 2 * len;
	}
	if (i + len - 1 < n)
	{
		merge(tabs, tabg, i, i + len - 1, n);   //һ�ι鲢
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

//���������Ϣ��
void displayborrow(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp) {
	system("cls");
	mergesort(&bs);
	int i;
	printf("|---------------------------------------ͼ�������Ϣ----------------------------------|\n");
	printf("|  ���             ѧ��ѧ��          ��������         ��������     �Ƿ�����      ��ע|\n");
	for (i = 1; i <= bs.length; i++)
	{
		cout << " " << bs.bt[i].ISBN << "     " << bs.bt[i].student_ID << "           " << bs.bt[i].boorow_time << "        " << bs.bt[i].return_time << "        " << bs.bt[i].isrenew << "         " << bs.bt[i].remark << endl;
	}

	printf("�������������һ��\n");
	while (_getch())
		teacher_menu(bo, t, st, bs, root, bp);
}
//�����鼮����ѯͼ����Ϣ
void SeeBook(book *bo, char *type) {
	book *p = bo;
	cout << endl;
	cout << "|------------------------------------ͼ����Ϣ--------------------------------------|" << endl;
	cout << "|���           ����                ����         ���    �Ƿ���   �ݲ���   �ִ���|" << endl;
	while (p)
	{
		if (strcmp(p->type, type) == 0)
		{
			printf("|%-15s%-20s%-13s%-12s%-10s%-5d%5d  |\n", p->ISBN, p->book_name, p->writer, p->type, p->is_or_no, p->repertory, p->standing_stock);
		}
		p = p->next;
	}

}
//����ѧ�Ų鿴������Ϣ
void SeeBorrow(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID, char id[]) {
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
	printf("�������������һ��\n");
	while (_getch())
	{
		student_menu(bo, t, st, bs, root, bp, student_ID);
	}
}

/*ԭӱ*/
//��������ʱ�����ĺ���
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
	//������ʱ
	if (year1 == year2) {
		d1 = runnian(year1, month1, day1);
		d2 = runnian(year2, month2, day2);
		if (d1 >= d2) days = d1 - d2;
		else days = d2 - d1;
	}
	//��ݲ���ʱ
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
//���ݵ������ڸ���ѧ��Ƿ�����
void updataArrearge(student *st) {
	MYSQL mysql;
	string sqlstr;
	mysql_library_init(0, NULL, NULL);
	//��ʼ�����ݽṹ
	mysql_init(&mysql);
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	student *p;
	string temp;
	int i;
	p = st;
	while (p)
	{
		int sum = 0;
		if (p->length != 0)
		{
			p->Arrearge = 0;
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
				mysql_query(&mysql, sqlstr.c_str());

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
//һ�˹鲢�㷨����tabs�г���Ϊlen��������������ι鲢�ɳ���Ϊ2*len�������  ����tabg��
void  mergepasspopular(bookpopular *tabs, bookpopular *tabg, int len)
{
	int i, j, n;
	n = tabg->length = tabs->length;
	i = 1;
	while (i <= n - 2 * len + 1)  //����iΪ��㣬����Ϊlen���������������һ�ν��й鲢
	{
		mergepopular(tabs, tabg, i, i + len - 1, i + 2 * len - 1);
		i = i + 2 * len;
	}
	if (i + len - 1 < n)
	{
		mergepopular(tabs, tabg, i, i + len - 1, n);   //һ�ι鲢
	}
	else
	{
		for (j = i; j <= n; j++)
		{
			tabg->bp[j] = tabs->bp[j];
		}
	}
}
//���鼮�ܻ�ӭ�̶Ƚ�������
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
//ͼ���Ƽ�����
void display_popular(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID) {
	system("cls");
	mergesortpopular(&bp);
	int i;
	book save[MAXSIZE];
	int top = 0;
	cout << endl;
	cout << "|-----------------------------------ͼ���Ƽ���-------------------------------------|" << endl;
	cout << "|���           ����                ����         ���    �Ƿ���   �ݲ���   �ִ���|" << endl;
	for (i = bp.length; i >= 1; i--)
	{
		if (bp.bp[i].repertory == 1)
		{
			save[top++] = bp.bp[i];
		}

		else if (strcmp(bp.bp[i].book_name, bp.bp[i - 1].book_name) != 0)
		{
			save[top++] = bp.bp[i];
		}
		//printf("|%-6d%-15s%-20s%-13s%-12s%-10s%-5d%5d  |\n", bp->bp[i].number, bp->bp[i].ISBN, bp->bp[i].book_name, bp->bp[i].writer, bp->bp[i].type, bp->bp[i].is_or_no, bp->bp[i].repertory, bp->bp[i].standing_stock);
	}
	for (i = 0; i < top; i++)
	{
		printf("|%-15s%-20s%-13s%-12s%-10s%-5d%5d  |\n", save[i].ISBN, save[i].book_name, save[i].writer, save[i].type, save[i].is_or_no, save[i].repertory, save[i].standing_stock);
	}
	printf("�������������һ��\n");
	while (_getch())
	student_menu(bo, t, st, bs, root, bp, student_ID);
}
//�������㷨����ʦ��Ϣ��������
void siftTeacher(teacher_sequence *t, int k, int m) {		//ɸѡ�㷨
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
	//������Ԫ�ؽ���
	for (i = t->length / 2; i >= 1; i--)
	{
		siftTeacher(t, i, t->length);
	}
	for (i = t->length; i >= 2; i--)		//����С��Ԫ�غ����һ������
	{
		t->te[0] = t->te[i];
		t->te[i] = t->te[1];
		t->te[1] = t->te[0];
		siftTeacher(t, 1, i - 1);
	}
}
//�������㷨���������ŶԽ��ı�����
void siftBorrow(borrow_sequence *bs, int k, int m) {		//ɸѡ�㷨
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
	//������Ԫ�ؽ���
	for (i = bs->length / 2; i >= 1; i--)
	{
		siftBorrow(bs, i, bs->length);
	}
	for (i = bs->length; i >= 2; i--)		//����С��Ԫ�غ����һ������
	{
		bs->bt[0] = bs->bt[i];
		bs->bt[i] = bs->bt[1];
		bs->bt[1] = bs->bt[0];
		siftBorrow(bs, 1, i - 1);
	}
}

void updataMYSQLbook(book *bo) {
	MYSQL mysql;
	string sqlstr;
	mysql_library_init(0, NULL, NULL);
	//��ʼ�����ݽṹ
	mysql_init(&mysql);
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	cout << "���ݿ����ӳɹ�" << endl;
	system("pause");
	book *p = bo;
	while (p)
	{
		sqlstr = "update book set popular = ";
		char ss[MAXSIZE];
		sqlstr += itoa(p->popular, ss, 10);		//���ַ���ת��Ϊ����
		cout << ss << "---" << endl;
		sqlstr += " where ISBN = '";
		sqlstr += p->ISBN;
		sqlstr += "'";
		mysql_query(&mysql, sqlstr.c_str());
		p = p->next;
	}
	cout << "ͼ���ܻ�ӭ�ɶ����³ɹ�������" << endl;
	mysql_close(&mysql);
}

/*��С��*/
//����������ʾͼ����Ϣ ,�˴�����˳�������
void  display_book_type(book *head, char book_type[])
{
	printf("������%s����ͼ������������\n", book_type);
	//	printf("%20s%30s%30s%15s%50s%30s%20s%30s", "���", "����", "���", "����", "���", "�ִ�", "���", "��ע");
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
//����ˢ�¿�棬����Ϊͷ�ڵ�  �� ��������
book * refresh(book * head, char borrowed_name[30])
{
	MYSQL mysql;
	string sqlstr;
	mysql_library_init(0, NULL, NULL);
	//��ʼ�����ݽṹ
	mysql_init(&mysql);
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	system("pause");
	book *p = head;
	int count;
	while (p)
	{
		if (strcmp(borrowed_name, p->book_name) == 0)
		{
			p->standing_stock--;
			count = p->standing_stock;
		}
		p = p->next;
	}
	sqlstr = "update book set standing_stock = ";
	char ss[MAXSIZE];
	sqlstr += itoa(count, ss, 10);
	sqlstr += " where book_name = '";
	sqlstr += borrowed_name;
	sqlstr += "'";
	mysql_query(&mysql, sqlstr.c_str());
	mysql_close(&mysql);
	return head;
}
//����ʱ�亯��
char *returnbooktime()              /*ʱ�亯��*/
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
//������� ˢ�� ѧ����Ϣ��  ����Ϊ����ѧ��ѧ�ţ�ѧ����Ϣ��ָ�룬�������
student * refresh_student(char borrowed_stu_ID[20], student * stu_head, char borrowed_ISBN[30])
{
	MYSQL mysql;
	string sqlstr;
	mysql_library_init(0, NULL, NULL);
	//��ʼ�����ݽṹ
	mysql_init(&mysql);
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	student * p = stu_head;
	while (p&&strcmp(p->student_ID, borrowed_stu_ID) != 0)
	{
		p = p->next;
	}
	//����������һ
	p->boorow_sum++;

	//ѧ���Ľ�����Ϣ��
	int t = p->boorow_sum - 1;
	strcpy_s(p->borrow[t].ISBN, 30, borrowed_ISBN);
	strcpy_s(p->borrow[t].isrenew, 10, "��");
	strcpy_s(p->borrow[t].student_ID, 20, borrowed_stu_ID);
	sqlstr = "update student set borrow_sum = ";
	char ss[MAXSIZE];
	sqlstr += itoa(p->boorow_sum, ss, 10);
	sqlstr += " where student_ID = '";
	sqlstr += borrowed_stu_ID;
	sqlstr += "'";
	mysql_query(&mysql, sqlstr.c_str());

	//��������
	char str[MAXSIZE];
	strcpy_s(str, strlen(time()) + 1, time());
	strcpy_s(p->borrow[t].boorow_time, 30, str);
	//��������
	strcpy_s(str, strlen(returnbooktime()) + 1, returnbooktime());
	strcpy_s(p->borrow[t].return_time, 30, str);
	sqlstr = "INSERT INTO borrowing_table VALUES('";
	sqlstr += borrowed_ISBN;
	sqlstr += "','";
	sqlstr += borrowed_stu_ID;
	sqlstr += "','";
	sqlstr += p->borrow[t].boorow_time;
	sqlstr += "','";
	sqlstr += p->borrow[t].return_time;
	sqlstr += "','��','��')";
	mysql_query(&mysql, sqlstr.c_str());
	mysql_close(&mysql);
	return stu_head;
}
//�������Ž��н���
void input_num(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID)
{

	MYSQL mysql;
	string sqlstr;
	mysql_library_init(0, NULL, NULL);
	//��ʼ�����ݽṹ
	mysql_init(&mysql);
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	cout << "���ݿ����ӳɹ�" << endl;
	system("pause");
	printf("�����������ͼ�����ţ�\n");
	char temp_num[20];
	scanf_s("%s", temp_num, 20);
	book *p;
	p = bo;
	while (strcmp(p->ISBN, temp_num) != 0)
	{
		p = p->next;
	}
	if (!p)
	{
		printf("û�и�ͼ�飬����������:\n");
		input_num(bo, t, st, bs, root, bp, student_ID);
	}
	else
	{
		if (strcmp(p->is_or_no, "��") == 0)
		{
			printf("���ҳɹ�������Ϊ������......\n");

			//char temp_ID[20];
			//char temp_key[30];
			//printf("ѧ�ţ� ");
			//scanf_s("%s", temp_ID, 20);
			//printf("���룺 ");
			//scanf_s("%s", temp_key, 30);

			////�����֤�ɹ���ִ�����³���,�˴�����Ϊ��ֵ  ����  ����½����Ϣ����������
			//if (strcmp(temp_ID, "1410024336") == 0 && strcmp(temp_key, "1") == 0)
			//{
				printf("����ɹ�!\n");
				strcpy_s(p->is_or_no, 10, "��");
				sqlstr = "update book set is_or_no = '��' where ISBN = '";
				sqlstr += temp_num;
				sqlstr += "'";
				if (mysql_query(&mysql, sqlstr.c_str()) == 0)
					cout << "���ݿ�ˢ��" << endl;
				mysql_close(&mysql);
				//�˴�ˢ��ͼ����
				char borrowed_book_name[30];
				strcpy_s(borrowed_book_name, 20, p->book_name);

				bo = refresh(bo, borrowed_book_name);
				//display(new_head);

				//�˴�ˢ��ѧ����Ϣ��,������ѧ��ѧ�ţ�ѧ����ָ�룬����ͼ��ţ�
				//student * stu;
				st = refresh_student(student_ID, st, temp_num);
			/*}*/
				printf("�������������һ��\n");
				while (_getch())
				student_menu(bo, t, st, bs, root, bp, student_ID);
		}
		else
		{
			printf("����ѡ�鼮�Ѿ������ߣ������½���ѡ��!\n");
			input_num(bo, t, st, bs, root, bp, student_ID);
		}
	}
	
}
//����
void borrow_book(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID)
{
	system("cls");
	printf("******************************��dei,���������ѡ��!!!************************\n");
	printf("**                  1.��֪���Լ����ʲô��                                 **\n");
	printf("**                  2.���е㷽,ֻ֪����������͵���                    **\n");
	printf("**                  3.��Ŀǰ����ã������鿴���е���                     **\n");
	printf("*****************************************************************************\n");

	int tt;
	scanf_s("%d", &tt, 1);
	if (tt == 1)
	{

		/****************����Ӧ�����޸� ***************
		book *head = ���ȡһ��;
		******�˴����ø���������ʾ��ͼ����Ϣ�ĺ���**************
		***********************************************/
		char s[MAXSIZE];
		cout << "���������������ƴ��" << endl;
		cin >> s;
		printTire(bo, t, st, bs, root, bp, student_ID, s);
		input_num(bo, t, st, bs, root, bp, student_ID);

	}
	else if (tt == 2)
	{
		char temp_book_type[30];
		printf("����������������͵���:\n");
		scanf_s("%s", temp_book_type, 30);


		/*************�˴�Ӧ�޸ģ���ȡͼ����Ϣ���ͷ���*******

		book *head = ���ȡһ��;
		display_book_type(head,temp_book_type);

		****************************************************/
		book *head = bo;
		display_book_type(head, temp_book_type);
		input_num(bo, t, st, bs, root, bp, student_ID);

		//input_num(head);


	}
	else if (tt == 3)
	{
		displaybook(bo, t, st, bs, root, bp, student_ID);
		input_num(bo, t, st, bs, root, bp, student_ID);
	}
	else
	{
		printf("������������½���ѡ��");
		borrow_book(bo, t, st, bs, root, bp, student_ID);
	}
}

/*������*/
//��������
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

/*ԭӱ*/
//����ͼ�����ƽ���ɾ��
book * delete_book(book *head, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp)
{
	MYSQL mysql;
	string sqlstr;
	mysql_library_init(0, NULL, NULL);
	//��ʼ�����ݽṹ
	mysql_init(&mysql);
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	cout << "���ݿ����ӳɹ�" << endl;
	system("pause");
	printf("��������Ҫɾ��������:\n");
	char delete_book_name[50];
	scanf_s("%s", delete_book_name, 50);
	book *pre = NULL, *p;

	if (!(head))
	{
		printf("ͼ����Ϣ��Ϊ�գ��޷�����ɾ�������������룺\n");
		delete_book(head, t, st, bs, root, bp);
	}

	//��������ж���������Ƿ����ɾ��
	p = head;  //pΪ���ڴ���Ľ��

	while (p&&strcmp(p->book_name, delete_book_name) != 0)  //�ҵ������ֹͣ
	{
		pre = p;
		p = p->next;
	}
	if (!p)  //pΪ�գ���ʾû�д��飬�޷�����ɾ��
	{
		printf("��Ǹ!δ��ͼ����Ϣ���ҵ����飡���������룺\n");
		delete_book(head, t, st, bs, root, bp);
	}
	else
	{
		if ((p->repertory == p->standing_stock) && strcmp(p->remark, "��Ч") == 0)  //�ڹ���=�����������ͼ�鱸עΪ"��Ч"����ʾ���Խ���ɾ��
		{
			printf("���ҵ���ͼ��,����Ϊ��ɾ��  loading......\n");

			while (p)     //p��Ϊ�գ���һֱѭ������ֹͬ����©ɾ
			{
				if (!pre)   //Ҫɾ����һ�����
				{
					head = head->next;
					p = head;
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
			sqlstr = "delete from book where book_name = '";
			sqlstr += delete_book_name;
			sqlstr += "'";
			mysql_query(&mysql, sqlstr.c_str());
			mysql_close(&mysql);
			printf("ɾ���ɹ���\n");
			printf("�������������һ��\n");
			while (_getch())
				teacher_menu(head, t, st, bs, root, bp);
			return  head;
		}

		else
		{
			printf("�������ͼ��Ϊ��Ч�鼮�����ܽ���ɾ��!,���������룺\n");
			delete_book(head, t, st, bs, root, bp);
		}
	}
	return  head;
}

/*��С��*/
//�������ˢ��ͼ����Ϣ��
book * returned_book(book *book_head, char return_book_ID[20])
{
	MYSQL mysql;
	string sqlstr;
	mysql_library_init(0, NULL, NULL);
	//��ʼ�����ݽṹ
	mysql_init(&mysql);
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	book *p = book_head;

	//��¼���������
	char  temp_name[50];
	//�������Ϊ�ڹ�
	while (p)
	{
		if (strcmp(return_book_ID, p->ISBN) == 0)
		{
			strcpy_s(p->is_or_no, 10, "��");
			strcpy_s(temp_name, 50, p->book_name);
		}
		p = p->next;
	}
	sqlstr = "update book set is_or_not = '��' where ISBN = '";
	sqlstr += return_book_ID;
	sqlstr += "'";
	mysql_query(&mysql, sqlstr.c_str());
	book *q = book_head;
	int count;
	//��ͬ������ڹ�����+1;
	while (q)
	{
		if (strcmp(temp_name, q->book_name) == 0)
		{
			q->standing_stock++;
			count = q->standing_stock;
		}
		q = q->next;
	}
	sqlstr = "update book set standing_stock = ";
	char ss[MAXSIZE];
	sqlstr += itoa(count, ss, 10);
	sqlstr += " where book_name = '";
	sqlstr += temp_name;
	sqlstr += "'";
	mysql_query(&mysql, sqlstr.c_str());
	mysql_close(&mysql);
	return book_head;
}
//�������ˢ��ѧ����Ϣ�ͽ�����Ϣ��  ����������ѧ��ѧ�ţ� ѧ����Ϣ��ָ�룬�������
student * returned_student(char returned_stu_ID[20], book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char returned_ISBN[30])
{
	MYSQL mysql;
	string sqlstr;
	mysql_library_init(0, NULL, NULL);
	//��ʼ�����ݽṹ
	mysql_init(&mysql);
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	mysql_real_connect(&mysql, "localhost", "root", "123456", "datastructdesign", 3306, NULL, 0);
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	student * p = st;
	while (p&&strcmp(returned_stu_ID, p->student_ID) != 0)
	{
		p = p->next;
	}
	int i = 0;
	//ѧ��������Ϣ˳�����Ҹ���
	while (i < p->boorow_sum && strcmp(p->borrow[i].ISBN, returned_ISBN) != 0)
	{
		i++;
	}
	if (p->Arrearge > 0)
	{
		printf("���ѳ��ڽ��飬��Ҫ֧����Ӧ�ķ��ã�\n");
		printf("�˴�Ĭ���Ѿ�֧������.\n");
	}
	sqlstr = "delete from borrowing_table where ISBN = '";
	sqlstr += returned_ISBN;
	sqlstr += "'";
	mysql_query(&mysql, sqlstr.c_str());
	for (; i < p->boorow_sum; i++)
	{
		p->borrow[i] = p->borrow[i + 1];
	}
	p->boorow_sum--;
	sqlstr = "update student set borrow_sum = ";
	char ss[MAXSIZE];
	sqlstr += itoa(p->boorow_sum, ss, 10);
	sqlstr += " where student_ID = '";
	sqlstr += returned_stu_ID;
	sqlstr += "'";
	mysql_query(&mysql, sqlstr.c_str());
	mysql_close(&mysql);
	printf("����ɹ�!\n");
	return st;
}
//����
void return_book(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID)
{
	

	//������һ������ȡѧ��   �ٴε���ѧ����½��������ƥ�䣬�˴�Ϊ��ֵ

		//��ƥ��ɹ�������������
		printf("����Ϊ��Ŀǰ���еĽ��������\n");

		//չʾѧ���������
		SeeBorrow(bo, t, st, bs, root, bp, student_ID, student_ID);

		printf("\n��������Ҫ�������ţ�\n");
		char temp_return_book[20];
		scanf_s("%s", temp_return_book, 20);
		returned_book(bo, temp_return_book);
		returned_student(student_ID, bo, t, st, bs, root, bp, temp_return_book);
	

}
/*������*/
void clock_delay(int n)/*ʱ����ʱ����*/
{
	clock_t tm;
	tm = clock();
	while (clock()<tm + n);
}
//��Ա����
void adv()
{
	cout << "\n\n\n\n";
	cout << "\t\t\t\t\t*================================*\n";
	cout << "\t\t\t\t\t\t" << "����Ʒ�����˹�ͬŬ�����" << endl;
	cout << "\t\t\t\t\t\t" << "������Ա��:" << endl;
	clock_delay(1000);
	cout << "\t\t\t\t\t\t" << "�鳤�����Ѻ�" << endl;
	clock_delay(1000);
	cout << "\t\t\t\t\t\t" << "��Ա��������" << endl;
	clock_delay(1000);
	cout << "\t\t\t\t\t\t" << "��Ա����С��" << endl;
	clock_delay(1000);
	cout << "\t\t\t\t\t\t" << "��Ա��ԭӱ" << endl;
	clock_delay(1000);
	cout << "\t\t\t\t\t\t" << "ָ����ʦ���ܷ��" << endl;
	cout << "\t\t\t\t\t*================================*\n";
	cout << "\n\n\n\n";
	system("pause");
	system("cls");
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
	updataArrearge(st);
	//studentregistered(st);
	//teacherregistered(&t);
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

	//updataMYSQLbook();
	/*char x[] = "e";*/
	//SeeBook(bo, x);
	//cout << tireSearch(root, x)->isStr << "----" << endl;
	//printSpell(bo, x);
	//printTire(bo, root, x);
	//borrow_book(bo,root,st);

	//displaydetailed(&bo);
	//updataMYSQLbook(bo);
	//display_popular(&bp);
	//add_book(bo);
	/*return_book(st, bo);*/
	/*quicksort(&bs, 1, bs.length);
	displayborrow(&bs);*/
	//modify_book(bo);
	//displaybook(bo);
	//displaydetailed(&bo);
	//system("pause");
	system("color 3E");
	adv();
	system("title ͼ�����ϵͳ");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t\t*=================================*\n");
	printf("\t\t\t\t\t|* - * - * - * - * - * - * - * - *|\n");
	printf("\t\t\t\t\t||                               ||\n");
	printf("\t\t\t\t\t|*     ��ӭʹ��ͼ�����ϵͳ��    *|\n");
	printf("\t\t\t\t\t||      �밴���������ϵͳ��     ||\n");
	printf("\t\t\t\t\t|*                               *|\n");
	printf("\t\t\t\t\t|| - * - * - * - * - * - * - * - ||\n");
	printf("\t\t\t\t\t*=================================*\n");
	while (_getch())
	{
		menu(bo, t, st, bs, root, bp);
	}

	return 0;
}
//�����߼�
void menu(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp)
{
	/*book *bo;
	teacher_sequence t;
	student *st;
	borrow_sequence bs;
	tire *root;
	bookpopular bp;
	st = StudentLink();
	bo = BookLink();
	initData(&bo, &st, &t, &bs, &root, &bp);
	st = addstudent(st);
	addteacher(&t);*/
	system("color 3E");
	int n;
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t*=================================*\n");
	printf("\t\t\t\t\t|* - * - * - * ���˵�* - * - * - *|\n");
	printf("\t\t\t\t\t||                               ||\n");
	printf("\t\t\t\t\t|*      [1]  ѧ����¼            *|\n");
	printf("\t\t\t\t\t||                               ||\n");
	printf("\t\t\t\t\t|*      [2]  ѧ��ע��            *|\n");
	printf("\t\t\t\t\t||                               ||\n");
	printf("\t\t\t\t\t|*      [3]  ��ʦ��¼            *|\n");
	printf("\t\t\t\t\t||                               ||\n");
	printf("\t\t\t\t\t|*      [4]  �˳�ϵͳ            *|\n");
	printf("\t\t\t\t\t||                               ||\n");
	printf("\t\t\t\t\t|* - * - * - * - * - * - * - * - *|\n");
	printf("\t\t\t\t\t*=================================*\n");
	printf("����������ѡ��1-4����");
	scanf_s("%d", &n);
	getchar();
	menu_switch(bo, t, st, bs, root, bp, n);
}

//���˵�ͨ��ѡ��
void menu_switch(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, int n)
{
	int i;
	switch (n)
	{
	case 1:member(bo, t, st, bs, root, bp); break;
	case 2:studentregistered(bo, t, st, bs, root, bp); break;
	case 3:teacher_register(bo, t, st, bs, root, bp); break;
	case 4:exit(1); system("pause"); break;
	default:printf("�����������������루1-4����");
		cin >> i; menu_switch(bo, t, st, bs, root, bp, i); break;
	}
}

void member(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp)
{

	char student_ID[MAXSIZE];
	char password[MAXSIZE];
	
	int i;
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t\t\t***=============================***\n\n");
	printf("\t\t\t\t\t    �˻���account����");
	cin >> student_ID;
	printf("\t\t\t\t\t    ���루password����");
	cin >> password;
	studentlanding(bo, t, st, bs, root, bp, student_ID, password);
	//��ʱ����
	//i=member_log_in(student_ID);
	/*student *p = st;
	while (p)
	{
		if (strcmp(p->student_ID, student_ID) == 0) {
			break;
		}
		p = p->next;
	}*/
	/*if (1)
	{
		student_menu(bo, t, st, bs, root, bp, student_ID);
	}*/
}

void student_menu(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID)
{
	//system("color 2E");
	system("cls");
	//��¼����Ϣ
	//student_menu_id(st,student_ID,student_name);
	//��¼�߿�ִ�еĹ���
	printf("\t\t\t\t\t*=================================*\n");
	printf("\t\t\t\t\t|* - * - * - * ���ܱ�* - * - * - *|\n");
	printf("\t\t\t\t\t||                               ||\n");
	printf("\t\t\t\t\t|*      [1]  ������Ϣ            *|\n");
	printf("\t\t\t\t\t||      [2]  ����ͼ����Ϣ        ||\n");
	printf("\t\t\t\t\t|*      [3]  ����ͼ��            *|\n");
	printf("\t\t\t\t\t||      [4]  �����鼮            ||\n");
	printf("\t\t\t\t\t|*      [5]  �黹�鼮            *|\n");
	printf("\t\t\t\t\t||      [6]  ��ѯ���ı�          ||\n");
	printf("\t\t\t\t\t|*      [7]  ͼ�黶ӭ������      *|\n");
	printf("\t\t\t\t\t|*      [8]  �˳���¼            *|\n");
	printf("\t\t\t\t\t||                               ||\n");
	printf("\t\t\t\t\t|* - * - * - * - * - * - * - * - *|\n");
	printf("\t\t\t\t\t*=================================*\n");
	int i;
	printf("��������Ҫִ�еĹ��ܣ�1-8����");
	cin >> i;
	student_menu_switch(bo, t, st, bs, root, bp, i, student_ID);
}

void student_menu_switch(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, int n, char *student_ID)
{
	int i;
	switch (n)
	{
	case 1:print_student_information(bo, t, st, bs, root, bp, student_ID); break;//���ѧ����Ϣ ������Ƿ���Ҫ�޸���Ϣ	
	case 2:displaybook(bo, t, st, bs, root, bp, student_ID); break;//���ȫ��ͼ����Ϣ	
	case 3: {
		cout << "����������Ҫ���鼮��ƴ��:" << endl;
		char front[MAXSIZE];
		cin >> front;
		printTire(bo, t, st, bs, root, bp, student_ID, front);
		break; }//����
	case 4:borrow_book(bo, t, st, bs, root, bp, student_ID); break;//�����鼮
	case 5:return_book(bo, t, st, bs, root, bp, student_ID); break;//����
	case 6:showstudentborrow(bo, t, st, bs, root, bp, student_ID); break;//��ѯ���ı�
	case 7:display_popular(bo, t, st, bs, root, bp, student_ID); break;//���ܻ�ӭͼ��
	case 8:menu(bo, t, st, bs, root, bp); break;//���˵�
	default: {system("cls");
		printf("�����������������루1-8����");
		cin >> i;
		student_menu_switch(bo, t, st, bs, root, bp,i, student_ID); break; }
	}
}
//��Ա������Ϣ
void print_student_information(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, char *student_ID)
{
	system("cls");

	student *p = st;
	while (p)
	{
		if (strcmp(p->student_ID, student_ID) == 0)
		{
			break;
		}
		p = p->next;
	}
	//student_menu_id(st, student_ID,p->student_name);
	printf("\n");
	printf("\t\t\t\t\t*=================================*\n");
	printf("\t\t\t\t\t * - * - * - ������Ϣ* - * - * - * \n");
	printf("\t\t\t\t\t                                   \n");
	printf("\t\t\t\t\t       ѧ�ţ�%-20s\n", p->student_ID);
	printf("\t\t\t\t\t       ������%-10s\n", p->student_name);
	printf("\t\t\t\t\t       �Ա�%-10s\n", p->student_sex);
	printf("\t\t\t\t\t       ϵ��%-20s\n", p->department);
	printf("\t\t\t\t\t       ��ϵ��ʽ��%-20s\n", p->student_phone);
	printf("\t\t\t\t\t       �ۼƽ�������%-5d\n", p->boorow_sum);
	printf("\t\t\t\t\t       Ƿ�ѽ�%-5d\n", p->Arrearge);
	printf("\t\t\t\t\t       ��Чʱ�䣺%-30s\n", p->take_effect);
	printf("\t\t\t\t\t       ʧЧʱ�䣺%-30s\n", p->lose_efficay);
	printf("\t\t\t\t\t                                   \n");
	printf("\t\t\t\t\t * - * - * - * - * - * - * - * - * \n");
	printf("\t\t\t\t\t*=================================*\n");
	printf("\n");
	printf("�������������һ��\n");
	while (_getch())
	student_menu(bo, t, st, bs, root, bp, p->student_ID);

}

//��ʦ��¼������书��
void teacher_register(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp)
{
	int i;
	char teacher_ID[20];
	char password[30];
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t\t\t***=============================***\n\n");
	printf("\t\t\t\t\t    �˻���account����");
	gets_s(teacher_ID, 20);
	printf("\t\t\t\t\t    ���루password����");
	gets_s(password, 30);
	//����ȶ�
	//�ȶԳɹ�����ʱ

	if (1)
	{
		teacher_menu(bo, t, st, bs, root, bp);
	}
}


//��ʦ�����ִ�еĲ���
void teacher_menu(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp)
{
	system("cls");
	//teacher_menu_id();//�����½����Ϣ
					  //��¼�߿�ִ�еĹ���

	printf("\t\t\t\t\t*=================================*\n");
	printf("\t\t\t\t\t|* - * - * - * ���ܱ�* - * - * - *|\n");
	printf("\t\t\t\t\t||                               ||\n");
	printf("\t\t\t\t\t|*      [1]  ���ͼ��            *|\n");
	printf("\t\t\t\t\t||      [2]  ɾ��ͼ��            ||\n");
	printf("\t\t\t\t\t|*      [3]  �޸�ͼ����Ϣ        *|\n");
	printf("\t\t\t\t\t||      [4]  ��ʾ����ѧ����Ϣ    ||\n");
	printf("\t\t\t\t\t|*      [5]  ��ʾ���н�������Ϣ  *|\n");
	printf("\t\t\t\t\t|*      [6]  �˳���¼            *|\n");
	printf("\t\t\t\t\t||                               ||\n");
	printf("\t\t\t\t\t|* - * - * - * - * - * - * - * - *|\n");
	printf("\t\t\t\t\t*=================================*\n");

	int i;
	printf("������Ҫִ�еĹ��ܣ�1-6����");
	scanf_s("%d", &i);
	teacher_menu_switch(bo, t, st, bs, root, bp, i);
}

//��ʦ������������ʽ
void teacher_menu_switch(book *bo, teacher_sequence t, student *st, borrow_sequence bs, tire *root, bookpopular bp, int n)
{
	int i;
	switch (n)
	{
	case 1:add_book(bo, t, st, bs, root, bp); break;//���
	case 2:delete_book(bo, t, st, bs, root, bp); break;//ɾ��
	case 3:modify_book(bo, t, st, bs, root, bp); break;//�޸�
	case 4:displaystudent(bo, t, st, bs, root, bp); break;//���л�Ա��Ϣ
	case 5:displayborrow(bo, t, st, bs, root, bp); break;//��������Ϣ
	case 6:menu(bo, t, st, bs, root, bp); break;
	default:printf("�����������������루1-6����");
		scanf_s("%d", &i); getchar(); teacher_menu_switch(bo, t, st, bs, root, bp, i); break;
	}
}
