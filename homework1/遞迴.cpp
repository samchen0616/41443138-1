#include <iostream>
#include <stack>

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

int AR(int m, int n)
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

int main()
{
    int m, n;

    cout << "Enter m and n: ";
    cin >> m >> n;

    cout << "Recursive: ";
    cout << Ackermann(m, n) << endl;

    cout << "Non-recursive: ";
    cout << AR(m, n) << endl;

    return 0;
}
