#include <iostream>  // for input/output operations


/* ------------------------------------------ pratice 0.0 ---------------------------------------- */
#if 0

using namespace std;

int main()
{

    return 0;
}
#endif



/* ------------------------------------------ pratice 1.0 ---------------------------------------- */
#if 0

// using namespace std;

int main()
{
    int zozoX , zozoY;
    int zozoSum = 0;

    std::cout << "please enter the value of zozoX and zozoY: " << std::endl;
    std::cin >> zozoX >> zozoY ;
    std ::cout << std::endl;
    zozoSum = zozoX + zozoY;
    std::cout << "The sum of zozoX and zozoY is: " << zozoSum << std::endl;

    int zozoR = 15;
    const float zozoPI = 3.14;
    // zozoPI = 3.14159;       // error: assignment of read-only variable 'zozoPI'
    float zozoArea = zozoPI * zozoR * zozoR;
    std::cout << "The area of zozoCircle is: " << zozoArea << std::endl;

    char zozoStr[5] = "zozo";
    const char *zozoName = zozoStr;     // 指向常量字符串的指针变量
    // zozoName[3] = 'L';       // error: assignment of read-only location 'zozo'
    zozoName = "Tom";
    std::cout << "The myname is: " << zozoName << std::endl;
    std::cout << "The address of myname is: " << &zozoName << std::endl;
    std::cout << "The address of zozoStr is: " << &zozoStr << std::endl;

    int* const zozoNewPtr = &zozoR; // 指向变量的指针常量
    *zozoNewPtr = 100;
    // zozoNewPtr = &zozoSum;  // error: assignment of read-only variable 'zozoNewPtr'
    std::cout << "The value of zozoR is: " << *zozoNewPtr << std::endl;
    std::cout << "The address of zozoR is: " << zozoNewPtr << std::endl;

    const int *const zozoPtr = &zozoSum; // 指向常量的常指针
    // *zozoPtr = 100;       // error: assignment of read-only variable 'zozoPtr'
    // zozoPtr = &zozoX;  // error: assignment of read-only variable 'zozoPtr'
    std::cout << "The value of zozoSum is: " << *zozoPtr << std::endl;
    std::cout << "The address of zozoSum is: " << zozoPtr << std::endl;


    return 0;
}
#endif


/* ------------------------------------------ pratice 1.1 -------------------------------------- */
#if 0

using namespace std;   // 声明命名空间

inline int add(int a, int b);  //内联函数

int main()
{
    int zozoI = 10;
    char zozoC = 'a';
    void *zozoPtr = nullptr;    // void型指针 即通用指针
    zozoPtr = &zozoI;           // 已获值指针
    cout << "The value of zozoI is: " << *(int*)zozoPtr << endl;  // 进行显示类型转换
    zozoPtr = &zozoC;
    cout << "The value of zozoC is: " << *(char*)zozoPtr << endl; // 进行显示类型转换
    cout << "The address of zozoPtr is: " << zozoPtr << endl;
    cout << "The address of zozoC is: " << &zozoC << endl;


    char zozoBuf[10] ="hello";
    char *zozoBufPtr = zozoBuf;

    cout << "address of zozoBuf: " << &zozoBuf << endl;        // 输出 0x7ffffb542a1e 地址
    cout << "address of zozoBuf: " << (int*)zozoBuf << endl;    // 输出 0x7ffffb542a1e 地址
    cout << "zozoBuf: " << zozoBuf << endl;           // 输出 hello 即数组buffer的内容

    cout << "zozoPtr: " << zozoBufPtr << endl;      // 输出 hello 即数组buffer的内容
    cout << "address of zozoPtr: " << (int*)zozoBufPtr << endl;  // 输出 0x7ffffb542a1e 地址 即zozoBuf的地址
    cout << "address of zozoPtr: " << &zozoBufPtr << endl;        // 输出zozoBufPtr本身的地址 即指针的地址 与数组地址不同


    int zozoX,  zozoY;
    cout << "Enter two numbers for zozoX and zozoY: " << endl;
    cin >> zozoX ;
    cin >> zozoY ;
    int zozoSum = add(zozoX, zozoY);  // 调用内联函数
    cout << "The zozoSum is: " << zozoSum << endl;


    double IntX = 10.99;
    int DoubleY = (int)IntX;
    cout << "The value of DoubleY is: " << DoubleY << endl;

    return 0;
}

inline int add(int a, int b)
{
    return a + b;
}

#endif


/* ------------------------------------------ pratice 1.2 -------------------------------------- */

#if 0

using namespace std;

int main()
{
    int *p;

    p = new int;    // 为指针分配内存
    cout << "The 1st value of p is: " << *p << endl;
    delete p;

    p = new int(695);    // 为指针分配内存 并设置初值
    cout << "The 2nd value of p is: " << *p << endl;
    delete p;

    p = new int[5];    // 为指针数组分配内存 该数组有5个元素
    p[2] = 69;
    cout << "The value of p[2] is: " << p[2] << endl;
    delete[] p;

    int x = 42;
    int &r = x;    // 引用变量
    cout << "The value of x is: " << x << endl;
    cout << "the value of r is :" << r << endl;
    cout << "The address of x is: " << &x << endl;
    cout << "the address or r is: " << &r << endl;

    return 0;
}

#endif


/* ------------------------------------------ pratice 1.3 -------------------------------------- */
#if 0
using namespace std;

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

int main()
{
    int a1 = 12 , b1 = 11;
    swap(a1, b1);
    cout << "a1 = " << a1 << "b1 = " << b1 << endl;

    int testIndex = 2;
    cout << "The value of a[" << testIndex << "] is: " << get_datastr(testIndex) << endl;
    get_datastr(testIndex) = 100;
    cout << "changed The value of a[" << testIndex << "] is: " << get_datastr(testIndex) << endl;

    int num = 10;
    int &renum = num;
    int *pointer ;
    pointer = &renum;
    cout << "The value of num is: " << num << endl;
    cout << "The value of renum is: " << renum << endl;
    cout << "the address of num is: " << &num << endl;
    cout << "the address of renum is: " << &renum << endl;
    cout << "the address of pointer is: " << pointer << endl;

    const int& renum2 = num;
    cout << "The value of renum2 is: " << renum2 << endl;
    // renum2 = 20;        // error: assignment of read-only variable 'renum2'
    num = 30;
    cout << "The value of num is: " << num << endl;
    cout << "The value of renum2 is: " << renum2 << endl;


    return 0;
}

#endif


/* ------------------------------------------ pratice 1.4 -------------------------------------- */
#if 0
using namespace std;

class Score{
    public:
        void setScore(int m, int f);
        void showScore(void);
    private:
        int mid_exam;
        int fin_exam;
};

void Score::setScore(int m, int f)
{
    mid_exam = m;
    fin_exam = f;
}
void Score::showScore(void)
{
    cout << "The mid_exam score is: " << mid_exam << endl;
    cout << "The fin_exam score is: " << fin_exam << endl;
}

int main()
{
    int mid_score = 80, fin_score = 90;
    Score s1;
    s1.setScore(mid_score, fin_score);
    s1.showScore();

    return 0;
}
#endif


/* ------------------------------------------ pratice 1.5 -------------------------------------- */
#if 0

#include <cstring>

using namespace std;

class Student{
private:
    char *stu_name;
    char *stu_no;
    float stu_score;
public:
    Student(char *name1, char *no1, float score1);
    ~Student();
    void modify(float score2);
    void stuShow();

};

Student::Student(char *name1, char *no1, float score1)
{
    stu_name = new char[strlen(name1)+1];
    strcpy(stu_name, name1);
    stu_no = new char[strlen(no1)+1];
    strcpy(stu_no, no1);
    stu_score = score1;
}

Student::~Student()
{
    delete []stu_name;
    delete []stu_no;
}

void Student::modify(float score2)
{
    stu_score = score2;
}

void Student::stuShow()
{
    cout << "The name of student is: " << stu_name << endl;
    cout << "The number of student is: " << stu_no << endl;
    cout << "The score of student is: " << stu_score << endl;
}


int main()
{
    Student stu1("Tom", "2019001", 95.5);
    // stu1.stuShow();
    stu1.modify(100);
    stu1.stuShow();

    return 0;
}
#endif


/* ------------------------------------------ pratice 1.6 -------------------------------------- */
#if 0
#include <cstring>

using namespace std;

class Stu{
    public:
        Stu(char *stu_name, int stu_age);
        ~Stu();
        Stu(const Stu& s);
        void show_stu(void);
    private:
        char *name;
        int age;
};

Stu::Stu(char *stu_name, int stu_age)
{
    name = new char[strlen(stu_name)+1];
    strcpy(name, stu_name);
    age = stu_age;
}

Stu::~Stu()
{
    delete []name;
}

Stu::Stu(const Stu& s)
{
    name = new char[strlen(s.name)+1];
    strcpy(name, s.name);
    age = s.age;
}

void Stu::show_stu(void)
{
    cout << "The name of student is: " << name << endl;
    cout << "The age of student is: " << age << endl;
}

int main()
{
    Stu s1("Tom", 18);
    // s1.show_stu();
    Stu s2(s1);
    s2.show_stu();
    // s2.age = 19;         // error: age is a private member of class Stu

    return 0;
}
#endif


/* ------------------------------------------ pratice 1.7 -------------------------------------- */
#if 0
#include <string>
using namespace std;

int main()
{
    string str1 = "hello myself";
    string str2("my name is zozo");
    string str3 = str1 + " " + str2;
    cout << " " << str3 << endl;
    str2 += str2;
    str3 += " off";
    cout << " " << str2 << endl;
    cout << " " << str3 << endl;

    cout << "str == str1 ? " << (str1 == str2) << endl;
    cout << "str!= str1 ? " << (str1!= str2) << endl;
    cout << "str < str1  ? " << (str1 < str2) << endl;
    cout << "str > str1  ? " << (str1 > str2) << endl;

    return 0;
}
#endif


/* ------------------------------------------ pratice 1.8 ---------------------------------------- */
#if 0
using namespace std;

class Point{
    public:
        int x;
        int y;
        Point(int x1, int y1):x(x1), y(y1)
        {}
        int distance()
        {
            return x*x + y*y;
        }
};

void print_distance(Point p1)   // 使用对象作为函数参数
{
    p1.x += 1;
    p1.y -= 1;
}

void change_point1(Point *p)     // 使用对象指针作为函数参数
{
    p->x += 1;
    p->y -= 1;
}

void change_point(Point& p)     // 使用引用作为函数参数
{
    p.x += 1;
    p.y -= 1;
}

int main()
{
    Point point[3] = {Point(1, 2), Point(3, 4), Point(5, 6)};
    Point *p = point;
    print_distance(*p);
    cout << "The distance of point1 is: " << p[0].distance() << endl;
    p++;
    change_point1(p);
    cout << "The distance of point2 is: " << p->distance() << endl;
    change_point(point[2]);
    cout << "The distance of point3 is: " << point[2].distance() << endl;

    return 0;
}
#endif


/* ------------------------------------------ pratice 1.9 ---------------------------------------- */
#if 0
using namespace std;

class Score{
    private:
        int mid_exam;
        int fin_exam;
        static int count;
        static float sum;
        static float ave;   // 静态成员变量
    public:
        Score(int m, int f);
        ~Score();
        static void show_count_sum_ave();   // 静态成员函数
};

Score::Score(int m, int f)
{
    mid_exam = m;
    fin_exam = f;
    count++;
    sum += fin_exam;
    ave = sum / count;
}

Score::~Score()
{

}

/* 静态成员初始化 */
int Score::count = 0;
float Score::sum = 0;
float Score::ave = 0;

void Score::show_count_sum_ave()
{
    cout << "The count of scores is: " << count << endl;
    cout << "The sum of scores is: " << sum << endl;
    cout << "The average of scores is: " << ave << endl;
}

int main()
{
    Score sco[3] = {Score(80, 90), Score(70, 80), Score(90, 95)};
    sco[1].show_count_sum_ave();
    Score::show_count_sum_ave();

    return 0;
}
#endif


/* ------------------------------------------ pratice 2.0 ---------------------------------------- */
#if 0
#include <string>

using namespace std;

class Score;   // 提前声明Score类以便引用

class Student{
    private:
        string name;
        int number;
    public:
        Student(string na, int num)
        {
            name = na;
            number = num;
        }
        friend void show_score(Score &sc, Student &st);   // 声明show_score为友元函数
};

class Score{
    private:
        int mid_exam;
        int fin_exam;
    public:
        Score(int m, int f)
        {
            mid_exam = m;
            fin_exam = f;
        }
        friend void show_score(Score &sc, Student &st);   // 声明show_score为友元函数
};

void show_score(Score &sc, Student &st)
{
    cout << "The name of student is: " << st.name << "student number is: " << st.number << endl;
    cout << "The mid_exam score is: " << sc.mid_exam << " fin_exam score is: " << sc.fin_exam << endl;
}

int main()
{
    Score sco1(80, 90);
    Student st("Tom", 20101);
    show_score(sco1, st);

    return 0;
}
#endif


/* ------------------------------------------ pratice 2.1 ---------------------------------------- */
#if 0

using namespace std;

class Person{
    private:
        string name;
        int age;
        int number;
    public:
        Person(string na, int ag, int num) {
            name = na;
            age = ag;
            number = num;
        }

        ~Person() {
        }

        void show_person(void) {
            cout << "name is: " << name << " age is: " << age << " number is: " << number << endl;
        }
};

class Student: public Person{
    private:
        string major;
    public:
        Student(string na, int ag, int num, string maj) : Person(na, ag, num) {
            major = maj;
        }

        ~Student() {
        }

        void show_student(void) {
            Person::show_person();
            cout << " major is: " << major << endl;
        }
};

int main()
{
    Student stu("Tom", 18, 2019001, "Computer Science");
    stu.show_student();

    return 0;
}
#endif

/* ------------------------------------------ pratice 2.2 ---------------------------------------- */
#if 0

using namespace std;

class Base{
    protected:
        int a;
    public:
        Base() {
            a = 5;
            cout << "Base = " << a << endl;
        }
};

class Base1: virtual public Base{
    public:
        Base1() {
            a += 5;
            cout << "Base1 = " << a << endl;

        }
};

class Base2: virtual public Base{
    public:
        Base2() {
            a += 20;
            cout << "Base2 = " << a << endl;
        }
};

class Derived: public Base1, public Base2{
    public:
        Derived() {
            cout << "the Base1 = " << Base1::a << endl;
            cout << "the Base2 = " << Base2::a << endl;
        }
};

int main()
{
    Derived objd;

    return 0;
}
#endif


/* ------------------------------------------ pratice 2.3 ---------------------------------------- */
#if 0

#include <string>
using namespace std;

class Family{
    private:
        string flower;
    public:
        Family(string name = "flowers") : flower(name) {
        }
        string get_flower(void) {
            return flower;
        }

        virtual void like_flower(void) {
            cout << "they like different flowers" << endl;
        }
};

class Child: public Family{
    public:
        Child(string name = "camellia"): Family(name) {
        }
        void like_flower(void) {
            cout << " she likes " << get_flower() << endl;
        }
};

class Parent: public Family{
    public:
        Parent(string name = "rose"): Family(name) {
        }
        void like_flower(void) {
            cout << " he likes  " << get_flower() << endl;
        }
};

int main()
{
    Family *F;
    Family y;
    Child c;
    Parent p1;
    F = &y;
    F->like_flower();
    F = &c;
    F->like_flower();
    F = &p1;
    F->like_flower();

    return 0;
}
#endif


/* ------------------------------------------ pratice 2.4 ---------------------------------------- */
#if 0
#include <string>

using namespace std;

class Base{
    public:
        // ~Base() {         //此时系统仅调用基类的析构函数
        virtual ~Base() {
            cout << "调用基类Base的析构函数" << endl;
        }
};

class Derived: public Base{
    public:
        ~Derived() {
            cout << "调用派生类Derived的析构函数" << endl;
        }
};


int main()
{
    Base *p;
    p = new Derived();
    delete p;

    return 0;
}
#endif


/* ------------------------------------------ pratice 2.5 ---------------------------------------- */
#if 0

using namespace std;

class Figure{
    protected:
        double zozoX, zozoY;
    public:
        Figure(double x, double y) : zozoX(x), zozoY(y) {}
        virtual void getArea() // 基类Figure的虚函数
        {
            cout << "no area for this class" << endl;
        }
};

class Triangle: public Figure{
    public:
        Triangle(double x, double y) : Figure(x, y) {}
        void getArea()  // 重写基类Figure的虚函数
        {
            cout << "area of triangle is: " << 0.5 * zozoX * zozoY << endl;
        }
};

class Square: public Figure{
    public:
        Square(double x, double y) : Figure(x, y) {}
        void getArea()  // 重写基类Figure的虚函数
        {
            cout << "area of square is: " << zozoX * zozoY << endl;
        }
};

class Circle: public Figure{
    public:
        Circle(double x, double y) : Figure(x, y) {}
        void getArea()  // 重写基类Figure的虚函数
        {
            cout << "area of circle is: " << 3.14 * zozoX * zozoX << endl;
        }
};

int main()
{
    Figure *f;
    Triangle t(3, 4);
    Square s(5, 5);
    Circle c(6, 6);

    f = &t;
    f->getArea();
    f = &s;
    f->getArea();
    f = &c;
    f->getArea();

    return 0;
}
#endif


/* ------------------------------------------ pratice 2.6 ---------------------------------------- */
#if 0

using namespace std;

class Complex{
    private:
        double real, imag;

    public:
        Complex(double r = 0, double i = 0) : real(r), imag(i) {}
        friend Complex operator+(const Complex& c, const Complex& d) {
            Complex temp;
            temp.real = c.real + d.real;
            temp.imag = c.imag + d.imag;
            return temp;
        }
        void show() {
            cout << real << endl;
            cout << imag << endl;
        }
};

int main()
{
    Complex c1(2, 3), c2(4, 5), c3;
    c1.show();
    c2.show();
    c3 = c1 + c2;
    c3.show();
    c3 = operator+(c1, c2);
    c3.show();

    return 0;
}
#endif

/* ------------------------------------------ pratice 2.7 ---------------------------------------- */
#if 0

using namespace std;

template <typename T>
T Max(T *arry, int numb = 0)
{
    T max = arry[0];
    for(int i = 1; i < numb; i++)
    {
        if(arry[i] > max)
        {
            max = arry[i];
        }
    }
    return max;
}

int main()
{
    int arry[] = {1, 2, 9, 4, 5};
    cout << "The max number is: " << Max(arry, 5) << endl;
    double arry1[] = {1.1, 4.2, 3.3};
    cout << "The max number is: " << Max(arry1, 3) << endl;

    return 0;
}
#endif


/* ------------------------------------------ pratice 2.8 ---------------------------------------- */
#if 0

using namespace std;

template <class T>
T Max(T a, T b)
{
    return (a > b)? a : b;
}

template <class T>
T MAX(T a, T b, T c)
{
    T max = a > b? a : b;
    max = max > c? max : c;
    return max;
}

int main()
{
    cout << "The two number max is: " << Max(3, 5) << endl;
    cout << "The three number max is: " << MAX(9, 5, 7) << endl;

    return 0;
}
#endif

/* ------------------------------------------ pratice 2.9 ---------------------------------------- */
/* err!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
#if 0
#include <string>

using namespace std;

const int size = 10;
template <class T>
class Stack{
    private:
        T stackBuffer[10];
        int top;
    public:
        void init() {
            int top = 0;
        }
        void push(T data);
        T pop();
};

template <class T>
void Stack<T>::push(T data)
{
    if(top == 9) {
        cout << "Stack is full" << endl;
        return;
    }
    stackBuffer[top++] = data;
}

template <class T>
T Stack<T>::pop()
{
    if(top == 0) {
        cout << "Stack is empty" << endl;
        return 0;
    }

    return stackBuffer[top--];
}

int main()
{
    Stack<string> s;
    s.init();
    s.push("hello");
    s.push("world");
    cout << s.pop() << endl;
    cout << s.pop() << endl;

    return 0;
}
#endif
/* err!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */



/* ------------------------------------------ pratice 3.0 ---------------------------------------- */
#if 0
#include <iomanip>

using namespace std;

ostream &output(ostream &stream)
{
    stream.setf(ios::left);    //设置输出左对齐
    stream << setw(10) << hex << setfill('-');  //将输出 设置域宽为10 十六进制 填充字符为-
    return stream;
}

int main()
{
    cout << 123 << endl;
    cout << output << 123 << endl;

    return 0;
}
#endif


/* ------------------------------------------ pratice 3.1 ---------------------------------------- */

#if 0
#include <fstream>

using namespace std;

int main()
{
    ofstream fout("./test.txt", ios::out);
    if (!fout) {
        cout << "Cannot open output file." << endl;
        exit(1);
    }
    fout << "I am a student.";
    fout.close();

    ifstream fin("./test.txt", ios::in);
    if (!fin) {
        cout << "Cannot open input file." << endl;
        exit(1);
    }
    char str[80];
    fin.getline(str, 80);
    cout << str << endl;
    fin.close();

    return 0;
}
#endif


/* ------------------------------------------ pratice 3.2 ---------------------------------------- */
#if 0
#include <fstream>

using namespace std;
int cput()
{
    ofstream outf("test.txt", ios::out);
    if(!outf) {
        cout << "Cannot open output file." << endl;
        exit(1);
    }

    char ch = 'a';
    for(int i = 0; i< 26; i++) {
        outf.put(ch);
        ch++;
    }

    outf.close();
    return 0;
}

int cget()
{
    ifstream inf("test.txt", ios::in);
    if(!inf) {
        cout << "Cannot open input file." << endl;
        exit(1);
    }

    char ch;
    while(inf.get(ch)) {
        cout << ch << ' ';
    }
    cout << endl;

    inf.close();
    return 0;
}

int main()
{
    cput();
    cget();

    return 0;
}
#endif


/* ------------------------------------------ pratice 3.3 ---------------------------------------- */
#if 0
#include <fstream>

using namespace std;

struct strList {
    char course[15];
    int score;
};

int main()
{
    strList obj[2] = {{"C++", 90}, {"Java", 85}};
    ofstream outf("test.txt", ios::binary);    //以二进制格式打开文件
    if(!outf) {
        cout << "Cannot open output file." << endl;
        // exit(1);
        abort();
    }

    for(int i = 0; i< 2; i++) {
        outf.write((char*) &obj[i], sizeof(obj[i]));
    }
    outf.close();

    ifstream inf("test.txt", ios::binary);
    if(!inf) {
        cout << "Cannot open input file." << endl;
        abort();
    }

    for(int i = 0; i< 2; i++) {
        inf.read((char*) &obj[i], sizeof(obj[i]));
        cout << "Course: " << obj[i].course << " Score: " << obj[i].score << endl;
    }
    inf.close();

    return 0;
}
#endif


/* ------------------------------------------ pratice 3.4 ---------------------------------------- */
#if 0
#include <cmath>

using namespace std;

double triangle(double a, double b, double c)
{
    double s = (a + b + c)/2;
    if(a+b <= c || a+c <= b || b+c <= a) {
        throw 1.0;   //抛出double异常
    }
    return sqrt(s * (s-a) * (s-b) * (s-c));
}

int main()
{
    double zozoA, zozoB, zozoC;
    try{
        cout << "Enter three sides of a triangle: " << endl;
        cin >> zozoA >> zozoB >> zozoC;
        if(zozoA <= 0 || zozoB <= 0 || zozoC <= 0) {
            throw 1;   //抛出int异常
        }
        if(zozoA >0 && zozoB >0 && zozoC >0){
            cout << "The area of the triangle is: " << triangle(zozoA, zozoB, zozoC) << endl;
        }
    }catch(double){
        cout << "Invalid input, please enter positive numbers." << endl;
    } catch(int){
        cout << "边长小于0" << endl;
    }

    return 0;
}
#endif


/* ------------------------------------------ pratice 3.5 ---------------------------------------- */
#if 0
#include <vector>

using namespace std;

int main()
{
    vector<int> zoVec;
    zoVec.insert(zoVec.begin(), 99);
    zoVec.insert(zoVec.begin(), 88);
    zoVec.insert(zoVec.end(), 77);
    zoVec.push_back(695);

    cout << "当前zoVec中的元素为: " << endl;
    for(int i = 0; i < zoVec.size(); i++){
        cout << zoVec[i] << " ";
    }
    cout << endl;

    cout << zoVec.at(2) << endl;
    zoVec.erase(zoVec.begin());
    zoVec.pop_back();

    cout << "现在zoVec中的元素为: " << endl;
    for(int i = 0; i < zoVec.size(); i++){
        cout << zoVec[i] << " ";
    }
    cout << endl;

    return 0;
}
#endif


/* ------------------------------------------ pratice 3.6 ---------------------------------------- */
#if 0
#include <list>

using namespace std;

int main()
{
    list<int> zoList;
    list<int>::iterator niter;  // 定义迭代器 指向int类型元素
    zoList.push_back(123);
    zoList.push_back(456);
    zoList.push_back(789);

    cout << "链表内容 : " << endl;
    for(niter = zoList.begin(); niter != zoList.end(); niter++)
        cout << *niter << " ";
    cout << endl;

    zoList.reverse();  // 反转链表

    cout << "反转链表内容 : " << endl;
    for(niter = zoList.begin(); niter != zoList.end(); niter++)
        cout << *niter << " ";
    cout << endl;

    zoList.reverse();

    return 0;
}
#endif


/* ------------------------------------------ pratice 3.7 ---------------------------------------- */
#if 0
#include <stack>
using namespace std;

int main()
{
    stack<int> zoSt;
    int zoNum = 100;
    cout << "100的八进制为: ";
    while(zoNum) {
        zoSt.push(zoNum % 8);
        zoNum /= 8;
    }

    int zoS;
    while(!zoSt.empty()) {
        zoS = zoSt.top();
        cout << zoS;
        zoSt.pop();
    }
    cout << endl;

    return 0;
}
#endif


/* ------------------------------------------ pratice 3.8 ---------------------------------------- */
#if 0
#include <queue>
using namespace std;

int main()
{
    queue<int> zoQue;
    for(int i = 0; i<10; i++)
        zoQue.push(i*3 + i);

    while(!zoQue.empty()){
        cout << zoQue.front() << " ";
        zoQue.pop();
    }
    cout << endl;

    return 0;
}
#endif


/* ------------------------------------------ pratice 3.9 ---------------------------------------- */
#if 0
#include <queue>
#include <functional>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    priority_queue<int> zoPq;
    srand((unsigned)time(0));
    for(int i=0; i < 6; i++) {
        int zoR = rand();
        cout << zoR << " ";
        zoPq.push(zoR);
    }
    cout << endl;

    cout << "优先队列中的元素: " << endl;
    for(int i=0; i < 6; i++) {
        cout << zoPq.top() << " ";
        zoPq.pop();
    }

    return 0;
}
#endif



/* ------------------------------------------ pratice 4.0 ---------------------------------------- */
#if 0
#include <set>
#include <string>

using namespace std;

int main()
{
    set<string> zoSet;
    zoSet.insert("my");
    zoSet.insert("hair");
    zoSet.insert("wet");
    if(zoSet.count("my") != 0) {
        cout << "Existential element : my " << endl;
    }

    set<string>::iterator zoIter;
    for(zoIter = zoSet.begin(); zoIter != zoSet.end(); zoIter++) {
        cout << *zoIter << " ";
    }
    cout << endl;

    return 0;
}
#endif



/* ------------------------------------------ pratice 4.1 ---------------------------------------- */
#if 0
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, int> zoMap;
    zoMap["apple"] = 100;
    zoMap["banana"] = 200;
    zoMap["orange"] = 300;
    if(zoMap.count("apple")) {
        cout << "The price of apple is: " << zoMap.at("apple") << endl;
        // cout << "The price of apple is: " << zoMap["apple"] << endl;
    }

    return 0;
}
#endif



/* ------------------------------------------ pratice 0.0 ---------------------------------------- */
#if 1

using namespace std;


int main()
{

    return 0;
}

#endif



/*
 * @brief 保存人脸特征点数据
*/
void save_face_featuresListData();


save_face_featuresListData()
{
    QString featuresDir = "featuresListData";
    QDir dir(featuresDir);
    if (!dir.exists())
    {
        bool ismkdir = QDir().mkdir(featuresDir);
        if(!ismkdir)
            qDebug() << "Create path fail";
        else
            qDebug() << "Create fullpath success";
    }

    featuresDir += "/jh-face-module-";
    QDateTime time = QDateTime::currentDateTime();
    featuresDir += time.toString("yyyy-MM-dd");
    featuresDir += ".txt";

    featuresDir = QFileDialog::getSaveFileName(0, "保存人脸特征点数据", featuresDir, "*.txt");


    QDateTime time = QDateTime::currentDateTime();
    QString strTime = time.toString("yyyy-MM-dd_hh_mm_ss");
    static uint64_t index = 0;
    image.save(QString("%1/%2-%3.jpg").arg(rgbImageDir).arg(strTime).arg(index), "jpg", 100);
    index++;
}


void save_face_featuresListData(const QString &data)
{
    // 创建一个文件对话框或者直接指定保存路径
    QString featuresDir = QFileDialog::getSaveFileName(nullptr, "featuresListData", QDir::homePath(), "文本文件 (*.txt)");

    if (!featuresDir.isEmpty()) {
        QFile file(featuresDir);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            // 如果需要时间戳，可以加上下面的一行
            out << "保存时间：" << QDateTime::currentDateTime().toString() << "\n\n";

            out << data;

            file.close();
        } else {
            qDebug() << "Create path fail";
        }
    }
}
