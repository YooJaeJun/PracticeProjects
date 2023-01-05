#include "Framework.h"

void Direct3D11::Create()
{
	//EnumerateAdapters
	{
		//IDXGIFactory1 DXGI ��ü�� �����ϱ� ���� �޼ҵ带 ����
		IDXGIFactory1* factory;
		FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory));

		UINT index = 0;
		while (true)
		{
			//��͵��� ��Ƶ� ������
			IDXGIAdapter1* adapter;
			//IDXGIFactory1 ��ü�� ���� ��͸� ����
			HRESULT hr = factory->EnumAdapters1(index, &adapter);

			//���� index�� �ý��ۿ� �����ϴ� ����� ������ ���ų� �� ũ�ٸ� ����
			if (hr == DXGI_ERROR_NOT_FOUND)
				break;

			Check(hr);

			//���� �־�� ��͵��� ������ ����ü�� ���� �ִ� ����
			D3DEnumAdapterInfo* adapterInfo = new D3DEnumAdapterInfo();
			ZeroMemory(adapterInfo, sizeof(D3DEnumAdapterInfo));
			adapterInfo->adapterOrdinal = index;
			adapter->GetDesc1(&adapterInfo->adapterDesc);
			adapterInfo->adapter = adapter;

			IDXGIOutput* output = NULL;

			hr = adapterInfo->adapter->EnumOutputs(0, &output);
			if (DXGI_ERROR_NOT_FOUND == hr)
				break;

			D3DEnumOutputInfo* outputInfo = new D3DEnumOutputInfo();
			ZeroMemory(outputInfo, sizeof(D3DEnumOutputInfo));

			hr = output->GetDesc(&outputInfo->outputDesc);
			Check(hr);

			outputInfo->output = output;

			UINT num_modes = 0;
			//���÷��� ���
			DXGI_MODE_DESC* displayModes = nullptr;
			//���ĸ� �����Ͽ� ä�δ� 8��Ʈ�� �����ϴ� 4����, 32��Ʈ ��ȣ ���� ����ȭ ���� ����.
			DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

			//��û�� ���� �� ��Ÿ �Է� �ɼǰ� ��ġ�ϴ� ǥ�� ��带 ������
			hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &num_modes, nullptr); // ��� ���� ��������
			//DXGI_ENUM_MODES_INTERLACED INTERLACE��� : ��ü �̹����� ���� �� �纻�� �� �� �ֵ��� ��Ʈ �� �̹����� ���ڵ��ϴ� ���
			Check(hr);

			displayModes = new DXGI_MODE_DESC[num_modes];
			hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &num_modes, displayModes); // ���÷��� ��� ��������
			Check(hr);

			for (UINT i = 0; i < num_modes; i++)
			{
				bool isCheck = true;
				isCheck &= displayModes[i].Width == app.width;
				isCheck &= displayModes[i].Height == app.height;

				if (isCheck == true)
				{
					//										ȭ�� �ֻ���
					outputInfo->numerator = displayModes[i].RefreshRate.Numerator;
					outputInfo->denominator = displayModes[i].RefreshRate.Denominator;
				}
			}

			adapterInfo->outputInfo = outputInfo;

			SafeDeleteArray(displayModes);

			adapterInfos.push_back(adapterInfo);

			index++;
		}
		SafeRelease(factory);
	}

	//CreateSwapChainAndDevice
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = 0;
		swapChainDesc.BufferDesc.Height = 0;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		if (app.vSync == true)
		{
			//�󵵼� �����?						����
			swapChainDesc.BufferDesc.RefreshRate.Numerator = adapterInfos[0]->outputInfo->numerator;
			//									�и�
			swapChainDesc.BufferDesc.RefreshRate.Denominator = adapterInfos[0]->outputInfo->denominator;
		}
		else
		{
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		}

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = app.handle;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = !app.fullScreen;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;

		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
//#if defined(_DEBUG)
//		creationFlags = D3DCOMPILE_PREFER_FLOW_CONTROL | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
//#endif
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
		};

		UINT maxVideoMemory = 0;
		int selectedAdapterIndex = -1;
		for (UINT i = 0; i < adapterInfos.size(); ++i)
		{
			if (adapterInfos[i]->adapterDesc.DedicatedVideoMemory > maxVideoMemory)
			{
				selectedAdapterIndex = i;
				maxVideoMemory = (UINT)adapterInfos[i]->adapterDesc.DedicatedVideoMemory;
			}
		}

		numerator = adapterInfos[0]->outputInfo->numerator;
		denominator = adapterInfos[0]->outputInfo->denominator;

		HRESULT hr = D3D11CreateDeviceAndSwapChain
		(
			adapterInfos[selectedAdapterIndex]->adapter
			, D3D_DRIVER_TYPE_UNKNOWN
			, NULL
			, creationFlags
			, featureLevels
			, 1
			, D3D11_SDK_VERSION
			, &swapChainDesc
			, &swapChain
			, &device
			, NULL
			, &deviceContext
		);
		assert(SUCCEEDED(hr));
	}

	CreateBackBuffer(app.width, app.height);

	//����������� ����
	//Disable DepthStencil
	{ 
		ID3D11DepthStencilState* depthStencilState;
		D3D11_DEPTH_STENCIL_DESC desc = { 0 };
		desc.DepthEnable = false;
		desc.StencilEnable = false;
		device->CreateDepthStencilState(&desc, &depthStencilState);
		//���ε�
		deviceContext->OMSetDepthStencilState(depthStencilState, 0xFF);
	}
	//CullNone, FillSolid
	{
		ID3D11RasterizerState* rasterizerState;
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_NONE; 
		desc.DepthBias = 0;
		desc.FrontCounterClockwise = false; 
		desc.DepthBiasClamp = 0;
		desc.SlopeScaledDepthBias = 0;
		desc.DepthClipEnable = false;
		desc.ScissorEnable = false; 
		desc.MultisampleEnable = false; 
		desc.AntialiasedLineEnable = false; 
		device->CreateRasterizerState(&desc, &rasterizerState);
		deviceContext->RSSetState(rasterizerState);
		rasterizerState->Release();
	}
	//���İ� ó��
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		desc.RenderTarget[0].BlendEnable = true;
		//rgb
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; //1 - 0.3 -> 0.7
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // 0.3
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;// 0.7 * dest + 0.3 * src
		//a
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE; // 1
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO; // 0
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD; // 0 + 1
		device->CreateBlendState(&desc, &blendState);
		deviceContext->OMSetBlendState(blendState, NULL, 0xFF);
	}
	isCreated = true;
}

Direct3D11::Direct3D11()
:numerator(0), denominator(1), isCreated(0), backBuffer(nullptr), device(nullptr)
,deviceContext(nullptr),renderTargetView(nullptr),swapChain(nullptr)
{

}

Direct3D11::~Direct3D11()
{
	DeleteBackBuffer();

	if (swapChain != nullptr)
		swapChain->SetFullscreenState(false, NULL);

	SafeRelease(deviceContext);
	SafeRelease(device);
	SafeRelease(swapChain);
}

void Direct3D11::SetRenderTarget(ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
	if (rtv == nullptr)
		rtv = renderTargetView;

	//if (dsv == nullptr)
	//	dsv = depthStencilView;

	deviceContext->OMSetRenderTargets(1, &rtv, nullptr);
}

void Direct3D11::Clear(Color color, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
	if (rtv == nullptr)
		rtv = renderTargetView;

	//if (dsv == nullptr)
	//	dsv = depthStencilView;

	deviceContext->ClearRenderTargetView(rtv, color);
	//deviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
}

void Direct3D11::Present()
{
	swapChain->Present(app.vSync == true ? 1 : 0, 0);
}

void Direct3D11::ResizeScreen(float width, float height)
{
	if (width < 1 || height < 1)
		return;

	app.width = width;
	app.height = height;

	DWRITE->DeleteBackBuffer();
	DeleteBackBuffer();
	{
		HRESULT hr = swapChain->ResizeBuffers(0, (UINT)width, (UINT)height, DXGI_FORMAT_UNKNOWN, 0);
		assert(SUCCEEDED(hr));
	}
	CreateBackBuffer(width, height);
	DWRITE->CreateBackBuffer(width, height);
}

void Direct3D11::CreateBackBuffer(float width, float height)
{
	HRESULT hr;

	//Create RTV - System BackBuffer
	{
		ID3D11Texture2D* backbufferPointer;
		hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbufferPointer);
		Check(hr)

			hr = device->CreateRenderTargetView(backbufferPointer, NULL, &renderTargetView);
		Check(hr)

			SafeRelease(backbufferPointer);
	}
}

void Direct3D11::DeleteBackBuffer()
{
	//SafeRelease(depthStencilView);
	SafeRelease(renderTargetView);
	SafeRelease(backBuffer);
}

D3DEnumAdapterInfo::D3DEnumAdapterInfo()
	: adapter(nullptr), outputInfo(nullptr)
{
}

D3DEnumAdapterInfo::~D3DEnumAdapterInfo()
{
	SafeRelease(adapter);
	SafeDelete(outputInfo);
}


D3DEnumOutputInfo::D3DEnumOutputInfo()
	: output(nullptr), numerator(0), denominator(1)
{
}

D3DEnumOutputInfo::~D3DEnumOutputInfo()
{
	SafeRelease(output);
}