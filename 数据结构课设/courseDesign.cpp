#include <winsock.h>
#include <iostream>
#include <string.h>
#include<stdlib.h>
#include <mysql.h>
#define MAXSIZE 50
using namespace std;
typedef struct b {			//图书信息表
	char ISBN[20];			//书号
	char book_name[50];		//书名
	char type[30];			//类别
	char writer[15];		//作者
	char intro[200];		//简介
	int standing_stock;		//现存量
	int repertory;			//库存
	char remark[200];		//备注
	struct b *next;
} book;
typedef struct {			//借阅表
	char ISBN[20];			//书号
	char student_ID[20];	//学生学号
	char boorow_time[30];	//借书日期
	char return_time[30];	//还书日期
	char isrenew[10];		//是否续借
	char remark[200];		//备注
}borrowing_table;
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
	teacher te[MAXSIZE];
	int length;
}teacher_sequence;
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
	//ISBN:书号,book_name:书名,class:类别,writer:作者,intro:简介,remark:备注,standing_stock:现存量,repertory:库存
	sqlstr = "create table if not exists book(ISBN VARCHAR(20),";
	sqlstr += "book_name VARCHAR(50)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
	sqlstr += "class VARCHAR(30)CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL,";
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
		"INSERT INTO book VALUES('9787544285147','恶意','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。',2,6,'借阅量大，需加购'),";
	sqlstr += "('9787544285148','恶意','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。',2,6,'借阅量大，需加购'),";
	sqlstr += "('9787544285149','恶意','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。',2,6,'借阅量大，需加购'),";
	sqlstr += "('9787544285150','恶意','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。',2,6,'借阅量大，需加购'),";
	sqlstr += "('9787544285151','恶意','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。',2,6,'借阅量大，需加购'),";
	sqlstr += "('9787544285152','恶意','文学','东野圭吾','《恶意》深刻揭示人性，故事中无边的恶意深不见底，有如万丈深渊，让人不寒而栗。从未遇到这样的案子：杀人不是目的，而是手段；死亡不是结束，而是开始。',2,6,'借阅量大，需加购'),";
	sqlstr += "('9787020024759','围城','文学','钱钟书','《围城》是中国现代文学史上一部风格独特的讽刺小说，被誉为“新儒林外史”。故事主要写抗战初期知识分子的群相。',4,5,'无'),";
	sqlstr += "('9787020024760','围城','文学','钱钟书','《围城》是中国现代文学史上一部风格独特的讽刺小说，被誉为“新儒林外史”。故事主要写抗战初期知识分子的群相。',4,5,'无'),";
	sqlstr += "('9787020024761','围城','文学','钱钟书','《围城》是中国现代文学史上一部风格独特的讽刺小说，被誉为“新儒林外史”。故事主要写抗战初期知识分子的群相。',4,5,'无'),";
	sqlstr += "('9787020024762','围城','文学','钱钟书','《围城》是中国现代文学史上一部风格独特的讽刺小说，被誉为“新儒林外史”。故事主要写抗战初期知识分子的群相。',4,5,'无'),";
	sqlstr += "('9787020024763','围城','文学','钱钟书','《围城》是中国现代文学史上一部风格独特的讽刺小说，被誉为“新儒林外史”。故事主要写抗战初期知识分子的群相。',4,5,'无'),";
	sqlstr += "('9787020049295','平凡的世界','文学','路遥','《平凡的世界》是一部现实主义小说，也是一部小说形式的家族史。作者浓缩料中国西北农村的历史变迁过程，在小说中全景式地表现了中国当代城乡的社会生活。在近十年的广阔背景下，通过复杂的矛盾纠葛，刻划社会格阶层众多普通人的形象',0,3,'一本严重损坏，需丢弃'),";
	sqlstr += "('9787020049296','平凡的世界','文学','路遥','《平凡的世界》是一部现实主义小说，也是一部小说形式的家族史。作者浓缩料中国西北农村的历史变迁过程，在小说中全景式地表现了中国当代城乡的社会生活。在近十年的广阔背景下，通过复杂的矛盾纠葛，刻划社会格阶层众多普通人的形象',0,3,'一本严重损坏，需丢弃'),";
	sqlstr += "('9787020049297','平凡的世界','文学','路遥','《平凡的世界》是一部现实主义小说，也是一部小说形式的家族史。作者浓缩料中国西北农村的历史变迁过程，在小说中全景式地表现了中国当代城乡的社会生活。在近十年的广阔背景下，通过复杂的矛盾纠葛，刻划社会格阶层众多普通人的形象',0,3,'一本严重损坏，需丢弃'),";
	sqlstr += "('9787020026906','白鹿原','文学','陈忠实','这是一部渭河平原五十年变迁的雄奇史诗，一轴中国农村斑斓多彩、触目惊心的长幅画卷。主人公六娶六丧，神秘的序曲暗示着不祥。一个家族两代子孙，为争夺白鹿原的统治代代斗争不已，上演了一幕幕惊心动魄的活剧。',2,3,'无'),";
	sqlstr += "('9787020026907','白鹿原','文学','陈忠实','这是一部渭河平原五十年变迁的雄奇史诗，一轴中国农村斑斓多彩、触目惊心的长幅画卷。主人公六娶六丧，神秘的序曲暗示着不祥。一个家族两代子孙，为争夺白鹿原的统治代代斗争不已，上演了一幕幕惊心动魄的活剧。',2,3,'无'),";
	sqlstr += "('9787020026908','白鹿原','文学','陈忠实','这是一部渭河平原五十年变迁的雄奇史诗，一轴中国农村斑斓多彩、触目惊心的长幅画卷。主人公六娶六丧，神秘的序曲暗示着不祥。一个家族两代子孙，为争夺白鹿原的统治代代斗争不已，上演了一幕幕惊心动魄的活剧。',2,3,'无'),";
	sqlstr += "('9787549529322','看见','历史','柴静','《看见》是著名记者和主持人柴静讲述央视十年历程的自传性作品，既是柴静个人的成长告白书，某种程度上亦可以视作中国十年变迁的备忘录',3,5,'无'),";
	sqlstr += "('9787549529323','看见','历史','柴静','《看见》是著名记者和主持人柴静讲述央视十年历程的自传性作品，既是柴静个人的成长告白书，某种程度上亦可以视作中国十年变迁的备忘录',3,5,'无'),";
	sqlstr += "('9787549529324','看见','历史','柴静','《看见》是著名记者和主持人柴静讲述央视十年历程的自传性作品，既是柴静个人的成长告白书，某种程度上亦可以视作中国十年变迁的备忘录',3,5,'无'),";
	sqlstr += "('9787549529325','看见','历史','柴静','《看见》是著名记者和主持人柴静讲述央视十年历程的自传性作品，既是柴静个人的成长告白书，某种程度上亦可以视作中国十年变迁的备忘录',3,5,'无'),";
	sqlstr += "('9787549529326','看见','历史','柴静','《看见》是著名记者和主持人柴静讲述央视十年历程的自传性作品，既是柴静个人的成长告白书，某种程度上亦可以视作中国十年变迁的备忘录',3,5,'无'),";
	sqlstr += "('9787508645056','你的孤独，虽败犹荣','爱情','刘同','孤独之所以迷茫，孤独之后是成长。这本书里记录了33种孤独感，希望能让你想起自己某种忘我无形的成长。最后。愿你比别人更不怕一个人独处，愿日后想起时你会被自己感动。',3,3,'无'),";
	sqlstr += "('9787508645057','你的孤独，虽败犹荣','爱情','刘同','孤独之所以迷茫，孤独之后是成长。这本书里记录了33种孤独感，希望能让你想起自己某种忘我无形的成长。最后。愿你比别人更不怕一个人独处，愿日后想起时你会被自己感动。',3,3,'无'),";
	sqlstr += "('9787508645058','你的孤独，虽败犹荣','爱情','刘同','孤独之所以迷茫，孤独之后是成长。这本书里记录了33种孤独感，希望能让你想起自己某种忘我无形的成长。最后。愿你比别人更不怕一个人独处，愿日后想起时你会被自己感动。',3,3,'无')";
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
	sqlstr += "('1410024336','王媛','女','13466992580','英语','20150901','20180701',0,2,'学生信息过期，需注销'),";
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
void initData(book **bo, student **st, teacher_sequence *t) {
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
		while (row = mysql_fetch_row(result))	//返回结果集中行的记录
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
			strcpy_s(p->ISBN,strlen(row[0])+1, row[0]);
			strcpy_s(p->book_name,strlen(row[1])+1, row[1]);
			strcpy_s(p->type, strlen(row[2]) + 1, row[2]);
			strcpy_s(p->writer, strlen(row[3]) + 1, row[3]);
			strcpy_s(p->intro, strlen(row[4]) + 1, row[4]);
			p->standing_stock = atoi(row[5]);	//将字符串转换为int
			p->repertory = atoi(row[6]);
			strcpy_s(p->remark, strlen(row[7]) + 1, row[7]);
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
			strcpy_s(q->student_name,strlen(row[1])+1, row[1]);
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
//输出图书信息表
void displaybook(book *bo)
{
	book *p;
	p = bo;
	while (p) 
	{
		cout << p->ISBN << "---" << p->book_name << "---" << p->type << "---" << p->writer << endl;
		cout << p->intro << endl;
		p = p->next;
	}
}
//输出学生信息
void displaystudent(student  *st) {
	student *p;
	p = st;
	while (p)
	{
		cout << p->student_ID << "---" << p->student_name << "---" << p->student_sex << "---" << p->student_phone << "---" << p->department << endl;
		p = p->next;
	}
}
//根据学号查看借阅信息
void SeeBorrow(student *st,char id[]) {
	student * p;
	int i;
	p = st;
	while (p)
	{
		if (strcmp(p->student_ID,id) == 0)
		{
			
			for ( i = 0; i < p->length; i++)
			{
				cout << p->borrow[i].ISBN << "---" << p->borrow->boorow_time << "---" << p->borrow->return_time << endl;
			}
		}
		p = p->next;
	}
}
int main() {
	book *bo;
	teacher_sequence t;
	student *st;
	st = StudentLink();
	bo = BookLink();
	 initData(&bo, &st, &t);
	cout << "图书信息表" << endl;
	//displaybook(bo);
	//displaystudent(st);
	char id[] = "1509024219";
	SeeBorrow(st, id);
	system("pause");
	return 0;
}