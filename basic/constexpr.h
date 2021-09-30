#include "../stdafx.h"
/**
 * constexpr
 * 使指定的常量表达式获得在程序编译阶段计算出结果的能力，而不必等到程序运行阶段
 * C++ 11 标准中，constexpr 可用于修饰普通变量、函数（包括模板函数）以及类的构造函数。
 * 注意，获得在编译阶段计算出结果的能力，并不代表 constexpr 修饰的表达式一定会在程序编译阶段被执行，具体的计算时机还是编译器说了算。
 */

/** 
 * constexpr修饰int变量，可用于数组定义长度
 */
void constexprForArrayIndex()
{
    int num = 3;
    // int arr1[num] = {1, 2, 3}; //编译报错，因为数组定义时元素个数不能是变量
    int arr2[]{1, 2, 3};
    int arr3[3]{1, 2, 3};
    for (auto n : arr2)
        cout << n << " ";
    cout << endl;
    for (auto n : arr3)
        cout << n << " ";
    cout << endl;
    constexpr int num1 = 1 + 2; //这里未编译时，intelliSense（代码感知）会提示variable-sized object may not be initialized
    int arr1[num1]{1, 2, 3};    //编译后num1会被计算为一个常亮保存在编译结果中，运行时num1就是一个常量
    for (const int n : arr1)
        cout << n << " ";
    cout << endl;
}

/**
 * constexpr修饰函数
 * 条件：
 * 1，必须且只能只能一条 return 返回语句，不能有其他逻辑代码
 * 2，不能声明使用，即定义必须出现在使用之前
 * 3，返回值必须是常量表达式（不能有参数除外的变量参与）
 */
constexpr int constexprForFunc(int x)
{
    //可以添加 using 执行、typedef 语句以及 static_assert 断言
    return 1 + 2 + x;
}

/**
 * constexpr修饰模板函数
 * C++11 标准规定，如果 constexpr 修饰的模板函数实例化结果不满足常量表达式函数的要求，则 constexpr 会被自动忽略，即该函数就等同于一个普通函数。
 */
template <typename T>
constexpr T constexprForTF(T x)
{
    return x;
}
//自定义类型的定义
struct ttType
{
    const char *name;
    int age;
    //其它结构体成员
};
void constexprForTFunc()
{
    int arr[constexprForTF(5)]{1, 2, 3};
    for (auto n : arr)
        cout << n << " ";
    cout << endl;

    struct ttType tt
    {
        "tom", 11
    };
    struct ttType t1 = constexprForTF(tt); //constexpr 被自动忽略，即该函数就等同于一个普通函数。
    cout << tt.name << "," << tt.age << endl;
    cout << t1.name << "," << t1.age << endl;
}

/**
 * constexpr修饰结构体/类
 * 条件：
 * 1，constexpr构造函数的函数体必须为空
 * 2，采用初始化列表的方式为各个成员赋值时，必须使用常量表达式
 */
class myType
{
public:
    constexpr myType(const char *name, int age) : name(name), age(age), id(0){};
    myType(const char *name, int age, int id) : name(name), age(age), id(id){};
    constexpr int getAge() { return age; }
    constexpr const char *getName() { return name; }
    int getId() { return id; }

private:
    const char *name;

public:
    int age;
    int id;
};
void constexprForClass()
{
    myType mt{"tom", 11};
    // constexpr int age = mt.getAge(); //mt非常量，所以常量表达式不成立
    int id = mt.getId();

    constexpr myType mt1{"tom", 11};
    constexpr int age1 = mt1.getAge();
    constexpr const char *name1 = mt1.getName();
    // int id1 = mt1.getId(); //getId()未添加常量限定，无法访问常量成员id
    constexpr int id1 = mt1.id;
    // id1 = 20; //constexpr告诉编译器id1是个可在编译器确定的变量，所以编译器认为id1不是个可修改的左值
    // mt1.id = 10; //myType为常量对象,非左值
}