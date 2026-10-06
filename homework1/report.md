# 41443138
作業一
## problem1
### 解題說明
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

#include <iostream>
#include <stack>

using namespace std;

int AckermannNonRecursive(int m, int n)
{
    stack<int> s;

    s.push(m);

    while (!s.empty())
    {
        m = s.top();
        s.pop();

        if (m == 0)
        {
            n = n + 1;
        }
        else if (n == 0)
        {
            n = 1;
            s.push(m - 1);
        }
        else
        {
            s.push(m - 1);
            s.push(m);
            n = n - 1;
        }
    }

    return n;
}

```
## 效能分析
- 時間複雜度： 程式的時間複雜度為 \(O(A(m,n))\).
- 空間複雜度： 程式的空間複雜度為 O(A(m,n)).

## 測試與驗證

| 測試案例 | 輸入 | 預期輸出 |
| --- | --- | --- |
| 測試一 | `A(0,0)` | `1` |
| 測試二 | `A(1,1)` | `3` |
| 測試三 | `A(2,2)` | `7` |
| 測試四 | `A(2,3)` | `9` |
| 測試五 | `A(3,2)` | `29` |
### 編譯結果
```shell
g++ src/problem1.cpp --std=c++21 -o problem1.exe
./problem1.exe
Recursive: 3
Non-recursive: 3
```
## 申論及開發報告
遞迴版本是直接依照 Ackermann 函式的數學定義進行實作，透過函式自己呼叫自己的方式完成計算，
遞迴程式的結構較為簡潔，也容易理解，但當遞迴層數過深時，會消耗較多的記憶體，
且可能降低執行效率，甚至造成 Stack Overflow，非遞迴版本則不使用函式自行呼叫的方式，
而是利用 Stack 來模擬遞迴的執行過程。由於 Stack 具有**後進先出（LIFO）**的特性，
可以將尚未完成的計算工作暫時保存，並依照正確的順序取出處理，因此能夠模擬原本遞迴函式的執行方式。

## problem2

### 解題說明
這題要計算一個集合的 Powerset（冪集），也就是找出這個集合所有可能的子集合，而且要使用遞迴來完成。

例如：

S = {1, 2, 3}

每一個元素都有「選擇」和「不選擇」兩種情況：

不選擇目前的元素。
選擇目前的元素。

透過遞迴將每個元素分成這兩種情況，就可以找出所有可能的子集合。

當所有元素都處理完時，就將目前的結果輸出。

因為每個元素都有 2 種選擇，所以如果集合有 n 個元素，總共有 \(2^n\) 個子集合
## 程式實作
```cpp
#include <iostream>
#include <vector>
using namespace std;

void powerset(vector<int> S, int index, vector<int> result)
{

    if (index == S.size())
    {
        cout << "{ ";

        for (int i = 0; i < result.size(); i++)
        {
            cout << result[i] << " ";
        }

        cout << "}" << endl;

        return;
    }


    powerset(S, index + 1, result);


    result.push_back(S[index]);

    powerset(S, index + 1, result);
}
```
## 效能分析
- 時間複雜度：程式需要產生所有子集合，因此時間複雜度約為 \(O(2^n)\)。
- 空間複雜度：遞迴過程最多會有 n 層，因此空間複雜度為 \(O(n)\)。

## 測試與驗證
{ }
{ 3 }
{ 2 }
{ 2 3 }
{ 1 }
{ 1 3 }
{ 1 2 }
{ 1 2 3 }
### 編譯結果
```shell
g++ src/problem2.cpp --std=c++21 -o problem2.exe
./problem2.exe
{ }
{ 3 }
{ 2 }
{ 2 3 }
{ 1 }
{ 1 3 }
{ 1 2 }
{ 1 2 3 }
```
## 申論及開發報告
這題是利用遞迴的方式來產生集合的所有子集合。每處理一個元素時，
都會分成「選擇」和「不選擇」兩種情況，再繼續處理下一個元素。
當所有元素都處理完成後，就會將目前產生的子集合輸出，因為每個元素都有兩種選擇，
所以一個有 n 個元素的集合，最後會產生 \(2^n\) 個子集合，
在開發過程中，我使用 vector 來存放原本的集合以及目前產生的子集合，並利用 index 判斷目前處理到哪一個元素，
透過遞迴不斷處理「選擇」與「不選擇」的情況，最後成功產生所有可能的子集合，
透過這次作業，我更加了解遞迴的使用方式，也了解到冪集的數量會隨著集合元素增加而快速增加。
