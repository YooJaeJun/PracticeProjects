#include <bits/stdc++.h>
using namespace std;

int moveJoy(char& ch)
{
    return min(ch - 'A', 'Z' - ch);
}

int solution(string name) {
    int cnt = 0;
    int siz = name.size();
    int dir = 0;    // 0:정방향, 1:리버스

    for (int i = 0; i < siz; )
    {
        // 현재 위치 조작
        cnt += moveJoy(name[i]);

        // 다음 A 아닌 곳
        int nextNotAIdx = 0;
        while (i + nextNotAIdx + 1 < siz && name[i + nextNotAIdx + 1] == 'A')
        {
            nextNotAIdx++;
        }
        // 이동 정방향 or 거꾸로
        int reverseCnt = i + (siz - (i + nextNotAIdx + 1));
        if (dir == 0 && nextNotAIdx > reverseCnt)
        {
            cnt += reverseCnt;
            i += nextNotAIdx + 1;
            dir = 1;
        }
        else
        {
            if (dir == 0) cnt += nextNotAIdx + 1;
            i += nextNotAIdx + 1;
        }
    }
    return cnt;
}