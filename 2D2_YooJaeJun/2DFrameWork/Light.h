#pragma once
class Light : public Singleton<Light>
{
private:
    struct PointLight
    {
        Vector2 screenPos;      //��ũ����ǥ  //8
        float   radius;         //������ũ��  //12
        float   select;         //���� ����    //16
        Color   lightColor;     //���� ��     // 16 + 16
        Color   outColor;       //���� �� ��
    };
    ID3D11Buffer * lightBuffer;

public:
    PointLight light;

    Light();
    ~Light();

    void        Set();
    void        SetLightPos(Vector2 WPos);
};

