#include "stdafx.h"
#include "./basic/constexpr.h"

int main()
{
    constexprForArrayIndex();

    int n = 3;
    cout << constexprForFunc(n) << endl;

    constexprForTFunc();

    constexprForClass();

    return 0;
}
