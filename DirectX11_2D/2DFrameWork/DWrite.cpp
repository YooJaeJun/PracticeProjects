#include "framework.h"

DWrite::DWrite()
{
    HRESULT hr;

    hr = DWriteCreateFactory
    (
        DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&writeFactory
    );
    assert(SUCCEEDED(hr));


    D2D1_FACTORY_OPTIONS option;
    option.debugLevel = D2D1_DEBUG_LEVEL_NONE;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);
    assert(SUCCEEDED(hr));

    IDXGIDevice* dxgiDevice;
    hr = D3D->GetDevice()->QueryInterface(&dxgiDevice);
    assert(SUCCEEDED(hr));

    hr = factory->CreateDevice(dxgiDevice, &device);
    assert(SUCCEEDED(hr));

    hr = device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &deviceContext);
    assert(SUCCEEDED(hr));


    IDXGISurface* dxgiSurface;
    hr = D3D->GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&dxgiSurface);
    assert(SUCCEEDED(hr));


    D2D1_BITMAP_PROPERTIES1 bp;
    bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
    bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
    bp.dpiX = 96;
    bp.dpiY = 96;
    bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
    bp.colorContext = NULL;

    hr = deviceContext->CreateBitmapFromDxgiSurface(dxgiSurface, &bp, &targetBitmap);
    assert(SUCCEEDED(hr));
    SafeRelease(dxgiDevice);
    SafeRelease(dxgiSurface);
    deviceContext->SetTarget(targetBitmap);
}

DWrite::~DWrite()
{
    //���� ������ ��ŭ ����
    for (FontBrushDesc desc : fontBrush)
        SafeRelease(desc.brush);

    for (FontTextDesc desc : fontText)
        SafeRelease(desc.format);

    SafeRelease(targetBitmap);

    SafeRelease(factory);
    SafeRelease(writeFactory);

    SafeRelease(deviceContext);
    SafeRelease(device);
}

void DWrite::CreateBackBuffer(float width, float height)
{
    HRESULT hr;

    hr = device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &deviceContext);
    assert(SUCCEEDED(hr));

    IDXGISurface* dxgiSurface;
    hr = D3D->GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&dxgiSurface);
    assert(SUCCEEDED(hr));


    D2D1_BITMAP_PROPERTIES1 bp;
    bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
    bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
    bp.dpiX = 96;
    bp.dpiY = 96;
    bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
    bp.colorContext = NULL;

    hr = deviceContext->CreateBitmapFromDxgiSurface(dxgiSurface, &bp, &targetBitmap);
    assert(SUCCEEDED(hr));
    SafeRelease(dxgiSurface);

    deviceContext->SetTarget(targetBitmap);
}

void DWrite::DeleteBackBuffer()
{
    SafeRelease(targetBitmap);
    SafeRelease(deviceContext);
}

void DWrite::RenderText(wstring text, RECT rect, float size, wstring font, Color color, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch)
{
    FontBrushDesc brushDesc;
    brushDesc.color = color;

    FontBrushDesc* findBrush = NULL;

    for (FontBrushDesc& desc : fontBrush)
    {
        if (desc == brushDesc)
        {
            findBrush = &desc;
            break;
        }
    }

    //���;ȿ� �ش� �귯�ð� ���ٸ�
    if (findBrush == NULL)
    {
        D2D1::ColorF colorF = D2D1::ColorF(color.x, color.y, color.z);
        deviceContext->CreateSolidColorBrush(colorF, &brushDesc.brush);

        //�ش� �귯�ø� ���Ϳ� �߰�(������ �������� �ʱ⶧����)
        fontBrush.push_back(brushDesc);
        findBrush = &brushDesc;
    }

    //�Ű����� ��Ʈ�� ����
    FontTextDesc textDesc;
    textDesc.font = font;
    textDesc.fontSize = size;
    textDesc.stretch = stretch;
    textDesc.style = style;
    textDesc.weight = weight;

    FontTextDesc* findText = NULL;
    //������ �����ŭ �ݺ�

    //for (FontTextDesc& desc : fontText)
    for (UINT i = 0; i < fontText.size(); i++)
    {
        //���� ���� �ؽ�Ʈ�� ���� �Ҷ�
        //if (desc == textDesc)
        if (fontText[i] == textDesc)
        {
            //findText = &desc;
            findText = &fontText[i];
            break;
        }
    }
    //���ٸ� �߰�
    if (findText == NULL)
    {
        writeFactory->CreateTextFormat
        (
            textDesc.font.c_str(), NULL, textDesc.weight, textDesc.style, textDesc.stretch, textDesc.fontSize,
            L"ko", &textDesc.format
        );

        fontText.push_back(textDesc);
        findText = &textDesc;
    }

    D2D1_RECT_F rectF;
    rectF.left = (float)rect.left;
    rectF.right = (float)rect.right;
    rectF.top = (float)rect.top;
    rectF.bottom = (float)rect.bottom;


    deviceContext->DrawTextW
    (
        text.c_str(), text.size(), findText->format, rectF, findBrush->brush
    );
}
