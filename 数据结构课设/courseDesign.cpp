#include <winsock.h>
#include <iostream>
#include <string>
#include <mysql.h>
#define MAXSIZE 100
using namespace std;
typedef struct b{			//ͼ����Ϣ��
	char ISBN[20];			//���
	char book_name[50];		//����
	char writer[15];		//����
	char intro[200];		//���
	int standing_stock;		//�ִ���
	int repertory;			//���
	char remark[200];		//��ע
	struct b *next;
} book;
typedef struct s{			//ѧ����Ϣ��
	char student_ID[20];	//ѧ��ѧ��
	char student_name[10];	//ѧ������
	char student_sex[10];	//ѧ���Ա�	
	char student_phone[20];	//ѧ���绰
	char department[20];	//����ϵ
	char take_effect[30];	//ѧ����Чʱ��
	char lose_efficay[30];	//ѧ��ʧЧʱ��
	int Arrearge;			//Ƿ�ѽ��
	int boorow_sum;			//�ۻ���������
	char remark[200];		//��ע
	borrowing_table borrow[100];
	struct s *next;
}student;
typedef struct {			//��ʦ��Ϣ��
	char job_number[20];	//��ʦ������
	char teacher_name[20];	//��ʦ����
	char teacher_sex[10];	//��ʦ�Ա�
	char teacher_phone[20];	//��ʦ�绰
	char remark[200];		//��ע
}teacher;
typedef struct {			//���ı�
	char ISBN[20];			//���
	char student_ID[20];	//ѧ��ѧ��
	char boorow_time[30];	//��������
	char return_time[30];	//��������
	char isrenew[10];		//�Ƿ�����
	char remark[200];		//��ע
}borrowing_table;

int main() {
	//�ر���һ�����ݽṹ
	MYSQL mysql;
	string sqlstr;
	//��ʼ�����ݿ�
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	}
	else {
		cout << "mysql_library_init() failed" << endl;
		return -1;
	}
	system("pause");
	//��ʼ�����ݽṹ
	if (NULL != mysql_init(&mysql)) {
		cout << "mysql_init() succeed" << endl;
	}
	else {
		cout << "mysql_init() failed" << endl;
		return -1;
	}
	system("pause");
	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	if (0 == mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	}
	else {
		cout << "mysql_options() failed" << endl;
		return -1;
	}
	system("pause");
	//�������ݿ�
	if (NULL
		!= mysql_real_connect(&mysql, "localhost", "root", "123456", "DataStructDesign", 3306, NULL, 0))
		//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	{
		cout << "mysql_real_connect() succeed" << endl;
	}
	else {
		cout << "mysql_real_connect() failed" << endl;
		return -1;
	}
	system("pause");
	//ͼ����Ϣ��(book)
	//ISBN:���,book_name:����,writer:����,intro:���,remark:��ע,standing_stock:�ִ���,repertory:���
	/*sqlstr = "create table if not exists book(ISBN VARCHAR(20),book_name VARCHAR(50),writer VARCHAR(15),intro VARCHAR(200),";
	sqlstr += "standing_stock INT,repertory INT,remark VARCHAR(200),PRIMARY KEY(ISBN))";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() create book succeed" << endl;
	}
	else {
		cout << "mysql_query() create book failed" << endl;
		mysql_close(&mysql);
		return -1;
	}
	system("pause");*/

	//ѧ����Ϣ��(student)
	//student_ID:ѧ��ѧ��,student_name��ѧ������,student_sex:ѧ���Ա�,student_phone:ѧ���绰,department:����ϵ,take_effect:ѧ����Чʱ��
	//lose_efficay:ѧ��ʧЧʱ��,Arrearage:Ƿ�ѽ��,borrow_sum:�ۻ���������,remark:��ע
	//sqlstr = "creat table if not exists student(student_ID VARCHAR(20),student_name VARCHAR(10),student_sex VARCHAR(10),student_phone VARCHAR(20),";
	//sqlstr += "department VARCHAR(20),take_effect VARCHAR(30),lose_efficay VARCHAR(30),Arrearge INT,borrow_sum INT,remark VARCHAR(200),PRIMARY KEY(student_ID))";
	//if (0 == mysql_query(&mysql, sqlstr.c_str())) {
	//	cout << "mysql_query() create student succeed" << endl;
	//}
	//else {
	//	cout << "mysql_query() create student failed" << endl;
	//	system("pause");
	//	mysql_close(&mysql);
	//	return -1;
	//}
	//system("pause");
	////��ʦ��Ϣ��(teacher)
	////job_number:��ʦ������,teacher_name:��ʦ����,teacher_sex:��ʦ�Ա�,teacher_phone:��ʦ�绰,remark:��ע
	//sqlstr = "creat table if not exists teacher(job_number VARCHAR(20),teacher_name VARCHAR(20),teacher_sex VARCHAR(10),teacher_phone VARCHAR(20),remark VARCHAR(200))��PRIMARY KEY(job_number)";
	//if (0 == mysql_query(&mysql, sqlstr.c_str())) {
	//	cout << "mysql_query() create teacher succeed" << endl;
	//}
	//else {
	//	cout << "mysql_query() create teacher failed" << endl;
	//	mysql_close(&mysql);
	//	return -1;
	//}
	//system("pause");
	////���ı�borrowing_table��
	////ISBN:���,student_ID:ѧ��ѧ��,borrow_time:��������,return_time:��������,isrenew:�Ƿ�����,remark:��ע
	//sqlstr = "creat table if not exists borrowing_table(ISBN VARCHAR(20),student_ID VARCHAR(20),borrow_time VARCHAR(30),return_time VARCHAR(30),isrenew VARCHAR(10),remark VARCHAR(200),PRIMARY KEY(ISBN))";
	//if (0 == mysql_query(&mysql, sqlstr.c_str())) {
	//	cout << "mysql_query() create borrowing_table succeed" << endl;
	//}
	//else {
	//	cout << "mysql_query() create borrowing_table failed" << endl;
	//	mysql_close(&mysql);
	//	return -1;
	//}
	//system("pause");
	//����в�������
	/*sqlstr =
		"INSERT INTO book VALUES('9787545148','����','��Ұ����','�����������',4,6,'��');";
	if (0 == mysql_query(&mysql, sqlstr.c_str())) {
		cout << "mysql_query() insert data succeed" << endl;
	}
	else {
		cout << "mysql_query() insert data failed" << endl;
		mysql_close(&mysql);
		return -1;
	}*/
	MYSQL_RES *result;
	MYSQL_FIELD *field;
	MYSQL_ROW row;
	sqlstr = "SELECT * FROM book";
	if (0 == mysql_query(&mysql, sqlstr.c_str()))
		cout << "mysql_query() select data succeed" << endl;
	int numfields = 0;	//ͳ�ƽ�����е��ֶ���
	int numRows = 0;	//ͳ�ƽ�����е�����
	result = mysql_store_result(&mysql);		//����ѯ��ȫ�������ȡ���ͻ���
	numfields = mysql_num_fields(result);
	numRows = mysql_num_rows(result);
	while (field = mysql_fetch_field(result))	//���ؽ�����е�����Ϣ(�ֶ�)
	{
		cout << field->name << "---";
	}
	cout << endl;
	if (result)
	{
		while (row = mysql_fetch_row(result))	//���ؽ�������еļ�¼
		{
			for (int i = 0; i < numfields; i++)
			{
				cout << row[i] << "---";
			}
			cout << endl;
		}
	}
	mysql_free_result(result);	//�ͷ�result�ռ�
	mysql_close(&mysql);
	system("pause");
	return 0;
}