# 41443138
作業一

## 解題說明

### 解題策略
使用 Term 類別儲存多項式的每一項資料，包含：
- `coef`：表示多項式的係數。
- `exp`：表示多項式的次方。
\n 使用 Polynomial 類別管理整個多項式，主要資料成員如下：
- `termArray`：使用動態陣列儲存多項式的各項資料。
- `capacity`：表示目前陣列可以儲存的容量。
- `terms`：表示目前多項式有幾個非零項。  
本次作業使用運算子多載，讓多項式可以直接進行輸入與輸出
- `operator>>`：讓使用者輸入多項式的項數、係數及次方。
- `operator<<`：將多項式以正常數學格式顯示。
- 另外使用 friend，讓輸入及輸出函式可以存取 Polynomial 和 Term 的 private 資料。

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
１建構子 Polynomial():目的是建立容量為 2 的動態陣列。
時間複雜度：O(C)
空間複雜度：O(C)

２複製建構子:目的是使用迴圈複製原本多項式的所有資料。
時間複雜度：O(n)
空間複雜度：O(C)



３指定運算子 operator=:目的是先釋放原本的記憶體，再配置新的陣列並複製資料。
時間複雜度：O(C=n)
空間複雜度：O(C)

４解構子:目的是釋放動態配置的陣列。
時間複雜度：O(n)
空間複雜度：O(1)

５newTerm():新增一個多項式項目，如果陣列容量不足，就擴大容量。
時間複雜度：O(n)
空間複雜度：O(C)

６Add():將兩個多項式逐項比較，並合併相同次方的項目。
假設兩個多項式分別有 m、n 項：
時間複雜度：O(m+n)
空間複雜度：O(m+n)

７Mult():使用雙層迴圈，將第一個多項式的每一項與第二個多項式的每一項相乘。
 時間複雜度：O(mn(m+n))（依目前的插入合併實作）
空間複雜度：O(mn)（保守最壞估計）
## 測試與驗證


| 測試案例 | 輸入 | 輸入 | 加法輸出 | 乘法輸出 | ｘ輸出 |
| --- | --- | --- | --- | --- | --- |
| 測試一 | `3x^2 + 4x - 2` | ` 2x + 1` | `3x^2 + 6x - 1`| `6x^3 + 11x^2 - 2`| `１８`|
| 測試二 | `x^3 - 5x^2 + 6` | `4x^4 - 2x^2 + x - 7` | `4x^4 + x^3 - 7x^2 + x - 1`| `4x^7 - 20x^6 + x^5 + 16x^4 + 13x^3 - 37x^2 + 6x - 42`| `－６`|
| 測試三 | `5x^5 + 3x^3 - 8` | `-x^2 + 10x - 15` | `5x^5 - x^2 + 3x^3 + 10x - 23`| `-5x^7 + 50x^6 - 78x^5 - 15x^3 + 8x^2 - 80x + 120`| `１７６`|
| 測試四 | `7x^3 + 2x^2 - 9x + 4` | `x^6 - 1` | `x^6 + 7x^3 + 2x^2 - 9x + 3`| `7x^9 + 2x^8 - 9x^7 + 4x^6 - 7x^3 - 2x^2 + 9x - 4`| `５０`|
### 編譯結果
```shell
g++ src/problem1.cpp --std=c++21 -o problem1.exe
./problem1.exe
```
## 申論及開發報告
選擇以動態陣列與雙指標實作多項式的原因
在本專案中，實作多項式的加法與乘法時，採用動態陣列（termArray）搭配雙指標與 newTerm 機制，其主要原因如下：

1. 記憶體使用具備高效率與緊湊性
多項式通常具有「稀疏（Sparse）」的特性（即許多次方項的係數為 0）。若使用傳統的一維陣列直接以指數作為索引，會浪費大量記憶體空間來儲存係數為 0 的項。
採用 Term 結構體（僅儲存非零項的係數 coef 與指數 exp），能夠精準利用記憶體：
```cpp
class Term {
    friend class Polynomial;
private:
    float coef;
    int exp;
};
```
當容量不足時，透過動態擴容（capacity *= 2）與 newTerm 確保只配置實際需要的空間。
２.完整的物件生命週期與安全性
由於類別內部使用動態配置指標（Term* termArray），透過完整實作 Rule of Three（複製建構子、指定運算子與解構子），確保物件在進行複製品指派或函式傳回時，不會發生淺拷貝（Shallow Copy）或記憶體重複釋放（Double Free）的問題，保障程式執行的穩定性。

透過動態陣列與結構化設計，程式兼顧了執行效能與記憶體空間的節省。然而，若多項式項數極度龐大且頻繁進行中間插入時，陣列搬移仍會帶來一定的額外開銷，但在常規代數運算中已能高效且正確地完成加法與乘法需求。


