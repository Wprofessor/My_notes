#include <winsock.h>
#include <iostream>
#include <string>
#include <mysql.h>
#define MAXSIZE 100
using namespace std;
typedef struct b {			//ͼ����Ϣ��
	char ISBN[20];			//���
	char book_name[50];		//����
	char writer[15];		//����
	char intro[200];		//���
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
	borrowing_table *borrow[MAXSIZE];
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
	//ISBN:���,book_name:����,writer:����,intro:���,remark:��ע,standing_stock:�ִ���,repertory:���
	sqlstr = "create table if not exists book(ISBN VARCHAR(20),";
	sqlstr += "book_name VARCHAR(50)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "writer VARCHAR(30)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "intro VARCHAR(1000)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
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
		"INSERT INTO book VALUES('9787544285147','����','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��',2,6,'����������ӹ�'),";
	sqlstr += "('9787544285148','����','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��',2,6,'����������ӹ�'),";
	sqlstr += "('9787544285149','����','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��',2,6,'����������ӹ�'),";
	sqlstr += "('9787544285150','����','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��',2,6,'����������ӹ�'),";
	sqlstr += "('9787544285151','����','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��',2,6,'����������ӹ�'),";
	sqlstr += "('9787544285152','����','��Ұ����','�����⡷��̽�ʾ���ԣ��������ޱߵĶ�������ף�����������Ԩ�����˲�����������δ���������İ��ӣ�ɱ�˲���Ŀ�ģ������ֶΣ��������ǽ��������ǿ�ʼ��',2,6,'����������ӹ�'),";
	sqlstr += "('9787020024759','Χ��','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ',4,5,'��'),";
	sqlstr += "('9787020024760','Χ��','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ',4,5,'��'),";
	sqlstr += "('9787020024761','Χ��','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ',4,5,'��'),";
	sqlstr += "('9787020024762','Χ��','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ',4,5,'��'),";
	sqlstr += "('9787020024763','Χ��','Ǯ����','��Χ�ǡ����й��ִ���ѧʷ��һ�������صķ��С˵������Ϊ����������ʷ����������Ҫд��ս����֪ʶ���ӵ�Ⱥ�ࡣ',4,5,'��'),";
	sqlstr += "('9787020049295','ƽ��������','·ң','��ƽ�������硷��һ����ʵ����С˵��Ҳ��һ��С˵��ʽ�ļ���ʷ������Ũ�����й�����ũ�����ʷ��Ǩ���̣���С˵��ȫ��ʽ�ر������й�����������������ڽ�ʮ��Ĺ��������£�ͨ�����ӵ�ì�ܾ��𣬿̻�����ײ��ڶ���ͨ�˵�����',0,3,'һ�������𻵣��趪��'),";
	sqlstr += "('9787020049296','ƽ��������','·ң','��ƽ�������硷��һ����ʵ����С˵��Ҳ��һ��С˵��ʽ�ļ���ʷ������Ũ�����й�����ũ�����ʷ��Ǩ���̣���С˵��ȫ��ʽ�ر������й�����������������ڽ�ʮ��Ĺ��������£�ͨ�����ӵ�ì�ܾ��𣬿̻�����ײ��ڶ���ͨ�˵�����',0,3,'һ�������𻵣��趪��'),";
	sqlstr += "('9787020049297','ƽ��������','·ң','��ƽ�������硷��һ����ʵ����С˵��Ҳ��һ��С˵��ʽ�ļ���ʷ������Ũ�����й�����ũ�����ʷ��Ǩ���̣���С˵��ȫ��ʽ�ر������й�����������������ڽ�ʮ��Ĺ��������£�ͨ�����ӵ�ì�ܾ��𣬿̻�����ײ��ڶ���ͨ�˵�����',0,3,'һ�������𻵣��趪��'),";
	sqlstr += "('9787020026906','��¹ԭ','����ʵ','����һ��μ��ƽԭ��ʮ���Ǩ������ʷʫ��һ���й�ũ���쵶�ʡ���Ŀ���ĵĳ����������˹���Ȣ��ɥ�����ص�������ʾ�Ų��顣һ�������������Ϊ�����¹ԭ��ͳ�δ����������ѣ�������һĻĻ���Ķ��ǵĻ�硣',2,3,'��'),";
	sqlstr += "('9787020026907','��¹ԭ','����ʵ','����һ��μ��ƽԭ��ʮ���Ǩ������ʷʫ��һ���й�ũ���쵶�ʡ���Ŀ���ĵĳ����������˹���Ȣ��ɥ�����ص�������ʾ�Ų��顣һ�������������Ϊ�����¹ԭ��ͳ�δ����������ѣ�������һĻĻ���Ķ��ǵĻ�硣',2,3,'��'),";
	sqlstr += "('9787020026908','��¹ԭ','����ʵ','����һ��μ��ƽԭ��ʮ���Ǩ������ʷʫ��һ���й�ũ���쵶�ʡ���Ŀ���ĵĳ����������˹���Ȣ��ɥ�����ص�������ʾ�Ų��顣һ�������������Ϊ�����¹ԭ��ͳ�δ����������ѣ�������һĻĻ���Ķ��ǵĻ�硣',2,3,'��'),";
	sqlstr += "('9787549529322','����','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼',3,5,'��'),";
	sqlstr += "('9787549529323','����','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼',3,5,'��'),";
	sqlstr += "('9787549529324','����','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼',3,5,'��'),";
	sqlstr += "('9787549529325','����','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼',3,5,'��'),";
	sqlstr += "('9787549529326','����','��','�����������������ߺ������˲񾲽�������ʮ�����̵��Դ�����Ʒ�����ǲ񾲸��˵ĳɳ�����飬ĳ�̶ֳ�������������й�ʮ���Ǩ�ı���¼',3,5,'��'),";
	sqlstr += "('9787508645056','��Ĺ¶����������','��ͬ','�¶�֮������ã���¶�֮���ǳɳ����Ȿ�����¼��33�ֹ¶��У�ϣ�������������Լ�ĳ���������εĳɳ������Ը��ȱ��˸�����һ���˶�����Ը�պ�����ʱ��ᱻ�Լ��ж���',3,3,'��'),";
	sqlstr += "('9787508645057','��Ĺ¶����������','��ͬ','�¶�֮������ã���¶�֮���ǳɳ����Ȿ�����¼��33�ֹ¶��У�ϣ�������������Լ�ĳ���������εĳɳ������Ը��ȱ��˸�����һ���˶�����Ը�պ�����ʱ��ᱻ�Լ��ж���',3,3,'��'),";
	sqlstr += "('9787508645058','��Ĺ¶����������','��ͬ','�¶�֮������ã���¶�֮���ǳɳ����Ȿ�����¼��33�ֹ¶��У�ϣ�������������Լ�ĳ���������εĳɳ������Ը��ȱ��˸�����һ���˶�����Ը�պ�����ʱ��ᱻ�Լ��ж���',3,3,'��')";
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
	sqlstr += "('1410024336','����','Ů','13466992580','Ӣ��','20150901','20180701',0,2,'ѧ����Ϣ���ڣ���ע��'),";
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
student * StudentLink(student *st) {
	return NULL;
}
book * BookLink(book *bo) {
	return NULL;
}
void initData(student *st, book *bo) {
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
		while (row = mysql_fetch_row(result))	//���ؽ�������еļ�¼
		{
			/*for (int i = 0; i < numfields; i++)
			{
				cout << row[i] << "---";
			}
			cout << endl;*/
			book *p;
			p = (book *)malloc(sizeof(book));
			strcpy(p->ISBN, row[0]);
			strcpy(p->book_name, row[1]);
			strcpy(p->writer, row[2]);
			strcpy(p->intro, row[3]);
			p->standing_stock = atoi(row[4]);	//���ַ���ת��Ϊint
			p->repertory = atoi(row[5]);
			strcpy(p->remark, row[6]);
			if (!bo)
			{
				bo = p;
			}
			else
			{
				//���½ڵ���뵽��ͷ
				p->next = bo;
				bo = p;
			}
		}
	}
	mysql_free_result(result);	//�ͷ�result�ռ�
	//��ʼ��ѧ����
	sqlstr = "SELECT * FROM book";
	mysql_query(&mysql, sqlstr.c_str());
	result = mysql_store_result(&mysql);		//����ѯ��ȫ�������ȡ���ͻ���
	numfields = mysql_num_fields(result);
	numRows = mysql_num_rows(result);
	if (result) {
		while (row = mysql_fetch_row(result))
		{
			student *q;
			q = (student *)malloc(sizeof(student));
			strcpy(q->student_ID,row[0]);
			strcpy(q->student_name,row[1]);
			strcpy(q->student_sex,row[2]);
			strcpy(q->student_phone,row[3]);
			strcpy(q->department,row[4]);
			strcpy(q->take_effect,row[5]);
			strcpy(q->lose_efficay,row[6]);
			q->Arrearge = atoi(row[7]);		//���ַ���ת��Ϊ����
			q->boorow_sum = atoi(row[8]);
			strcpy(q->remark,row[9]);
		}
	}
	mysql_close(&mysql);
	system("pause");
}
int main() {
	MySql();
	return 0;
}