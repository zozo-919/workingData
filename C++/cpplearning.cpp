
May::study::learn(){

面向对象程序设计： {
        面向对象程序设计：是一种新的程序设计范型 程序设计范型是指设计程序的规范、模型和风格

        区别：
            面向过程程序设计范型：是使用较为广泛的面向过程性语言
                                其主要特点是： 程序是由 过程定义、过程调用组成 (过程是指程序执行某项操作的一段代码 函数就是最常用的过程)
            面向对象： 程序的基本元素是对象
                      结构特点：程序一般由类的定义和类的使用两部分组成
                               程序中一切操作通过向对象发送消息来实现 对象接收到消息 启动有关方法完成相应操作

        对象：
            描述其属性的数据以及对这些数据施加的一组操作封装在一起构成的统一体 对象可认为是数据+操作
        类：
            类是具有相同的数据和相同的操作的一组对象的集合
        消息传递：
            对象之间的交互
        方法：
            对象实现的行为称为方法

        面向对象程序设计的基本特征：
            抽象： 程序的对象是抽象的，不依赖于具体的实现细节，只关注对象所应具备的功能和属性
            封装： 把数据和显示操作的代码集中起来放在对象内部 尽可能隐藏对象的内部实现细节 信息隐藏
            继承： 允许创建新的类从已有的类继承其属性和方法 使得类之间的关系更加紧密
            多态： 允许不同类的对象对同一消息作出不同的响应 使得程序具有更好的灵活性
    }

    编译器编译过程 :
        编译{
            预编译: 注释删除、宏替换、头文件包含、条件编译等
            编译:   语法检查、符号汇总
            汇编:   符号表生成 (存有符号的名称和其存储在内存中的地址) (若某个符号仅声明未定义则符号表中就会存储一份虚拟地址)
        }
        链接{
            合并段表
            符号表的合并及重定位
        }


    C++基础： {

        #include <iostream>      // 包含iostream头文件
        iostream 库              // 包含两个基础类型: 输入流istream 输出流ostream

/* ----------- practice 1.0 -----------*/
        'cin' : {
            标准输入流  用于从控制台读取输入数据
            输入运算符 '>>'  默认情况下跳过空白符 读入后面与变量类型对应的值(给一组变量赋值时可用空格符 回车符 制表符将输入数据间隔开)
                            输入字符串时 跳过空白符 读入非空白字符 直到另一个空白字符为止 并在串尾放置字符串结束标志 '\0'
            eg:{
                int cinX ;
                cin >> cinX ;   // 读取变量x
            }
        }

        'cout' : {
            标准输出流  用于向控制台输出数据
            输出运算符 '<<'
            eg:{
                cout << "Hello, world!" ; // 输出字符串 "Hello, world!"
            }
        }

        标准错误：
            cerr  用于输出错误信息
        运行时信息：
            clog  用于输出运行时信息

        'endl' : 刷新缓冲区 即换行


        '::' : {
            作用域标识符: 用于区分同名的变量和函数 作用域指的是变量或函数的可访问范围 全局作用域 局部作用域 命名空间作用域
               当全局变量与函数中某个局部变量重名 则可通过'::'来区分
               eg:{
                   int zozoX;  //全局变量
                   int anyfunc() {
                        int zozoX;  //局部变量
                        ::zozoX = ::zozoX * zozoX;  // 其中 '::zozoX' 指代全局变量  'zozoX'指代局部变量
                        return ::zozoX;
                   }
               }

               可通过 '命名空间名称 :: 命名空间成员' 的方式访问命名空间成员
               eg:{
                   std::cout << "Hello, world!" ; // 输出字符串 "Hello, world!"
                   注释： std 命名空间  cout是该命名空间的成员  std::cout 访问该命名空间的cout成员
               }

               假设 A、B 表示两个类 在A、B中都有成员member
               那么可以通过 A::member 和 B::member 访问各自的member

               假设声明了一个类Zozo ,声明了一个成员函数zozoFunc(), 在类中未给出定义 则类外定义时使用 '类名::成员函数名(形参表)'
               eg:{
                    class Zozo {
                        public:
                            int zozoFunc();
                            ...
                    };

                    int Zozo::zozoFunc() //  类名::成员函数名(形参表)
                    {
                        ...
                    }
               }
        }


        'const' 常量限定符：{   修饰常量  const对象必须初始化
               const float PI = 3.14 ; // 此时PI是个常量 不能修改 类似于宏定义 #define PI 3.14
               float const PI = 3.14 ; // 与上例等价

               /* 若想在多个文件之间共享const对象 则需要在定义变量之前加上 extern */
               extern const int buffer = 695;   //定义
               extern const int buffer;         // 外部调用形式

               指向常量的指针：一个指向常量的指针变量  '非const指针 const数据'
               {
                    const char* ptr = "abcd";   //指针变量ptr指向一个常量字符串 'abcd'   const位于*右侧
                    ptr[3] = 'x' ;             // error: 不能修改常量字符串的内容
                    ptr = "efgh";              // 指针是变量 可以改变ptr所指的地址
               }

               常指针：将指针变量所指的地址声明为常量  'const指针 非const数据'
               {
                    char* const ptr1 = "myName";  //指针常量ptr1指向一个字符串 "myName"  const位于*右侧
                    ptr[3] = 'L' ;                // 可以修改ptr1所指的地址的内容
                    ptr = "world!" ;              // error: 不能修改指针ptr1指向的地址
               }

               指向常量的常指针：指针指向的地址及地址中的内容均不可改变 'const指针 const数据'
               {
                    const char* const ptr2 = "you are my hart"; // 指针常量ptr2指向常量字符串  const位于*两边
               }

               总结: '左定值 右定向 const修饰不变量'

               常量一旦建立 任何地方都不能修改
        }

/* ----------- practice 1.1 -----------*/
        'void' :{
                通常表示无值 将void作为指针类型时 表示不确定类型 void型指针是一种通用型指针 任何类型的指针值都可以赋给void类型
                已获值的void型指针 处理时 须进行显示类型转换

                void *pc;
                int i = 123;
                char str = 'a';
                pc = &i;
                cout << pc << endl;          // 输出指针的地址
                cout << *(int*)pc << endl;   // 输出值123
                pc = &str;
                cout << *(char*)pc << endl;  // 输出值a
        }

        'inline' :{
                函数名前冠以 inline 关键字 表明该函数是内联函数 编译器将在调用该函数的地方将其展开 使得程序运行速度更快

                inline int zozoAdd(int zoa, int zob) {
                    return zoa + zob;
                }

                int main() {
                    int zozoRes = zozoAdd(10, 20);
                    return 0;
                }

                注释 ：内联函数以空间换时间 内联函数体内一般不含复杂语句 如for、switch等
                      内联函数不宜冗长且频繁调用  inline函数的定义最好放在头文件中
        }


    带有默认参数的函数：{
            进行函数调用时 编译器从左至右依次将实参与形参结合 若未指定足够实参 则使用默认值
            void init(int x = 10, int y = 9);
            init(100, 20);       //100 , 20
            init(40);           //40 , 9
            init();             //10 , 9

            注释: 带默认值的参数必须从从右至左依次出现
            void init(int x, int y, int z = 100);
            void init(int x, int y = 30, int z = 100);
            void init(int x, int y = 30, int z);   // error!!!!!!!!!!!

            如果函数声明和函数定义分开写 函数声明和函数定义不能同时设置默认参数 建议函数声明时设置参数
            eg:{
                int zozoFunc(int x = 10, int y = 20);
                int main()
                {
                    cout << zozoFunc() << endl;
                    return 0;
                }

                int zozoFunc(int x, int y)
                {
                    return x + y;
                }

            }
    }

    函数重载：{
            同一作用域 函数参数列表(类型or个数or顺序)一个及以上不同 但函数名称相同 称为函数重载

            int add(int a, int b)
            {
                return a+b;
            }
            double add(double a, double b)
            {
                return a+b;
            }
            int add(int a, int b, int c)
            {
                return a+b+c;
            }

            int main() {
                int a=6, b=9, c=5;
                double d=3.14, e=2.71;
                cout << add(a,b) << endl;    // 输出 15
                cout << add(d,e) << endl;    // 输出 5.85
                cout << add(a,b,c) << endl;  // 输出 20
                return 0;
            }

            注释: 只有返回值类型不同的函数 不允许重载
                 若函数重载与带默认值函数同时使用 可能引起二义性
                 若给出实参和形参类型不相符 可能产生不可识别错误
    }

    强制类型转换：{
           int x = 10;
           double y = double(x);  // 强制类型转换 整数转浮点数  或者  double y = (double)x;
    }

/* ----------- practice 1.2 -----------*/
    'new' 和 'delete' :{
        同c语言中的 malloc 和 free 函数  分配和释放堆区内存
        格式 : 指针变量名 = new 类型;
               delete 指针变量名;
                eg:{
                    int *p ;
                    p = new int ;
                    delete p ;
                }

        注释:
            new分配的空间 结束后用delete释放 否则该部分空间变为不可回收的死空间
            使用new分配内存时 不能满足分配要求 则new返回空指针NULL

            new 可为数组动态分配内存及释放 形式如下:
                指针变量名 = new 类型 [下标表达式];
                delete [] 指针变量名;
                eg:{
                    int *p = new int[10];
                    delete [] p;
                }

            new 可在为简单变量分配空间时进行初始化 形式如下:
                指针变量名 = new 类型(初值);
                eg:{
                    int *p;
                    p = new int(99);  // p指向一个值为99的int型变量
                    delete p;
                }
    }

/* ----------- practice 1.3 -----------*/
    引用：{
            变量的引用就是变量的别名 故引用又称别名
            引用与其代表的变量共享一内存单元 系统不为引用另外分配存储空间 引用及其代表的变量具有相同地址
            格式：类型 &引用名 = 已定义变量名;//(类型& 引用名 = 已定义变量名 or 类型 & 引用名 = 已定义变量名)
                  eg:{
                    int x = 10;
                    int &j = x;  // int& j = x;  int & j = x;
                    cout << "j = " << j << endl;
                    cout << "i的地址为 " << &i << endl;
                    cout << "j的地址为 " << &j << endl;
                  }
            注释: 引用非独立数据类型 必须与某一变量联系 且声明时需立即初始化
                  指针通过地址间接访问变量 引用通过别名直接访问变量
                  引用可以被用作函数参数 也可以被用作函数的返回值
                  eg:{
                    void swap(int &a, int &b)  // 引用作为函数参数
                    {
                        int temp = a;
                        a = b;
                        b = temp;
                    }

                    int a[] = {3, 4, 5, 6, 7};

                    int& get_datastr(int i)     // 引用作为函数返回值
                    {
                        return a[i];
                    }
                  }

            不允许建立void类型引用 不能建立引用的数组 不能建立引用的引用 不能建立指向引用的指针
            可以将引用的地址赋值给一个指针 此时指针指向原变量
            可以用const修饰引用 此时不允许通过引用改变变量的值 但不阻止原变量的值被改变
    }

  }

/* ----------- practice 1.4 -----------*/
    类与对象：{
        类的构成：{
            把具有共同属性和行为的事物所构成的集合称为类
            类声明中包含数据和函数 即 数据成员和成员函数
            访问权限分为 public公有、private私有、protected保护 三种
            格式：{
                class 类名{
                    public:
                        公有数据成员;
                        公有成员函数;
                    protected:
                        保护数据成员;
                        保护成员函数;
                    private:
                        私有数据成员;
                        私有成员函数;
                };
            }
            eg:{
                class Score{
                    public:
                        void setScore(int s);
                        void showScore();
                    private:
                        int mid_exam;
                        int fin_exam;
                };
            }
            注释：一般的 一个类的数据成员声明为私有成员 成员函数声明为公有成员
                私有部分处于类的第一部分时 关键字private可以省略
                一个类中没有访问权限关键字 默认为私有
                不能在类声明中给数据成员赋初值

        }

        成员函数定义：{
            普通成员函数的定义 其形式如下：
                返回值类型 类名::成员函数名(参数表) { 函数体 }
            在类的声明中 只给出成员函数的原型 定义在类的外部
            eg:{
                class Score{
                    public:
                        void setScore(int mid, int fin);
                        void showScore();
                    private:
                        int mid_exam;
                        int fin_exam;
                };

                void Score::setScore(int mid, int fin)
                {
                    mid_exam = mid;
                    fin_exam = fin;
                }

                void Score::showScore(void)
                {
                    cout << "mid_exam = " << mid_exam << endl;
                    cout << "fin_exam = " << fin_exam << endl;
                }

                int main()
                {
                    Score s1;
                    s1.setScore(80, 90);
                    s1.showScore();
                    return 0;
                }
            }

            内联成员函数定义：{
                隐式声明 将成员函数直接定义在类内部
                显示声明 在类声明中只给函数原型 定义在类外部
            }

            eg:{
                // 隐式内联成员函数
                class Score{
                    public:
                        int add(int a, int b)
                        {
                            .....
                        }
                    private:
                        ....
                };

                // 显示内联成员函数
                class Student{
                    public:
                        inline int add(int a, int b);
                    private:
                        ...
                };

                inline int Student::add(int a, int b)
                {
                    ...
                }
                注释 :用inline定义的内联函数 声明和定义须在同一文件中 否则编译器无法区分
            }

        }

        对象的定义及使用：{
            声明类的同时 直接定义对象
                eg:{
                    class Score{
                        public:
                            void setScore(int mid, int fin);
                            void showScore();
                        private:
                            int mid_exam;
                            int fin_exam;
                    }op1, op2;      // 定义两个对象op1和op2
                }

            声明类后 定义对象
                eg:{
                    Score s1, s2;   // 定义两个对象s1和s2
                }

            对象中成员的访问 形式如下
                对象名.数据成员名 或 对象名.成员函数名(参数列表)
                eg:{
                    op1.setScore(80, 90);
                    op1.showScore();
                }

            注释:
                类的内部所有成员之间都可通过成员函数直接访问 类的外部 不能访问对象的私有成员

                定义对象时 若是指向此对象的指针变量 则用'->'操作符访问成员对象
                eg:{
                    Score *p ;
                    p->setScore(80, 90);
                }

            类的作用域及类成员的访问属性：{
                私有成员只能被类中成员函数访问 不能在类外部通过类的对象进行访问
                一般来说 公有成员是类的对外接口 私有成员是类的内部数据和内部实现
                类的访问级别优点 信息隐藏 数据保护
            }

        }

/* ----------- practice 1.5 -----------*/
        构造函数与析构函数：{
            构造函数：{
                构造函数是一种特殊的成员函数 主要用于为对象分配空间 进行初始化
                构造函数的名称与类名相同 无返回值 参数类型任意(可不带参数)
                构造函数的调用方式 无需显示调用 系统在创建对象时自动调用 且只执行一次
                eg:{
                    class Score{
                        public:
                            Score(int mid, int fin);   // 构造函数
                            void setScore(int mid, int fin);
                            void showScore();
                        private:
                            int mid_exam;
                            int fin_exam;
                    };

                    Score::Score(int mid, int fin)
                    {
                        mid_exam = mid;
                        fin_exam = fin;
                    }
                }
                建立对象时 采用构造函数给数据成员赋值 形式如下
                类名 对象名(参数表)
                    Score s1(80, 90);
                    s1.showScore();
                类名 *指针变量名 = new 类名(参数表)
                    Score *p = new Score(80, 90);  // 同Score *p; p = new Score(80, 90);
                    p->showScore();
            }

            成员初始化列表：{
                数据成员的初始化一般在构造函数中进行 也可使用成员初始化列表实现数据成员初始化
                格式：
                    类名::构造函数名(参数表): 数据成员名1(初值1), 数据成员名2(初值2), ...
                    {
                        // 构造函数体
                    }

                    eg:{
                        class Animal{
                            private:
                                int age;
                                int& a_age;
                                const double pi;
                            public:
                                Animal(int v):age(v), a_age(age), pi(3.14)
                                {

                                }
                                void show()
                                {
                                    cout << "age = " << age << "a_age =" << a_age << "pi = " << pi << endl;
                                }

                        };
                    }
                    类成员初始化顺序按照声明顺序进行
            }

            带默认参数的构造函数：{
                eg:{
                        class Score{
                            public:
                                Score(int mid = 0, int fin = 0);
                                ...
                            private:
                                int mid_exam;
                                int fin_exam;
                        };
                        Score::Score(int mid, int fin):mid_exam(mid), fin_exam(fin)
                        {
                            cout << "构造函数使用中...." << endl;
                        }
                }
            }

            析构函数：{
                析构函数也是一种特殊的成员函数 执行与构造函数相反的操作
                通常用于撤销对象时一些清理任务 如释放分配给对象的内存空间
                析构函数特点
                            析构函数与构造函数名相同 前面一个'~'
                            析构函数无参数 无返回值 不能重载
                            撤销对象时 系统自动调用析构函数
                eg:{
                    class Score{
                        public:
                            Score(int mid, int fin); // 构造函数
                            ~Score();   // 析构函数
                        private:
                            int mid_exam;
                            int fin_exam;
                    };

                    Score::Score(int mid, int fin) : mid_exam(mid), fin_exam(fin)
                    {
                        cout << "构造函数使用中...." << endl;
                    }

                    Score::~Score()
                    {
                        cout << "析构函数使用中...." << endl;
                    }
                }
            }

            默认的构造函数和析构函数：{
                若未定义构造函数 则系统自动生成一个默认的构造函数
                对未定义构造函数的类 其公有数据成员可用初始值列表进行初始化
                eg:{
                    class Stu{
                        public:
                            char name[10];
                            int no;
                    };

                    Stu s1 = {"张三", 1001};
                    cout << s1.name << " " << s1.no << endl;

                }

                若未定义析构函数 则系统自动生成默认析构函数
            }

            构造函数的重载：{
                class Stu{
                    public:
                        Stu(int n, char *name);
                        Stu();
                        ...
                    private:
                        ...
                };
                注释：无参构造函数和带默认参数的构造函数重载时 可能产生二义性
            }

/* ----------- practice 1.6 ----------- */
            拷贝构造函数：{
                拷贝构造函数是一种特殊的构造函数 其形参是本类对象的引用 用于将一个已有的对象去初始化另一个新的对象
                每个类必须有一个拷贝构造函数 若没有定义 则系统自动生成一个默认的拷贝构造函数 用于复制与数据成员值完全相同的新对象
                格式:
                    类名::类名(const 类名 &对象名)
                    {
                        // 拷贝构造函数体
                    }
                调用拷贝构造的形式如下:
                    类名 对象2(对象1);
                    类名 对象2 = 对象1;
                eg:{
                    class Score{
                        public:
                            Score(int mid, int fin);   // 构造函数
                            Score();
                            Score(const Score &s);   // 拷贝构造函数
                            ~Score();   // 析构函数
                            ...
                        private:
                            int mid_exam;
                            ...
                    };

                    Score::Score(int mid, int fin)
                    {
                        mid_exam = mid;
                        ...
                    }

                    Score::Score(const Score &s)
                    {
                        mid_exam = s.mid_exam;
                        ...
                    }

                    int main()
                    {
                        Score s1(80, 90);
                        Score s2(s1);       // 调用拷贝构造函数
                        Score s3 = sc2;    // 调用拷贝构造函数
                        return 0;
                    }
                }
            }

            深拷贝与浅拷贝：{
                浅拷贝 由默认的拷贝构造函数所实现的数据成员逐一赋值
                若类中含有指针类型数据 则浅拷贝的两个对象将指向同一块内存 那么系统调用析构函数后将导致同一空间多次释放而产生错误
            }

        }

        自引用指针'this': {
            this 指针保存当前对象的地址
            eg:{
                void Sample::copy(Sample &s)
                {
                    if(this == &s)
                        return;

                    *this = s;
                }
            }
        }

        对象数组与对象指针：{
            对象数组:{
                类名 数组名(元素个数);
                eg:{
                    用只有一个参数的构造函数给对象数组赋值
                    Exam ob[4] = {89, 90, 91, 92};
                    用不带参数和一个带参数的构造函数给对象数组赋值
                    Exam ob[4] = {91, 92};
                    用带多个参数的构造函数给对象数组赋值
                    Score ob[3] = {Score{80, 90}, Score{70, 80}, Score{60, 70}};
                }
            }

            对象指针:{
                对象指针就是用于存放对象地址的变量 其形式如下：
                    类名 *对象指针变量名;
                    eg:{
                        Score score;
                        Score *p = &score;
                        p->成员函数名();
                    }
            }

            用对象指针访问对象数组eg:{
                Score score[2];
                score[0].setScore(80, 90);
                score[1].setScore(70, 80);
                Score *p ;
                P = score;
                p->showScore();
                p++;
                p->showScore();
                Score *p1 = &score[1]; // 指向score[1]的指针

            }
        }

/* ----------- practice 1.7 ----------- */
        string 类{
            头文件 #include <string>
            常用string类运算符 : = + += == != > >= < <= [](下标) >> <<
            eg:{
                string s1;              // 默认初始化，s1为空字符串
                string s2(s1);          // s2是s1的副本，等价于 s2 = s1
                string s3("value");     // s3是字面值"value"的副本（除字面值最后那个空字符外），等价于 s3 = "value"
                string s4(n, 'c');      // 把s4初始化为连续n个字符c组成的字符串 等价于string s4 = string(n, 'c')
            }
            注释：使用等号(=)初始化一个变量, 则是拷贝初始化, 反之为直接初始化

            'getline' 读取一行:
                eg:{
                    string s;
                    getline(cin, s);   // 从标准输入读取一行到字符串s中 直到遇到换行符为止
                }

            'empty' 判断字符串是否为空:
                eg:{
                    string s1;
                    if(s1.empty())  // 判断是否为空行
                        cout << "s1 is empty" << endl;
                }

            'size' 获取字符串长度:
                eg:{
                    string s2("I am still stuck in the rain");
                    auto len = s2.size();   // 获取字符串长度  len 的类型是 string::size_type
                }
                注释: 一条表达式中若有了size()函数 则不需要使用int 避免混用int和unsigned

            'ispunct' 判断是否为标点符号:
                eg:{
                    string s3("my hair is still wet");
                    if(ispunct(s3[0]))
                        cout << "s3[0] is a punctuation" << endl;
                }

            'toupper' 转换为大写:
                eg:{
                    string s4("Under mount fuji");
                    toupper(s4[6]);   // 将s4[6]转换为大写
                    toupper(s4);      // 将字符串s4转换为大写
                }

            字符串string与字面值 (字符串字面值与string是不同类型)
                eg:{
                    string s1 = "your trace are still with me";
                    string s2 = "like dust without measure"
                    string s3 = s1 + s2;   // 字符串相加
                    string s4 = s1 + "like dust without measure" // 字符串字面值相加
                    string s5 = "like dust" + "without measure" // error: 字面值不可相加
                }

        }

/* ----------- practice 1.8 ----------- */
        向函数传递对象：{
            对象作为函数参数 (不影响实参本身)
            对象指针作为函数参数 (将影响实参对象的值)
            对象引用作为函数参数 (普遍应用)
        }

/* ----------- practice 1.9 ----------- */
        静态成员：{         关键字 'static'
            静态数据成员:{
                无论建立多少类的对象 都仅有一个静态数据成员的拷贝 所有对象共享同一份静态数据
                需在类外且定义对象前 单独初始化
                形式如下 : static 数据类型 数据成员名;
                访问格式:
                          类名::静态数据成员名;
                          对象名.静态数据成员名;
                          对象指针->静态数据成员名;
            }

            静态成员函数:{
                静态成员函数属于整个类 是该类所有对象共享的成员函数
                静态成员函数的作用： 处理静态数据成员
                静态成员函数限定为内部连接 私有静态成员函数不被类外部函数和对象访问
                形式如下: static 返回值类型 静态成员函数名(参数表);
                访问格式:
                        类名::静态成员函数名(参数表);   //(常用形式)
                         对象名.静态成员函数名(参数表);
                         对象指针->静态成员函数名(参数表);

            }
        }

/* ----------- practice 2.0 ----------- */
        友元：{       关键字 'friend'
                包括友元函数和友元类
                用于对私有或保护成员进行访问
            友元函数:{
                可以是不属于任何类的非成员函数 也可以是另一个类的成员函数 可访问该类的所有成员

                将非成员函数声明为友元函数eg:{
                    class A{
                        public:
                            A(int x);
                            friend int getA(A &a);
                            ...
                        private:
                            int Bb;
                    };

                    int getA(A &a)
                    {
                        return a.Bb;
                    }
                }
            }

            友元类:{
                将一个类声明为另一个类的友元
                class Y{
                    ...
                };
                class X{
                    friend Y;   // 声明Y为X的友元类
                };
            }

            友元关系不具备'交换性'和'传递性'
        }

        类的组合:{
            在一个类中内嵌另一个类的对象作为数据成员 称为类的组合 该内嵌对象称为对象成员 又称子对象
            class A{
                ...
            };
            class B{
                A a;   // 内嵌A对象作为数据成员
                ...
            };
        }

        共享数据的保护:{
            常引用   const 类型& 引用名
            eg:{
                int a = 5;
                const int &b = a;   // 此时b的值就不能被修改了

                int add(const int &m,, const int &n)
                {
                    return m+n;
                }
                //此函数中m和n都是常引用 不能被修改
            }
            常对象:{
                    类名 const 对象名(参数表);
                    const Date date(2021,1,1);

                常对象成员:{
                    常数据成员 使用const修饰
                    若一个类中声明了常数据成员 则构造函数只能通过成员初始化列表来初始化该常数据成员 其他函数不能改变该值
                }

                常成员函数:{
                    形式如下：  类名 函数名(参数表) const;
                    eg:{
                        calss Date{
                            public:
                                Date(int year, int month, int day);
                                int getYear() const;   // 常成员函数
                                ...
                            private:
                                int Dyear;
                                int Dmonth;
                                int Dday;
                        };

                        Date::Date(int year, int month, int day) : Dyear(year), Dmonth(month), Dday(day)
                        { }

                        int Date::getYear() const  // 常成员函数
                        {
                            ...
                        }

                        const可被用于对重载函数区分
                    }
                }

                注释：常成员函数可以访问常数据成员 也可访问普通数据成员
                      常对象只能调用它的常成员函数 不能调用它的普通成员函数 常成员函数是常对象唯一对外的接口
            }
        }
   }

/* ----------- practice 2.1 ----------- */
   继承与派生：{
        继承 即从已有类基础上创建新类 新类可从一个或多个类继承数据成员和成员函数
        可重新定义或添加新的数据 可改变基类成员在派生类中的访问属性
        已有类称为基类或父类 新类称为派生类或子类
        派生类对基类成员的访问:
            内部访问：由派生类中新增的成员函数对基类继承来的成员进行访问
            对象访问：在派生类的外部 通过派生类的对象对基类继承来的成员进行访问
        一般格式：{
            派生类名(参数表) : 基类名(参数表)
            {
                派生类新增数据成员初始化
            }

            含子对象构造函数：
            派生类名(参数总表) : 基类名(参数表0), 子对象1(参数表1), ... , 子对象n(参数表n)
            {
                派生类新增成员初始化
            }
        }

        派生类可声明与基类成员同名的成员 在无虚函数时 若派生类中定义了与基类成员同名的成员
        则派生类成员覆盖基类的同名成员 在派生类中使用该名字代表访问派生类中声明的成员
        若想在派生类中使用与基类同名的成员 须在成员名之前加上 基类名及作用域标识符'::' 即:{
            基类名::函数名(参数表);
            eg:{
                class B : private A{
                    private:
                        int Bb;
                    public:
                        B(int a, int b) : A(a) {
                            Bb = b;
                        }
                        A::show;    // 访问声明
                };
            }
        }

        数据成员也可以使用访问声明
        访问声明中只含不带类型和参数的函数名或变量名
        访问声明不能改变成员在基类中的访问属性
        对于基类的重载函数名 访问声明将对基类中所有同名函数其起作用

        多继承：{
            形式如下：
                class 派生类名 : 继承方式1 基类名1, ... , 继承方式n 基类名n
                {
                    ...
                }
            默认继承方式为private
        }

/* ----------- practice 2.2 ----------- */
        虚基类：{
            一般形式 :
                class 派生类名 : virtual 继承方式 类名{
                ...
                };
        }

        赋值兼容规则：{    '条件派生类从其基类公有派生'
            在任何需要基类对象的地方 都可用子类的对象代替 但只能使用从基类继承来的成员
            假设有如下类：{
                class Base{
                    ...
                };
                class Derived : public Base{
                    ...
                };
            }
            派生类对象可以赋值给基类对象，即用派生类对象中从基类继承来的数据成员，逐个赋值给基类对象的数据成员
            eg:{
                Base b;
                Derived d;
                b = d;
            }
            派生类对象可以初始化基类对象的引用
            eg:{
                Derived d;
                Base &b = d;
            }
            派生类对象的地址可以赋值给指向基类对象的指针
            eg:{
                Derived d;
                Base *p = &d;
            }
        }
   }

/* ----------- practice 2.3 ----------- */
   多态性与虚函数：{   '一个接口，多种方法'
        即不同对象收到相同消息 产生不同动作
        静态连编就是在编译阶段完成的连编 动态连编时运行阶段完成的
        编译时的多态是通过静态连编来实现 运行时的多态是用动态连编实现
        编译时多态性主要是通过函数重载和运算符重载实现  运行时多态性主要是通过虚函数来实现

        虚函数：{
            形式    virtual 返回值类型 函数名(参数表) {
                        函数体
                    }
            在基类中的某个成员函数被声明为虚函数后，此虚函数就可以在一个或多个派生类中被重新定义
            虚函数在派生类中重新定义时 其函数原型 包括返回类型 函数名 参数个数 参数类型的顺序 都必须与基类中的原型完全相同

            若在派生类中 没有用virtual显示给出虚函数说明 则根据以下规则判断 该函数是否为虚函数:
                与基类的虚函数是否有相同的名称 参数个数以及对应的参数类型 返回类型或者满足赋值兼容的指针 引用型的返回类型

            通过定义虚函数来使用多态性机制时 派生类必须从它的基类公有派生
            虚函数必须是其所在类的成员函数 而不能是友元函数 也不能是静态成员函数 因为虚函数调用要靠特定的对象来决定该激活哪个函数
            内联函数不能是虚函数 内联函数是不能在运行中动态确定其位置的
            构造函数不能是虚函数 析构函数可以是虚函数 且通常说明为虚函数

            在一个派生类中重新定义基类的虚函数是函数重载的另一种形式
        }

/* ----------- practice 2.4 ----------- */
        虚析构函数：{
            virtual ~类名() {
                ...
            }

            如果将基类的析构函数定义为虚函数 由该类所派生的所有派生类的析构函数也都自动成为虚函数
        }

        纯虚函数 {
            纯虚函数是在声明虚函数时被'初始化为0的函数' 声明纯虚函数的一般形式如下
                virtual 返回值类型 函数名(参数表) = 0;
            声明为纯虚函数后 基类中就不再给出程序的实现部分 纯虚函数的作用是在基类中为其派生类保留一个函数的名字 以便派生类根据需要重新定义
        }

        抽象类 {
            如果一个类至少有一个纯虚函数 那么就称该类为抽象类

                由于抽象类中至少包含一个没有定义功能的纯虚函数 抽象类只能作为其他类的基类来使用 不能建立抽象类对象
                不允许从具体类派生出抽象类 具体类即 不包含纯虚函数的普通类
                抽象类不能用作函数的参数类型 函数的返回类型 或是显式转换的类型
                可以声明指向抽象类的指针或引用 此指针可以指向它的派生类 进而实现多态性
                如果派生类中没有定义纯虚函数的实现 而派生类中只是继承基类的纯虚函数 则这个派生类仍然是一个抽象类 反之则是可以建立对象的具体类
        }
/* ----------- practice 2.5 ----------- */
实现多态

   }

/* ----------- practice 2.6 ----------- */
   运算符重载：{
        运算符重载 ：对已有的运算符赋予多重含义 使同一个运算符作用于不同类型的数据产生不同的行为
            返回值类型 operator 运算符(参数表)
            {
                ...
            }
        包含被重载的运算符的表达式会被编译成对运算符函数的调用 运算符的操作数成为函数调用时的实参 运算的结果就是函数的返回值 运算符可以被多次重载
        运算符可以被重载为全局函数 也可以被重载为成员函数 一般来说 倾向于将运算符重载为成员函数 这样能够较好地体现运算符和类的关系

        eg:{
            class Person{
                private:
                    int m_age;
                public:
                    Person& operator++();   // 前置递增运算符
                    Person operator++(int); // 后置递增运算符
            };

            Person& Person::operator++(){
                ++m_age;
                return *this;
            }

            Person Person::operator++(int){
                Person temp = *this;
                ++m_age;
                return temp;
            }
        }
(本章待完善:)
   }





/* ----------- practice 2.7 ----------- */
   函数模板与类模板：{      '将类型定义为参数 实现代码重用机制的工具'
       函数模板：{
            建立一个通用函数 其函数返回类型和形参类型不具体指定 用一个虚拟的类型来代表 具体形式如下:{
                template <typename 类型参数>  // 或 template <class 类型参数>
                返回类型 函数名(模板形参表)
                {
                    函数体
                }
            }
            'template' -- 声明模板的关键字  '类型参数' -- 常用T 、type等 使用函数模板时 必须将类型实例化
            类型参数前需加关键字'typename或class' 表示一个虚拟的类型名
/* ----------- practice 2.8 ----------- */

            在函数模板中允许使用多个类型参数 template定义部分的每个类型参数前必须有关键字'typename或class'
            在template语句与函数模板定义语句之间不允许插入别的语句
            函数模板与同名的非模板函数也可以重载
                调用的顺序是：首先寻找一个参数完全匹配的非模板函数 如果找到了就调用它
                            若没有找到 则寻找函数模板 将其实例化 产生一个匹配的模板参数 若找到了 就调用它

       }

       类模板：{
            建立一个通用类 其数据成员 成员函数的返回类型和形参类型不具体指定 用一个虚拟的类型来代表
            使用类模板定义对象时 系统会根据实参的类型来取代类模板中虚拟类型 从而实现不同类的功能
            eg:{
                template <typename T>
                class Classname{
                    private:
                        T data1, data2, data3;
                    public:
                        Classname(T a, T b, T c) : data1(a), data2(b), data3(c) {}
                        T sum()
                        {
                            return data1 + data2 + data3;
                        }
                };
            }

/* ----------- practice 2.9 ----------- err!!!!! */
            上面的例子  成员函数是定义在类体内的 类模板中的成员函数也可以在类模板体外定义 若成员函数中有类型参数存在 则C++有一些特殊的规定：
                需要在成员函数定义之前进行模板声明
                在成员函数名前要加上 '类名<类型参数>::'
            在类模板体外定义的成员函数的一般形式如下:{
                template <typename T>
                函数类型 类名<类型参数>::成员函数名(形参表)
                {
                    函数体
                }
            则上述例子中的sum函数可以改写如下:
                template <typename T>
                T Classname<T>::sum()
                {
                    return data1 + data2 + data3;
                }
            }
       }
   }






   C++的输入和输出：{     '以字节流形式实现'
       优点: 完全支持c语言的输入输出系统 建立面向对象的输入输出系统 比c更安全可靠
            可重载 << >> 运算符 实现用户自定义类型的输入输出 书写形式简单清晰 可读性强

       C++的流库及其基本结构: {
            '流' 指数据从一个源流到一个目的的抽象 从流中提取数据称为输入操作(提取操作) 向流中添加数据称为输出操作(插入操作)
            输入: 字节流从输入设备流向内存   输出: 字节流从内存流向输出设备
            文件和字符串也可以看成有序的字节流 分别称为文件流和字符串流

            常用的输入输出头文件:{
                'iostream' 包含输入/输出流进行操作所需的基本信息
                'fstream'   用于用户管理文件的I/O操作   (针对磁盘文件的操作)
                'strstream' 用于字符串流的I/O操作       (针对内存字符串空间的I/O操作)
                'iomanip'   用于输入/输出的格式控制
            }

            用流定义的对象称为流对象 以下是几个预定义的流对象:
                'cin'  标准输入流对象  从标准输入设备读取数据
                'cout'  标准输出流对象  向标准输出设备输出数据
                'cerr'  标准错误流对象  向标准错误设备输出错误信息
                'clog'  缓冲型标准错误流对象  向缓冲区输出错误信息

            使用istream和类ostream流对象的一些成员函数  实现字符的输出和输入: {
                'put()函数'         cout.put(单字符/字符形变量/ASCII码);
                'get()函数'         cin.get(字符型变量)   get()函数在读入数据时可包括空白符 提取运算符'>>'在默认情况下拒绝接受空白符
                'getline()函数'     cin.getline(字符数组, 字符个数n, 终止标志字符)  cin.getline(字符指针, 字符个数n, 终止标志字符)
                'ignore()函数'      cin.ignore(n, 终止字符)  ignore()函数的功能是跳过输入流中n个字符(默认个数1) 或在遇到指定的终止字符(默认终止字符是EOF)时提前结束

            }

            预定义类型输入/输出的格式控制：{
                流成员函数进行输入/输出格式控制 {
                    'setf()函数'        用于设置流的状态标志 如setf(ios::scientific)
                    'unsetf()函数'      用于清除流的状态标志
                    'width()函数'       用于设置域宽
                    'precision()函数'   用于设置实数的精度
                    'fill()函数'        用于设置填充字符
                }

            }

            使用预定义的操作符进行输入/输出格式控制

/* ----------- practice 3.0 ----------- */
            使用用户自定义的操作符进行输入/输出格式控制 {
                若输出流定义操作符函数 则形式如下
                ostream &操作符名(ostream &stream)
                {
                    自定义代码
                    return stream;
                }

                若为输入流定义操作符函数 形式如下
                istream &操作符名(istream &stream)
                {
                    自定义代码
                    return stream;
                }
            }
       }

/* ----------- practice 3.1 ----------- */
       文件的输入/输出：{   '文件' --存放在外部介质上的数据的集合
            '文件流'  -- 以外存文件为输入/输出对象的数据流  输出文件流是从内存流向外存文件的数据 输入文件流是从外存流向内存的数据
            根据文件中数据的组织形式 文件分为两类: 文本文件和二进制文件
            进行文件操作的一般步骤如下: {
                定义一个流对象 -- 建立文件 -- 进行读写操作 -- 关闭文件
                三个文件流类:
                    istream  -- 输入文件流类
                    ofstream -- 输出文件流类
                    fstream  -- 输入/输出文件流类

                执行文件输入/输出的一般步骤如下：{
                    含头文件fstream
                    建立流对象
                    使用open()函数打开文件
                    进行读写操作
                    使用close()函数关闭文件
                }

            }

            文件打开方式: {
                    ios::in  -- 以读方式打开文件
                    ios::out -- 以写方式打开文件
                    ios::ate -- 打开文件时指针指向文件末尾
                    ios::app -- 以追加方式打开文件
                    ios::trunc -- 若文件已存在 则清空文件内容
                    ios::binary -- 以二进制方式打开文件
            }

/* ----------- practice 3.2 ----------- */
            二进制文件读写
                用read()函数和write()函数读写二进制文件 格式如下:
                    inf.read(char *buf, int len);
                    outf.write(const char* buf, int len );
/* ----------- practice 3.3 ----------- */

            检测文件结束:
                在文件结束的地方有一个标志位 'EOF' 采用文件流方式读取文件时 使用eof()函数 可检测到该结束符
                若该函数返回'非零值' 则到达文件末尾 否则未到文件末尾
                eg:{
                    ifstream ifs;
                    ...
                    if(!ifs.eof()) {
                        cout << "文件未到末尾" << endl;
                    }

                    还有一个检测方法就是检查该流对象是否为零 为零表示文件结束
                    ifstream ifs;
                    ···
                    if (!ifs){
                        cout << "文件结束" << endl;
                    }
                    ···

                    检测文件流对象的某些成员函数的返回值是否为0 为0表示该流到达了末尾
                    while (cin.get(ch))
                        cut.put(ch);
                }

                键盘上输入字符时 其结束符是Ctrl+Z  按下【Ctrl+Z】组合键  eof()函数返回的值为真

                is_open() 函数:
                    用于检测文件流对象是否已打开 若已打开 返回true 否则返回false
                    eg:{
                        ifstream ifs("test.txt");
                        if(ifs.is_open()){
                            cout << "文件已打开" << endl;
                        }
                    }

                fail() 函数:
                    用于检测文件流对象的状态 若文件流对象发生错误(failbit or badbit被置为) 则返回true 否则返回false
                    failbit -- 发生非致命错误 一般为软件错误 可挽回     badbit -- 发生致命错误 一般为硬件或系统底层错误 不可挽回
                    eg:{
                        ifstream ifs("test.txt");
                        if(ifs.fail()){
                            cout << "文件打开失败" << endl;
                        }
                    }

                bad()函数:
                    用于检测文件流对象的状态 若文件流对象发生致命错误(badbit被置为) 则返回true 否则返回false
                    eg:{
                        ifstream ifs("test.txt");
                        if(ifs.bad()){
                            cout << "文件流发生致命错误" << endl;
                        }
                    }

                good()函数:
                    用于检测文件流对象的状态 若文件流对象处于正常状态() 则返回true 否则返回false
                    eg:{
                        ifstream ifs("test.txt");
                        if(ifs.good()){
                            cout << "文件流处于正常状态" << endl;
                        }
                    }

                clear()函数:
                    用于清除文件流对象的状态 若文件流对象发生错误 则调用clear()函数 则文件流对象的状态恢复正常
                    eg:{
                        ifstream ifs("test.txt");
                        if(ifs.fail()){
                            ifs.clear();
                            cout << "文件流发生错误" << endl;
                        }
                    }
       }
   }




/* ----------- practice 3.4 ----------- */
   异常处理与命名空间：{
       异常处理：{
            常见错误: 编译时错误  主要是语法错误
                     运行时错误  统称为异常

            如果在执行一个函数的过程中出现异常 可以不在本函数中立即处理 而是发出一个信息 传给它的上一级处理(即调用函数)
            若上一级函数也不能处理 则逐级上传 若到最高一级仍无法处理 则运行系统将自动调用系统函数'terminate()' 由它调用'abort()'终止程序

            catch(捕获异常) 、throw(抛出异常)、try(异常处理块)
            eg:{
                try{
                    string msg("This is a test exception");
                    throw msg;
                }catch(const string &e){
                    printf("exception = %s",e.c_str());
                }
            }
       }

        命名空间：{
           namespace(命名空间)
           自行命名的内存区域  将各命名空间中声明的标识符与该命名空间标识符建立关联 保证不同命名空间的同名标识符不发生冲突
           eg: {
                namespace myspace{
                    int x = 10;
                }

                int main(){
                    myspace::x = 20;
                    return 0;
                }
           }
        }

        c++使用不带扩展名的头文件： 如 #inlcude <cstring>

   }





   STL标准模板库 {
        STL(Standard Template Library) -- 标准模板库 是一个模板集合 包含了常用的数据结构和算法
/* ----------- practice 3.5 ----------- */
        'vector' 容器:{
            与数组相似 包含一组地址连续的存储单元 可进行查询、插入、删除等操作

            头文件: #include <vector>
            vector<类型> 变量名;
                eg: vector<int> vec;   // 声明一个int类型的vector
                    vector<vector<string>> file;  //该向量的元素是vector对象

            vector对象初始化:
                vector<T> vec1;               // 默认初始化 元素类型为T
                vector<T> vec2(vec1);         // 拷贝初始化 等价于 vec2 = vec1
                vector<T> vec3(n, val);       // 元素个数为n 值均为val 类型为T
                vector<T> vec4(n);            // 元素个数为n 默认值 类型为T
                vector<T> vec5{a,b,c,d,...};  // 初始化多个元素 等价于vec5 = {a,b,c,d,...}

            'push_back()函数' 向vector中添加元素
                eg:{
                    vector<int> vec;
                    vec.push_back(10);  // 向vec中添加元素10
                }
                注释: vector下标可用于访问已存在的元素 但不能用于添加元素 当vector是空时 只能用push_back()添加或访问元素

        }

/* ----------- practice 3.6 ----------- */
        'list' 容器:{
            头文件: #include <list>
            list<类型> 变量名;
                eg: list<int> lst;   // 声明一个元素类型为int的list

        }

/* ----------- practice 3.7 ----------- */
        'stack' :{
            头文件: #include <stack>
            stack<类型> 变量名;
                eg: stack<int> stk;   // 声明一个元素类型为int的stack

        }
/* ----------- practice 3.8 ----------- */
        'queue' :{
            头文件: #include <queue>
            queue<类型> 变量名;
                eg: queue<int> que;   // 声明一个元素类型为int的queue

        }

/* ----------- practice 3.9 ----------- */
        'priority_queue' 优先队列:{
            头文件: #include <queue>
            priority_queue<类型> 变量名;
                eg: priority_queue<int> pq;   // 声明一个元素类型为int的优先队列

        }

        'deque' 双端队列:{

            push_back();
            push_front();
            insert();
            pop_back();
            pop_front();
            erase();
            begin();
            end();
            rbegin();
            rend();
            size();
            maxsize();

        }

/* ----------- practice 4.0 ----------- */
        'set' :{
            头文件: #include <set>
            set<类型> 变量名;
                eg: set<int> st;   // 声明一个元素类型为int的set

        }

/* ----------- practice 4.1 ----------- */
        'map' :{
             头文件: #include <map>
             map<类型1,类型2> 变量名;
                eg: map<string,int> mp;   // 声明一个元素类型为string,值类型为int的map


        }

   }


}



