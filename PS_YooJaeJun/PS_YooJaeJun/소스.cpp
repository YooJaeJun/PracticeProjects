#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<string>> rel;
vector<vector<int>> history;  // 최소성 위해 성공한 것들 세이브
int ans = 0;
vector<int> cur;

bool checkOverlap()
{
    vector<string> values;
    for (auto& r : rel)
    {
        string forSearch;
        for (int i = 0; i < (int)cur.size(); i++)
        {
            forSearch += r[cur[i]];
        }

        auto it = find(values.begin(), values.end(), forSearch);
        if (it == values.end())
        {
            values.push_back(forSearch);
        }
        else return false;
    }
    return true;
}

bool checkMinimality()
{
    bool flag = false;
    for (int i = 0; i < (int)history.size(); i++)
    {
        for (int j = 0; j < (int)history.size(); j++)
        {
            if (find(cur.begin(), cur.end(), history[i][j]) == cur.end())
            {
                flag = true;
                break;
            }
        }
        if (flag == false) 
            return false;
    }
    return true;
}

void comb(int idx)
{
    if (cur.size() == n)
    {
        if (checkMinimality() and checkOverlap())
        {
            history.push_back(cur);
            ++ans;
        }
        return;
    }

    for (int i = idx; i < (int)rel[i].size(); i++)
    {
        cur.push_back(i);
        comb(i + 1);
        cur.pop_back();
    }
}

int solution(vector<vector<string>> relation) {
    rel = relation;

    for (int i = 1; i < (int)rel.size(); i++)
    {
        n = i;
        vector<int> v;
        comb(0);
    }

    return ans;
}

int main()
{
    solution({ {"100", "ryan", "music", "2"}, {"200", "apeach", "math", "2"}, {"300", "tube", "computer", "3"}, {"400", "con", "computer", "4"}, {"500", "muzi", "music", "3"}, {"600", "apeach", "music", "2"} });

    return 0;
}