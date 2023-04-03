#include "stdafx.h"
#include "Main.h"
#include "Systems/Window.h"

#include "GetMultiBoneDemo.h"
#include "ObbCollisionDemo.h"
#include "ObbRaycastDemo.h"
#include "GetRaycastDemo.h"
#include "ProjectionDemo.h"
#include "ViewportDemo.h"
#include "GetAnimationBoneDemo.h"
#include "InstancingFrameworkDemo.h"
#include "TextureBufferDemo.h"
#include "RawBufferDemo.h"
#include "ThreadDemo.h"
#include "InstancingDemo.h"
#include "CubeSkyDemo.h"
#include "MeshDemo.h"
#include "GetVerticalRaycast.h"
#include "GetHeightDemo.h"
#include "NormalVectorDemo.h"
#include "HeightMapDemo.h"
#include "TextureSamplerDemo.h"
#include "TextureLoadDemo.h"
#include "TextureDemo.h"
#include "RotationDemo.h"
#include "CubeDemo.h"
#include "GridDemo.h"
#include "IndexDemo.h"
#include "WorldDemo3.h"
#include "WorldDemo2.h"
#include "WorldDemo.h"
#include "UserInterfaceDemo.h"
#include "RectDemo.h"
#include "TriangleList.h"
#include "Vertex_Line2.h"
#include "Vertex_Line.h"  

void Main::Initialize()
{
	Push(new GetMultiBoneDemo());
	//Push(new ObbCollisionDemo());
	//Push(new ObbRaycastDemo());
	//Push(new GetRaycastDemo());
	//Push(new ProjectionDemo());
	//Push(new ViewportDemo());
	//Push(new GetAnimationBoneDemo());
	//Push(new InstancingFrameworkDemo());
	//Push(new TextureBufferDemo());
	//Push(new ThreadDemo());
	//Push(new InstancingDemo());
	//Push(new CubeSkyDemo());
	//Push(new MeshDemo());
	//Push(new GetVerticalRaycast());
	//Push(new GetHeightDemo());
	//Push(new NormalVectorDemo());
	//Push(new HeightMapDemo());
	//Push(new TextureSamplerDemo());
	//Push(new TextureLoadDemo());
	//Push(new TextureDemo());
	//Push(new RotationDemo());
	//Push(new CubeDemo());
	//Push(new GridDemo());
	//Push(new IndexDemo());
	//Push(new WorldDemo3());
	//Push(new WorldDemo2());
	//Push(new WorldDemo());
	//Push(new UserInterfaceDemo());
	//Push(new RectDemo());
	//Push(new TriangleList());
	//Push(new Vertex_Line2());
	//Push(new Vertex_Line());
}

void Main::Ready()
{

}

void Main::Destroy()
{
	for (IExecute* exe : executes)
	{
		exe->Destroy();
		SafeDelete(exe);
	}
}

void Main::Update()
{
	for (IExecute* exe : executes)
		exe->Update();
}

void Main::PreRender()
{
	for (IExecute* exe : executes)
		exe->PreRender();
}

void Main::Render()
{
	for (IExecute* exe : executes)
		exe->Render();
}

void Main::PostRender()
{
	for (IExecute* exe : executes)
		exe->PostRender();
}

void Main::ResizeScreen()
{
	for (IExecute* exe : executes)
		exe->ResizeScreen();
}

void Main::Push(IExecute * execute)
{
	executes.push_back(execute);

	execute->Initialize();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	D3DDesc desc;
	desc.AppName = L"D3D Game";
	desc.Instance = instance;
	desc.bFullScreen = false;
	desc.bVsync = false;
	desc.Handle = NULL;
	desc.Width = 1280;
	desc.Height = 720;
	desc.Background = Color(0.3f, 0.3f, 0.3f, 1.0f);
	D3D::SetDesc(desc);

	Main* main = new Main();
	WPARAM wParam = Window::Run(main);

	SafeDelete(main);

	return wParam;
}