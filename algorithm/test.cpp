 #include <iostream>
using namespace std;
#include "test.h"
template<typename T>

T Add(T a, T b)
{
    return a+b;
}
template int Add<int>(int,int);
// void test()
// {
//     int a=1,b=2;
//     cout<<Add(a,b)<<endl;
// }
