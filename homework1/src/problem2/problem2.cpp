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

int main()
{
    vector<int> S = {1, 2, 3};
    vector<int> result;

    powerset(S, 0, result);

    return 0;
}
