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
