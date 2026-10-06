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

int main()
{
    int m, n;

    cout << "Enter m and n: ";
    cin >> m >> n;

    cout << "Non-recursive Ackermann = ";
    cout << AckermannNonRecursive(m, n) << endl;

    return 0;
}
