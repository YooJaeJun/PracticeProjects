#include "framework.h"

Texture::~Texture()
{
    for (auto i = textureList.begin();
        i != textureList.end(); i++)
    {
        //i->first; // key
        //i->second;// value
        if (i->second)
        {
            i->second->Release();
        }
    }
    textureList.clear();
}

ID3D11ShaderResourceView* Texture::LoadTexture(wstring file)
{
    auto iter = textureList.find(file);
    //�ߺ��Ȱ� ����.
    if (iter == textureList.end())
    {
        ID3D11ShaderResourceView* temp;
        wstring path = L"../Contents/Images/" + file;

        ScratchImage image;
        LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);

        HRESULT hr = CreateShaderResourceView(D3D->GetDevice(), image.GetImages(), image.GetImageCount(),
            image.GetMetadata(), &temp);


        // �ؽ��Ŀ��� ��ǥ��
        // 130, 79
        // cout << (int)image.GetPixels()[4 * (79 * 10 + 130)] << endl;
        // cout << (int)image.GetPixels()[4 * (79 * 10 + 130) + 1] << endl;
        // cout << (int)image.GetPixels()[4 * (79 * 10 + 130) + 2] << endl;

        cout << "width: " << image.GetMetadata().width << ", ";
        cout << "height: " << image.GetMetadata().height << endl;


        Check(hr);
        textureList[file] = temp;
        return temp;
    }
    //������ �Ҵ���ִ� �ؽ��ĸ� ��ȯ
    return iter->second;
}

bool Texture::DeleteTexture(wstring file)
{
    auto iter = textureList.find(file);

    //�ߺ��Ȱ� ����.
    if (iter == textureList.end())
    {
        return false;
    }
    //first�� Ű, second ���
    iter->second->Release();

    //�ʿ����� ����
    textureList.erase(iter);

    return true;
}

ScratchImage* Texture::GetTexture(wstring file)
{
    ID3D11ShaderResourceView* temp;
    wstring path = L"../Contents/Images/" + file;

    ScratchImage* image = new ScratchImage();
    LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, *image);

    return image;
}