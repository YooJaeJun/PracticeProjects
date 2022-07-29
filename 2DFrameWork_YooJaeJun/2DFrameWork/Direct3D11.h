#pragma once

class Direct3D11 : public Singleton<Direct3D11>
{
private:
	//�������̽�
	//new �� ������ �ȵ� -> �߻�Ŭ����
	//create �Լ��� �̿��ؼ� ������ �ּҸ� �޾ƿ�
	ID3D11Device*						device; //���� ����
	ID3D11DeviceContext*				deviceContext; //������ ���������� ���ε�
	IDXGISwapChain*						swapChain; 
	ID3D11Texture2D*					backBuffer;
	ID3D11RenderTargetView*				renderTargetView;
	ID3D11BlendState *					blendState;
	//ID3D11DepthStencilView*				depthStencilView;

	vector<struct D3DEnumAdapterInfo*>	adapterInfos;
	UINT								numerator;
	UINT								denominator;
	bool								isCreated;

public:
	Direct3D11();
	~Direct3D11();

private:
	void CreateBackBuffer(float width, float height);
	void DeleteBackBuffer();

public:
	void Create();
	void SetRenderTarget(ID3D11RenderTargetView* rtv = nullptr,
		ID3D11DepthStencilView* dsv = nullptr);
	//
	void Clear(Color color = Color(0.7f,0.7f,0.7f,1.0f), ID3D11RenderTargetView* rtv = nullptr, ID3D11DepthStencilView* dsv = nullptr);
	//
	void Present();

	void ResizeScreen(float width, float height);
	
public:
	//Getter
	ID3D11Device*			GetDevice()		{ return device; }
	ID3D11DeviceContext*	GetDC()			{ return deviceContext; }
	IDXGISwapChain*			GetSwapChain()	{ return swapChain; }
	ID3D11RenderTargetView* GetRTV()		{ return renderTargetView; }
	bool					GetCreated()	{ return isCreated; }
	//ID3D11DepthStencilView* GetDSV() { return depthStencilView; }
};

struct D3DEnumOutputInfo
{
	IDXGIOutput*		output; //��� ���
	DXGI_OUTPUT_DESC	outputDesc;
	UINT				numerator;
	UINT				denominator;
	D3DEnumOutputInfo();
	~D3DEnumOutputInfo();
};

struct D3DEnumAdapterInfo
{
	UINT				adapterOrdinal;
	IDXGIAdapter1*		adapter;
	//��� ������ ����ü
	DXGI_ADAPTER_DESC1	adapterDesc;
	D3DEnumOutputInfo*	outputInfo;
	D3DEnumAdapterInfo();
	~D3DEnumAdapterInfo();
};

