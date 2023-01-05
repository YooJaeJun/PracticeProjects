#pragma once

struct FontBrushDesc;
struct FontTextDesc;

class DWrite : public Singleton<DWrite>
{
    ID2D1Device* device;
    ID2D1DeviceContext* deviceContext = nullptr;
    ID2D1Factory1* factory;
    IDWriteFactory* writeFactory = nullptr;
    ID2D1Bitmap1* targetBitmap;

    vector<FontBrushDesc> fontBrush;
    vector<FontTextDesc>  fontText;

public:
    DWrite();
    ~DWrite();
    ID2D1DeviceContext* GetDC() { return deviceContext; }
    //â������ ����
    void CreateBackBuffer(float width, float height);
    void DeleteBackBuffer();

public:
    //UI�ȿ��� �׸���
    void RenderText
    (
        wstring text
        , RECT rect
        , float size = 20.0f
        , wstring font = L"����ü"
        , Color color = Color(1, 1, 1, 1)
        , DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL
        , DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL
        , DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL
    );
};

struct FontBrushDesc
{
    Color color;
    ID2D1SolidColorBrush* brush = NULL;

    //�����ڿ������̵�
    bool operator==(const FontBrushDesc& val)
    {
        return color.x == val.color.x &&
            color.y == val.color.y &&
            color.z == val.color.z &&
            color.w == val.color.w;
    }
};

struct FontTextDesc
{
    wstring font;
    float fontSize;

    DWRITE_FONT_WEIGHT weight;
    DWRITE_FONT_STYLE style;
    DWRITE_FONT_STRETCH stretch;

    IDWriteTextFormat* format = nullptr;

    bool operator==(const FontTextDesc& val)
    {
        bool b = true;

        b &= font == val.font;
        b &= fontSize == val.fontSize;
        b &= weight == val.weight;
        b &= style == val.style;
        b &= stretch == val.stretch;

        return b;
    }

};
