# 41443138
作業一

## 解題說明

### 解題策略
使用 Term 類別儲存多項式的每一項資料，包含：

- `coef`：表示多項式的係數。
- `exp`：表示多項式的次方。

## 程式實作

以下為主要程式碼

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;

class Term {

    friend class Polynomial;
    friend istream& operator>>(istream& in, Polynomial& p);
    friend ostream& operator<<(ostream& out, const Polynomial& p);

private:

    float coef;
    int exp;

};

class Polynomial {

private:

    Term* termArray;

    int capacity;

    int terms;

public:

    Polynomial() : capacity(2), terms(0) {

        termArray = new Term[capacity];
    }

   
    Polynomial(const Polynomial& b) {

        capacity = b.capacity;
        terms = b.terms;

        termArray = new Term[capacity];

        for (int i = 0; i < terms; i++) {
            termArray[i] = b.termArray[i];
        }
    }

   
    Polynomial& operator=(const Polynomial& b) {

        if (this != &b) {

            delete[] termArray;

            capacity = b.capacity;
            terms = b.terms;

            termArray = new Term[capacity];

            for (int i = 0; i < terms; i++) {
                termArray[i] = b.termArray[i];
            }
        }

        return *this;
    }

  
    ~Polynomial() {

        delete[] termArray;
    }

    void newTerm(const float theCoef, const int theExp);

    Polynomial Add(const Polynomial& b);

    Polynomial Mult(const Polynomial& b);

    float Eval(float x);

  
    friend istream& operator>>(istream& in, Polynomial& p);

    friend ostream& operator<<(ostream& out, const Polynomial& p);

};



void Polynomial::newTerm(const float theCoef, const int theExp) {

    if (theCoef == 0) return;

    int i = 0;

    
    while (i < terms && termArray[i].exp > theExp) {
        i++;
    }


    if (i < terms && termArray[i].exp == theExp) {

        termArray[i].coef += theCoef;

        if (termArray[i].coef == 0) {

            for (int j = i; j < terms - 1; j++) {
                termArray[j] = termArray[j + 1];
            }

            terms--;
        }

        return;
    }

    if (terms == capacity) {

        capacity *= 2;

        Term* temp = new Term[capacity];

        for (int j = 0; j < terms; j++) {
            temp[j] = termArray[j];
        }

        delete[] termArray;

        termArray = temp;
    }

   
    for (int j = terms; j > i; j--) {
        termArray[j] = termArray[j - 1];
    }

    termArray[i].coef = theCoef;

    termArray[i].exp = theExp;

    terms++;
}



Polynomial Polynomial::Add(const Polynomial& b) {

    Polynomial c;

    int aPos = 0, bPos = 0;

    while ((aPos < terms) && (bPos < b.terms))

        if (termArray[aPos].exp == b.termArray[bPos].exp) {

            float t = termArray[aPos].coef + b.termArray[bPos].coef;

            if (t) c.newTerm(t, termArray[aPos].exp);

            aPos++;
            bPos++;

        }

        else if (termArray[aPos].exp < b.termArray[bPos].exp) {

            c.newTerm(b.termArray[bPos].coef,
                b.termArray[bPos].exp);

            bPos++;

        }

        else {

            c.newTerm(termArray[aPos].coef,
                termArray[aPos].exp);

            aPos++;

        }

    for (; aPos < terms; aPos++)

        c.newTerm(termArray[aPos].coef,
            termArray[aPos].exp);

    for (; bPos < b.terms; bPos++)

        c.newTerm(b.termArray[bPos].coef,
            b.termArray[bPos].exp);

    return c;

}



Polynomial Polynomial::Mult(const Polynomial& b) {

    Polynomial c;

    if (terms == 0 || b.terms == 0) {

        return c;
    }

    for (int i = 0; i < terms; i++) {

        Polynomial temp;

        for (int j = 0; j < b.terms; j++) {

            float coef = termArray[i].coef * b.termArray[j].coef;

            int exp = termArray[i].exp + b.termArray[j].exp;

            if (coef != 0) {

                temp.newTerm(coef, exp);
            }
        }

        c = c.Add(temp);
    }

    return c;
}


float Polynomial::Eval(float x) {

    float result = 0;

    for (int i = 0; i < terms; i++) {

        result += termArray[i].coef *
            pow(x, termArray[i].exp);
    }

    return result;
}



istream& operator>>(istream& in, Polynomial& p) {

    int n;

    in >> n;

    p.terms = 0;

    for (int i = 0; i < n; i++) {

        float coef;
        int exp;

        in >> coef >> exp;

        p.newTerm(coef, exp);
    }

    return in;
}



ostream& operator<<(ostream& out, const Polynomial& p) {

    if (p.terms == 0) {

        out << "0";

        return out;
    }

    for (int i = 0; i < p.terms; i++) {

        float coef = p.termArray[i].coef;

        int exp = p.termArray[i].exp;

        if (i > 0) {

            if (coef > 0)
                out << " + ";
            else
                out << " - ";
        }

        else if (coef < 0) {

            out << "-";
        }

        float absCoef = fabs(coef);

        if (exp == 0 || absCoef != 1) {

            out << absCoef;
        }

        if (exp > 0) {

            out << "x";

            if (exp > 1) {

                out << "^" << exp;
            }
        }
    }

    return out;
}



int main() {

    Polynomial P1, P2, FINISH;

    float x;

    cout << "輸入第一個多項式: ";
    cin >> P1;

    cout << "輸入第二個多項式): ";
    cin >> P2;

    cout << "\nP1 = " << P1 << endl;

    cout << "P2 = " << P2 << endl;

  
    FINISH = P1.Add(P2);

    cout << "\n加法 = " << FINISH << endl;

 
    FINISH = P1.Mult(P2);

    cout << "乘法 = " << FINISH << endl;

   
    cout << "\n輸入 x: ";
    cin >> x;

    cout << "P1(" << x << ") = " << P1.Eval(x) << endl;

    return 0;
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

