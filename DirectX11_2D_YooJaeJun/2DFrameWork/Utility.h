#pragma once

class Numeric;

namespace Utility
{
    //�浹Ÿ��
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


    // �� ��
    ColPos IntersectLineLine(LINE& l1, LINE& l2);

    // �簢�� ��
    ColPos IntersectRectCoord(RECT & rc, Vector2 coord);
    // �簢�� ��
    ColPos IntersectRectLine(RECT& rc, LINE& l);
    // �簢�� �簢��
    ColPos IntersectRectRect(RECT & rc1, RECT & rc2);
    // �簢�� �簢�� OBB 
    ColPos IntersectRectRect(GameObject * ob1, GameObject * ob2);
    // �簢�� ��
    ColPos IntersectRectCircle(RECT& rc, CIRCLE& cc);

    // �� ��
    ColPos IntersectCircleCoord(CIRCLE& cc, Vector2 coord);
    // �� ��
    ColPos IntersectCircleLine(CIRCLE& cc, LINE& l);
    // �� ��
    ColPos IntersectCircleCircle(CIRCLE & cc1, CIRCLE & cc2);

    // bool IntersectRectCircle(GameObject* ob1, GameObject* ob2, COLDIR& result);

    float DirToRadian(Vector2 Dir);

    //���ø� �Լ��� ����,���� �и� �Ұ�
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

