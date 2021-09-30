#include "stdafx.h"
#include "./basic/constexpr.h"
using namespace std;

int main()
{
    constexprForArrayIndex();

    int n = 3;
    cout << constexprForFunc(n) << endl;

    constexprForTFunc();

    return 0;
}
