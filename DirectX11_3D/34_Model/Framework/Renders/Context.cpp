#include "Framework.h"
#include "Context.h"
#include "Viewer/Viewport.h"
#include "Viewer/Perspective.h"
#include "Viewer/Freedom.h"

Context* Context::instance = NULL;

Context * Context::Get()
{
	//assert(instance != NULL);

	return instance;
}

void Context::Create()
{
	assert(instance == NULL);

	instance = new Context();
}

void Context::Delete()
{
	SafeDelete(instance);
}

Context::Context()
{
	D3DDesc desc = D3D::GetDesc();

	perspective = new Perspective(desc.Width, desc.Height);
	viewport = new Viewport(desc.Width, desc.Height);
	camera = new Freedom();
}

Context::~Context()
{
	SafeDelete(perspective);
	SafeDelete(viewport);
	SafeDelete(camera);
}

void Context::ResizeScreen()
{
	perspective->Set(D3D::Width(), D3D::Height());
	viewport->Set(D3D::Width(), D3D::Height());
}

void Context::Update()
{
	camera->Update();
}

void Context::Render()
{
	viewport->RSSetViewport();

	
	string str = string("FrameRate : ") + to_string(ImGui::GetIO().Framerate);
	Gui::Get()->RenderText(5, 5, 1, 1, 1, str);

	Vector3 R;
	camera->RotationDegree(&R);

	Vector3 P;
	camera->Position(&P);

	str = "Camera Rotation : ";
	str += to_string((int)R.x) + ", " + to_string((int)R.y) + ", " + to_string((int)R.z);
	Gui::Get()->RenderText(5, 20, 1, 1, 1, str);

	str = "Camera Position : ";
	str += to_string((int)P.x) + ", " + to_string((int)P.y) + ", " + to_string((int)P.z);
	Gui::Get()->RenderText(5, 35, 1, 1, 1, str);
}

Matrix Context::View()
{
	Matrix view;
	camera->GetMatrix(&view);

	return view;
}

D3DXMATRIX Context::Projection()
{
	Matrix projection;
	perspective->GetMatrix(&projection);

	return projection;
}
