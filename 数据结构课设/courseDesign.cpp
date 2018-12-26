#include <winsock.h>
#include <iostream>
#include <string>
#include <mysql.h>
#define MAXSIZE 100
using namespace std;
typedef struct b{			//图书信息表
	char ISBN[20];			//书号
	char book_name[50];		//书名
	char writer[15];		//作者
	char intro[200];		//简介
	int standing_stock;		//现存量
	int repertory;			//库存
	char remark[200];		//备注
	struct b *next;
} book;
typedef struct s{			//学生信息表
	char student_ID[20];	//学生学号
	char student_name[10];	//学生姓名
	char student_sex[10];	//学生性别	
	char student_phone[20];	//学生电话
	char department[20];	//所在系
	char take_effect[30];	//学生生效时间
	char lose_efficay[30];	//学生失效时间
	int Arrearge;			//欠费金额
	int boorow_sum;			//累积借书总量
	char remark[200];		//备注
	borrowing_table borrow[100];
	struct s *next;
}student;
typedef struct {			//老师信息表
	char job_number[20];	//老师工作号
	char teacher_name[20];	//老师姓名
	char teacher_sex[10];	//老师性别
	char teacher_phone[20];	//老师电话
	char remark[200];		//备注
}teacher;
typedef struct {			//借阅表
	char ISBN[20];			//书号
	char student_ID[20];	//学生学号
	char boorow_time[30];	//借书日期
	char return_time[30];	//还书日期
	char isrenew[10];		//是否续借
	char remark[200];		//备注
}borrowing_table;

int main() {
	//必备的一个数据结构
	MYSQL mysql;
	string sqlstr;
	//初始化数据库
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	}
	else {
		cout << "mysql_library_init() failed" << endl;
		return -1;
	}
	system("pause");
	//初始化数据结构
	if (NULL != mysql_init(&mysql)) {
		cout << "mysql_init() succeed" << endl;
	}
	else {
		cout << "mysql_init() failed" << endl;
		return -1;
	}
	system("pause");
	//在连接数据库之前，设置额外的连接选项
	//可以设置的选项很多，这里设置字符集，否则无法处理中文
	if (0 == mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	}
	else {
		cout << "mysql_options() failed" << endl;
		return -1;
	}
	system("pause");
	//连接数据库
	if (NULL
		!= mysql_real_connect(&mysql, "localhost", "root", "123456", "DataStructDesign", 3306, NULL, 0))
		//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
	{
		cout << "mysql_real_connect() succeed" << endl;
	}
	else {
		cout << "mysql_real_connect() failed" << endl;
		return -1;
	}
	system("pause");
	//图书信息表(book)
	//ISBN:书号,book_name:书名,writer:作者,intro:简介,remark:备注,standing_stock:现存量,repertory:库存
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

	//学生信息表(student)
	//student_ID:学生学号,student_name：学生姓名,student_sex:学生性别,student_phone:学生电话,department:所在系,take_effect:学生生效时间
	//lose_efficay:学生失效时间,Arrearage:欠费金额,borrow_sum:累积借书总量,remark:备注
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
	////老师信息表(teacher)
	////job_number:老师工作号,teacher_name:老师姓名,teacher_sex:老师性别,teacher_phone:老师电话,remark:备注
	//sqlstr = "creat table if not exists teacher(job_number VARCHAR(20),teacher_name VARCHAR(20),teacher_sex VARCHAR(10),teacher_phone VARCHAR(20),remark VARCHAR(200))，PRIMARY KEY(job_number)";
	//if (0 == mysql_query(&mysql, sqlstr.c_str())) {
	//	cout << "mysql_query() create teacher succeed" << endl;
	//}
	//else {
	//	cout << "mysql_query() create teacher failed" << endl;
	//	mysql_close(&mysql);
	//	return -1;
	//}
	//system("pause");
	////借阅表（borrowing_table）
	////ISBN:书号,student_ID:学生学号,borrow_time:借书日期,return_time:还书日期,isrenew:是否续借,remark:备注
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
	//向表中插入数据
	/*sqlstr =
		"INSERT INTO book VALUES('9787545148','恶意','东野圭吾','恶意深刻人性',4,6,'无');";
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
	int numfields = 0;	//统计结果集中的字段数
	int numRows = 0;	//统计结果集中的行数
	result = mysql_store_result(&mysql);		//将查询的全部结果读取到客户端
	numfields = mysql_num_fields(result);
	numRows = mysql_num_rows(result);
	while (field = mysql_fetch_field(result))	//返回结果集中的列信息(字段)
	{
		cout << field->name << "---";
	}
	cout << endl;
	if (result)
	{
		while (row = mysql_fetch_row(result))	//返回结果集中行的记录
		{
			for (int i = 0; i < numfields; i++)
			{
				cout << row[i] << "---";
			}
			cout << endl;
		}
	}
	mysql_free_result(result);	//释放result空间
	mysql_close(&mysql);
	system("pause");
	return 0;
}