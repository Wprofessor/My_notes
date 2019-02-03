# c++容器基本使用
## 顺序容器（按顺序存储，插入快，查找慢）：
- ### vector在最后插入数据；
    1.STLvector类与数组类似，允许随机询问元素，即可使用下标运算符[]指定元素在 vector 中的位置(索引)，从而直接访问或操作元素.
    2.将所有元素存储在连续的存储单元中
- ### deque允许在开头插入或删除元素；
- ### list可在任何位置添加或删除元素；
    1.链表的STL实现
    2.不能随机访问
- ### forward_list是单向链表，只能沿一个方向遍历。
## 关联容器（指定顺序存储，插入慢，查找快）：
- ### set:存储各不相同的值，插入时进行排序；
- ### map：存储键值对，根据唯一键排序；
- ### multiset：与set类似，但可以有重复元素。

## 注意：STL容器是泛型模板类，所以是通用的，可用于存储字符串、整型、结构或类对象。

## 1.STL动态数组vector类
* ### 实列化vector
    ```
    //实例化一个存储整型数据的 vector,使用了默认构造函数
    vector<int> vecone;
    //vector 至少应包含10个元素。注意，这并没有限制容器最终的大小，而只是设置了初始大小。
    vector<int> vectwo(10);
    //10个90值
    vector<int> vecthree(10, 90);
    //使用一个 vector 实例化另一个vector 的内容，即复制vector对象或其一部分
    vector<int> vecfour(vecthree);
    ```
* ### push_back()在末尾插入元素
    ```
    vector <int> veclntegers;
    veclntegers.push_back(50);
    veclntegers.push_back(1);
    vecIntegers.push_back(987);
    veclntegers.push_back(1001);
    cout << veclntegers.size()<<endl;
    //也可以像数组一样初始化
    vector<int> veclntegers = {50, 1, 987, 1001};
    vector<int> vecMorelntegers {50, 1, 987, 1001};
    ```
* ### 使用 insert()在指定位置插入元素
    ```
    //在开头插入
    vecone.insert (vecone.begin(), 25);
    ```
    #### 注意：尽量避免频繁使用insert，因为它是低效的，它会导致元素后移，频繁在中间插入应使用list
* ### 数组语法访问vector元素
    ```
    vector<int> vecone(5,10);
    for(int num; num<vecone.size();++num)
    //使用[]访问的时候有越界的危险
    cout<<vecone[num]<endl;
    //at（）函数会检查异常
    cout<<vecone.at(num)<<endl;
    ```
* ###  pop_back删除vector末尾的元素
    ```
    vector<int> vecone(10,90);
    vecone.pop_back();
    ```
## 2.STL动态数组deque：
* ### 与vector非常类似，区别：
 ###  使用 push_front 和 pop_front 在开头插入和删除元素
    ```
    deque<int> deqone;
    deqone.push_back(3);
    deqone.push_back(4);
    deqone.push_back(5);
    //在开头插入
    deqone.push_front(2);
    deqone.push_front(1);
    deqone.push_front(0); // 0,1,2,3,4,5
    deque.pop_back(); // 0,1,2,3,4
    //删除开头元素
    deque.pop_front(); //1,2,3,4
    ```
## 3.STL::list
* ### list是一个双向链表，插入和删除元素速度快，而且时间固定
* ### list的实列化和在末尾，开头插入元素和deque类似
* ### 在list中间插入元素，借助insert函数
    ```
    x.push_back(1);
	x.push_back(2);     //（1，2）
	x.insert(x.begin(),2);      //（2，1，2）
	x.insert(x.begin(),2,3);    //（3，3，2，1，2）
	x.insert(x.begin(),x.begin(),--x.end());    //（3，3，2，1，2，3，3，2，1，2）
    ```
###  注意：insert中的参数是迭代器（类似于指针）
* ### 删除list中元素，借助erase函数
    ```
    //接受一个迭代器参数并删除迭代器指向的元素
    listlntegers.erase(isite)
    //接受两个选代器参数并删除指定范围内的所有元素
    listlntegers.erase(listlntegers.begin() , listlntegers.end());
    ```
* ### 对list元素进行反转
    ```
    x.reverse();
    ```
* ### 对list元素进行排序
    ```
    x.sort();   //默认递增排序
    ```
* ### 对list的遍历访问
    ```
    list<int>x;
	list<int>::iterator it;     //创建迭代器
	x.push_back(1);
	x.push_back(2);
	x.insert(x.begin(),2);
	x.insert(x.begin(),2,3);
	x.insert(x.begin(),x.begin(),--x.end());
	x.reverse();
	for(it = x.begin(); it != x.end(); it++) {
		cout<<*it<<endl;        //循环输出
    ```
## STL集合set(快速的查找和搜索)
* ### 实例化对象(默认升序排序)
    ```
    set<int> seone;
    multiset<int> musone;
    ```
* ### set插入元素
    ```
    setlntegers.insert(1);
    msetlntegers.insert (setlntegers.begin(), setlntegers.end());
    ```
* ### set中查找元素
    ```
    和map类似
    map查找的是key
    set查找的是元素
    ```
* ### 删除set中的元素
    ```
    和map类似
    ```
## STL映射类map（类似于字典）
### key（键）--value（值）

* ### 实例化map对象
    ```
    map<int, string> maptwo;
    map<int, string> mapthree(maptwo);
    map<int, string> mapfour(mapthree.begin(), mapthree.end())
    ```
* ### map插入元素
    1.使用makepair函数
    ```
    mapone.insert(make_pair(1, "one"));
    ```
    2.使用pair
    ```
    mapone.insert(pair<int, string>(2, "two"))
    ```
    3.使用数组语法
    ```
    mapone[3] = "three";
    ```
* ### 查找
    ```
    std::map<char,int> mymap;
    std::map<char,int>::iterator it;

    mymap['a']=50;
    mymap['b']=100;
    mymap['c']=150;
    mymap['d']=200;

    it = mymap.find('b');
    f (it != mymap.end())
    mymap.erase (it); // b被成功删除

    ```
* ### map删除元素
1. 将键作为参数，这将删除包含指定键的所有键-值对:
    ```
    mapObject.erase(key);
    ```
2. 接受迭代器作为参数，并删除选代器指向的元素:
    ```
    mapObject.erase(iElement);
    ```
3. 使用选代器指定边界，从而将指定范围内的所有元素都从 map 或 multirnap 中删除:
    ```
    mapObject.erase(iLowerBound, iUpperBound);
    ```
