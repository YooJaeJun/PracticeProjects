#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

unordered_map<string, vector<int>> dicInfo;

void comb(vector<string>& vs, const int idx, const int score, const int depth, const int n)
{
    if (depth == n)
    {
        string s;
        for (auto& elem : vs)
        {
            s += elem;
        }
        dicInfo[s].push_back(score);
        return;
    }

    for (int i = idx; i < 4; i++)
    {
        string tmpSave = vs[i];
        vs[i] = "-";
        comb(vs, i + 1, score, depth + 1, n);
        vs[i] = tmpSave;
    }
}

vector<int> solution(vector<string> info, vector<string> query) {

    string tmpForStream;
    stringstream stream;
    vector<string> vs;
    for (auto& str : info)
    {
        vs.clear();
        stream.clear();
        stream.str(str);
        while (stream >> tmpForStream)
        {
            vs.push_back(tmpForStream);
        }
        int score = stoi(vs.back());
        vs.pop_back();

        for (int i = 0; i <= 4; i++)
        {
            comb(vs, 0, score, 0, i);
        }
    }

    vector<int> answer;
    for (auto& str : query)
    {
        string tmpForSearch;
        int score = 0;
        int ans = 0;

        for (int i = 0; i < (int)str.size(); )
        {
            if (str[i] == '-')
            {
                tmpForSearch += '-';
                i++;
            }
            else if (str[i] == ' ')
            {
                if (str[i + 1] >= '0' and str[i + 1] <= '9')
                {
                    score = stoi(str.substr(i + 1, (int)str.size() - i - 1));
                    sort(dicInfo[tmpForSearch].begin(), dicInfo[tmpForSearch].end());
                    ans = lower_bound(dicInfo[tmpForSearch].begin(), dicInfo[tmpForSearch].end(), score) 
                        - dicInfo[tmpForSearch].begin();
                    ans = dicInfo[tmpForSearch].size() - ans;
                    break;
                }
                else 
                    i += 5;
            }
            else
            {
                tmpForSearch += str[i];
                i++;
            }
        }

        answer.push_back(ans);
    }

    return answer;
}


int main()
{
    solution(
        { "java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50" },
        { "java and backend and junior and pizza 100", "python and frontend and senior and chicken 200", "cpp and - and senior and pizza 250", "- and backend and senior and - 150", "- and - and - and chicken 100", "- and - and - and - 150" }
    );

    return 0;
}