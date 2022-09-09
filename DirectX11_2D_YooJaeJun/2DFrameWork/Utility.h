#pragma once

namespace Utility
{
    //충돌타입
    struct RECT
    {
        Vector2 min;
        Vector2 max;
        Vector2 lt, lb, rt, rb;
        RECT(Vector2 pivot, Vector2 scale);
    };
    struct CIRCLE
    {
        Vector2 pivot;
        float   radius;
        CIRCLE(Vector2 pivot, Vector2 scale);
    };
    struct LINE
    {
        Vector2 begin;
        Vector2 end;
        LINE(Vector2 begin, Vector2 end);
    };


    // 선 선
    colPos IntersectLineLine(LINE& l1, LINE& l2);

    // 사각형 점
    colPos IntersectRectCoord(RECT & rc, Vector2 coord);
    // 사각형 선
    colPos IntersectRectLine(RECT& rc, LINE& l);
    // 사각형 사각형
    colPos IntersectRectRect(RECT & rc1, RECT & rc2);
    // 사각형 사각형 OBB 
    colPos IntersectRectRect(GameObject * ob1, GameObject * ob2);
    // 사각형 원
    colPos IntersectRectCircle(RECT& rc, CIRCLE& cc);

    // 원 점
    colPos IntersectCircleCoord(CIRCLE& cc, Vector2 coord);
    // 원 선
    colPos IntersectCircleLine(CIRCLE& cc, LINE& l);
    // 원 원
    colPos IntersectCircleCircle(CIRCLE & cc1, CIRCLE & cc2);

    // bool IntersectRectCircle(GameObject* ob1, GameObject* ob2, COLDIR& result);

    float DirToRadian(Vector2 Dir);

    //템플릿 함수는 선언,정의 분리 불가
    template<typename T>
    T Saturate(T src, T min = 0, T max = 1)
    {
        if (src < min)
        {
            return min;
        }
        else if (src > max)
        {
            return max;
        }
        return src;
    }

    template<typename T>
    void Swap(T & a, T & b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    /*template<typename T>
    void Shuffle(T & arr, int range, int count)
    {
        for (int i = 0; i < count; i++)
        {
            int sour = rand() % range;
            int dest = rand() % range;
            Swap(arr[sour], arr[dest]);
        }
    }*/

};

