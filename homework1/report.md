# 41443138
作業一
## problem1的解題說明
這題要計算 Ackermann 函數，而且要用遞迴以及非遞迴來做：

 Ackermann 函數的規則是：
 - 當 `m = 0` 時，答案是 `n + 1`。
 - 當 `m > 0` 且 `n = 0` 時，計算 `A(m - 1, 1)`。
 - 其他情況計算 `A(m - 1, A(m, n - 1))`。
## 程式實作

以下為主要程式碼

```cpp
#include <iostream>
using namespace std;

int Ackermann(int m, int n)
{
    if (m == 0)
    {
        return n + 1;
    }
    else if (n == 0)
    {
        return Ackermann(m - 1, 1);
    }
    else
    {
        return Ackermann(m - 1, Ackermann(m, n - 1));
    }
}
