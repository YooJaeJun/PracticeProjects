#pragma once
enum COLDIR
{
    NONE,
    UPDOWN,
    LEFTRIGHT,
    EDGE
};
namespace Utility
{
    //�浹Ÿ��
    struct RECT
    {
        Vector2 min;
        Vector2 max;
        RECT(Vector2 pivot, Vector2 scale);
    };
    struct CIRCLE
    {
        Vector2 pivot;
        float   radius;
        CIRCLE(Vector2 pivot, Vector2 scale);
    };

    //�簢�� �� �� ��ǥ
    bool IntersectRectCoord(RECT & rc, Vector2 coord);
    bool IntersectCircleCoord(CIRCLE & cc, Vector2 coord);

    //�׸� �׸�
    bool IntersectRectRect(RECT & rc1, RECT & rc2);
    //OBB
    bool IntersectRectRect(GameObject * ob1, GameObject * ob2);

    //�� ��
    bool IntersectCircleCircle(CIRCLE & cc1, CIRCLE & cc2);
    //�׸� ��
    bool IntersectRectCircle(RECT & rc, CIRCLE & cc);

    bool IntersectRectCircle(GameObject* ob1, GameObject* ob2, COLDIR& result);

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

