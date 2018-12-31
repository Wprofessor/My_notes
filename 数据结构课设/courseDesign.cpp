#include <winsock.h>
#include <iostream>
#include <string.h>
#include<stdlib.h>
#include <mysql.h>
#include<time.h>
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning( disable : 4996 )	//��ֹtime��������
#define MAXSIZE 50
using namespace std;
typedef struct b {			//ͼ����Ϣ��
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
	struct b *next;
} book;
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
	int id;
	while (word[i])
	{
		id = word[i] - 'a';
		if (!node->children[id])
		{
			node->children[id] = new tire();	//���ٿռ�
			node->children[id]->count = 0;
			node->children[id]->isStr = FALSE;
		}
		node = node->children[id];
		node->count++;
		i++;
	}
	node->isStr = TRUE;
}
int tireSearch(tire *root, char *word) {
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
			return 0;
		}
	}
	return node->count;
}
//��ӡ������ǰ׺��ͼ����Ϣ
void printTire(tire *root, char *front) {
	tire *node = root;
	int i = 0;
	bool flag = TRUE;
	while (front[i])
	{
		int id = front[i] - 'a';
		if (node->children[id])
		{
			node = node->children[id];
		}
		else
		{
			cout << "δ�ҵ�����Ҫ��ͼ�飬����������" << endl;
			break;
		}
		i++;
	}
	for ( i = 0; i < MAXSIZE; i++)
	{
		while (true)
		{

		}
	}
}
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
	//ISBN:���,book_name:����,class:���,writer:����,intro:���,is_or_no:�Ƿ��ڹ�,remark:��ע,standing_stock:�ִ���,repertory:���
	sqlstr = "create table if not exists book(ISBN VARCHAR(20),";
	sqlstr += "book_name VARCHAR(50)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "spell VARCHAR(100)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "class VARCHAR(30)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "writer VARCHAR(30)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "intro VARCHAR(1000)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "is_or_not VARCHAR(10)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "standing_stock INT,";
	sqlstr += "repertory INT,";
	sqlstr += "remark VARCHAR(200)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,PRIMARY KEY(ISBN))";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() create book succeed" << endl;
	}
	else {
		cout << "mysql_query() create book failed" << endl;
		mysql_close(&mysql);
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
		"INSERT INTO book VALUES('9787544285147','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�'),";
	sqlstr += "('9787544285148','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�'),";
	sqlstr += "('9787544285149','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�'),";
	sqlstr += "('9787544285150','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�'),";
	sqlstr += "('9787544285151','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�'),";
	sqlstr += "('9787544285152','����','eyi','��ѧ','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��','��',2,6,'����������ӹ�'),";
	sqlstr += "('9787020024759','Χ��','weicheng','��ѧ','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ','��',3,5,'��'),";
	sqlstr += "('9787020024760','Χ��','weicheng','��ѧ','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ','��',3,5,'��'),";
	sqlstr += "('9787020024761','Χ��','weicheng','��ѧ','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ','��',3,5,'��'),";
	sqlstr += "('9787020024762','Χ��','weicheng','��ѧ','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ','��',3,5,'��'),";
	sqlstr += "('9787020024763','Χ��','weicheng','��ѧ','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ','��',3,5,'��'),";
	sqlstr += "('9787020049295','ƽ��������','pingfandeshijie','��ѧ','·ң','��ƽ�������硷��һ����ʵ����С˵��Ҳ��һ��С˵��ʽ�ļ���ʷ������Ũ�����й�����ũ�����ʷ��Ǩ���̣���С˵��ȫ��ʽ�ر������й�����������������ڽ�ʮ��Ĺ��������£�ͨ�����ӵ�ì�ܾ��𣬿̻�����ײ��ڶ���ͨ�˵�����','��',0,3,'һ�������𻵣��趪��'),";
	sqlstr += "('9787020049296','ƽ��������','pingfandeshijie','��ѧ','·ң','��ƽ�������硷��һ����ʵ����С˵��Ҳ��һ��С˵��ʽ�ļ���ʷ������Ũ�����й�����ũ�����ʷ��Ǩ���̣���С˵��ȫ��ʽ�ر������й�����������������ڽ�ʮ��Ĺ��������£�ͨ�����ӵ�ì�ܾ��𣬿̻�����ײ��ڶ���ͨ�˵�����','��',0,3,'һ�������𻵣��趪��'),";
	sqlstr += "('9787020049297','ƽ��������','pingfandeshijie','��ѧ','·ң','��ƽ�������硷��һ����ʵ����С˵��Ҳ��һ��С˵��ʽ�ļ���ʷ������Ũ�����й�����ũ�����ʷ��Ǩ���̣���С˵��ȫ��ʽ�ر������й�����������������ڽ�ʮ��Ĺ��������£�ͨ�����ӵ�ì�ܾ��𣬿̻�����ײ��ڶ���ͨ�˵�����','��',0,3,'һ�������𻵣��趪��'),";
	sqlstr += "('9787020026906','��¹ԭ','bailuyuan','��ѧ','����ʵ','����һ��μ��ƽԭ��ʮ���Ǩ������ʷʫ��һ���й�ũ���쵶�ʡ���Ŀ���ĵĳ����������˹���Ȣ��ɥ�����ص�������ʾ�Ų��顣һ�������������Ϊ�����¹ԭ��ͳ�δ����������ѣ�������һĻĻ���Ķ��ǵĻ�硣','��',1,3,'��'),";
	sqlstr += "('9787020026907','��¹ԭ','bailuyuan','��ѧ','����ʵ','����һ��μ��ƽԭ��ʮ���Ǩ������ʷʫ��һ���й�ũ���쵶�ʡ���Ŀ���ĵĳ����������˹���Ȣ��ɥ�����ص�������ʾ�Ų��顣һ�������������Ϊ�����¹ԭ��ͳ�δ����������ѣ�������һĻĻ���Ķ��ǵĻ�硣','��',1,3,'��'),";
	sqlstr += "('9787020026908','��¹ԭ','bailuyuan','��ѧ','����ʵ','����һ��μ��ƽԭ��ʮ���Ǩ������ʷʫ��һ���й�ũ���쵶�ʡ���Ŀ���ĵĳ����������˹���Ȣ��ɥ�����ص�������ʾ�Ų��顣һ�������������Ϊ�����¹ԭ��ͳ�δ����������ѣ�������һĻĻ���Ķ��ǵĻ�硣','��',1,3,'��'),";
	sqlstr += "('9787549529322','����','kanjian','��ʷ','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼','��',3,5,'��'),";
	sqlstr += "('9787549529323','����','kanjian','��ʷ','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼','��',3,5,'��'),";
	sqlstr += "('9787549529324','����','kanjian','��ʷ','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼','��',3,5,'��'),";
	sqlstr += "('9787549529325','����','kanjian','��ʷ','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼','��',3,5,'��'),";
	sqlstr += "('9787549529326','����','kanjian','��ʷ','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼','��',3,5,'��'),";
	sqlstr += "('9787508645056','��Ĺ¶����������','nidegudusuibaiyourong','����','��ͬ','�¶�֮������ã���¶�֮���ǳɳ����Ȿ�����¼��33�ֹ¶��У�ϣ�������������Լ�ĳ���������εĳɳ������Ը��ȱ��˸�����һ���˶�����Ը�պ�����ʱ��ᱻ�Լ��ж���','��',3,3,'��'),";
	sqlstr += "('9787508645057','��Ĺ¶����������','nidegudusuibaiyourong','����','��ͬ','�¶�֮������ã���¶�֮���ǳɳ����Ȿ�����¼��33�ֹ¶��У�ϣ�������������Լ�ĳ���������εĳɳ������Ը��ȱ��˸�����һ���˶�����Ը�պ�����ʱ��ᱻ�Լ��ж���','��',3,3,'��'),";
	sqlstr += "('9787508645058','��Ĺ¶����������','nidegudusuibaiyourong','����','��ͬ','�¶�֮������ã���¶�֮���ǳɳ����Ȿ�����¼��33�ֹ¶��У�ϣ�������������Լ�ĳ���������εĳɳ������Ը��ȱ��˸�����һ���˶�����Ը�պ�����ʱ��ᱻ�Լ��ж���','��',3,3,'��')";
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
void initData(book **bo, student **st, teacher_sequence *t, borrow_sequence *bs, tire **root) {
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
		while (row = mysql_fetch_row(result))	//���ؽ�������еļ�¼
		{
			/*for (int i = 0; i < numfields; i++)
			{
				cout << row[i] << "---";
			}
			cout << endl;*/

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
//�������ͼ����Ϣ��
void displaybook(book *bo)
{
	book *p;
	cout << endl;
	cout << "|--------------------------------ͼ����Ϣ--------------------------------|" << endl;
	cout << "|���           ����                ����         ���      �ݲ���  �ִ���|" << endl;
	p = bo;
	while (p)
	{
		printf("|%-15s%-20s%-13s%-12s%-5d%5d  |\n", p->ISBN, p->book_name, p->writer, p->type, p->repertory, p->standing_stock);

		//cout << p->intro << endl;
		p = p->next;
	}
}
//���ѧ����Ϣ
void displaystudent(student  *st) {
	student *p;
	p = st;
	while (p)
	{
		cout << p->student_ID << "---" << p->student_name << "---" << p->student_sex << "---" << p->student_phone << "---" << p->department << "---" << p->Arrearge << endl;
		p = p->next;
	}
}
//�����ʦ��Ϣ��
void displayteacher(teacher_sequence *t) {
	int i;
	for (i = 0; i < t->length; i++)
	{
		cout << t->te[i + 1].job_number << "--" << t->te[i + 1].teacher_name << "--" << t->te[i + 1].teacher_sex << "--" << t->te[i + 1].teacher_phone << endl;
	}
}
//���������Ϣ��
void displayborrow(borrow_sequence *bs) {
	int i;
	for (i = 1; i <= bs->length; i++)
	{
		cout << bs->bt[i].ISBN << "--" << bs->bt[i].student_ID << endl;
	}
}
//����ѧ�Ų鿴������Ϣ
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
//ʱ�亯��
char *time()
{
	char a[50], b[50], c[50];
	char d[2];
	strcpy_s(d, strlen("0") + 1, "0");
	struct tm *local;
	time_t t;
	t = time(NULL);
	local = localtime(&t);
	_itoa(local->tm_year + 1900, a, 10);
	_itoa(local->tm_mon + 1, b, 10);
	_itoa(local->tm_mday, c, 10);
	if (local->tm_mon + 1 >= 1 && local->tm_mon <= 9)
	{
		strcat(d, b);
		strcpy(b, d);
	}
	if (local->tm_mday >= 1 && local->tm_mday <= 9)
	{
		strcat(d, c);
		strcpy_s(c, strlen(d) + 1, d);
	}
	strcat(a, b);
	strcat(a, c);
	return a;
}
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
	cout << "���ݿ����ӳɹ�" << endl;
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
				cout << "ѧ��Ƿ�ѽ����³ɹ�" << endl;

			}
		}
		p = p->next;
	}
	mysql_close(&mysql);
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
void updataMYSQLbook() {
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
	sqlstr = "update book set remark='emm' where book_name = 'Χ��'";

	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() UPDATA data succeed" << endl;
	}
	else {
		cout << "mysql_query() UPDATA data failed" << endl;
		system("pause");
		mysql_close(&mysql);
		exit(-1);
	}
	mysql_close(&mysql);
}
//���ѧ����Ϣ

int main() {
	//MySql();
	book *bo;
	teacher_sequence t;
	student *st;
	borrow_sequence bs;
	tire *root;
	st = StudentLink();
	bo = BookLink();
	initData(&bo, &st, &t, &bs, &root);
	displaybook(bo);
	/*updataArrearge(st);
	displaystudent(st);*/
	/*char id[] = "1509024219";
	SeeBorrow(st, id);
	*/
	/*heapsortTeacher(&t);
	displayteacher(&t);*/
	/*heapsortBorrow(&bs);
	displayborrow(&bs);*/
	//updataMYSQLbook();
	/*char x[] = "weicheng";
	cout << tireSearch(root, x) << "----" << endl;*/
	system("pause");
	return 0;
}