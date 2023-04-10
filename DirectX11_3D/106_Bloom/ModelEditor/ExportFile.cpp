#include "stdafx.h"
#include "ExportFile.h"
#include "Converter.h"

void ExportFile::Initialize()
{
	//Airplane();
	//Tower();
	//Tank();
	//Kachujin();
	//Weapon();
}

void ExportFile::Airplane()
{
	Converter* conv = new Converter();
	conv->ReadFile(L"B787/Airplane.fbx");
	conv->ExportMesh(L"B787/Airplane");
	conv->ExportMaterial(L"B787/Airplane");
	SafeDelete(conv);
}

void ExportFile::Tower()
{
	Converter* conv = new Converter();
	conv->ReadFile(L"Tower/Tower.fbx");
	conv->ExportMesh(L"Tower/Tower");
	conv->ExportMaterial(L"Tower/Tower");
	SafeDelete(conv);
}

void ExportFile::Tank()
{
	Converter* conv = new Converter();
	conv->ReadFile(L"Tank/Tank.fbx");
	conv->ExportMesh(L"Tank/Tank");
	conv->ExportMaterial(L"Tank/Tank", false);
	SafeDelete(conv);
}

void ExportFile::Kachujin()
{
	Converter* conv = NULL;

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Mesh.fbx");
	conv->ExportMesh(L"Kachujin/Mesh");
	conv->ExportMaterial(L"Kachujin/Mesh");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Sword And Shield Idle.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Sword And Shield Idle");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Sword And Shield Walk.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Sword And Shield Walk");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Sword And Shield Run.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Sword And Shield Run");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Sword And Shield Slash.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Sword And Shield Slash");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Salsa Dancing.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Salsa Dancing");
	SafeDelete(conv);

	//vector<wstring> clipNames;
	//conv->ClipList(&clipNames);
}

void ExportFile::Weapon()
{
	vector<wstring> names;
	names.push_back(L"Cutter.fbx");
	names.push_back(L"Cutter2.fbx");
	names.push_back(L"Dagger_epic.fbx");
	names.push_back(L"Dagger_small.fbx");
	names.push_back(L"Katana.fbx");
	names.push_back(L"LongArrow.obj");
	names.push_back(L"LongBow.obj");
	names.push_back(L"Rapier.fbx");
	names.push_back(L"Sword.fbx");
	names.push_back(L"Sword2.fbx");
	names.push_back(L"Sword_epic.fbx");

	for (wstring name : names)
	{
		Converter* conv = new Converter();
		conv->ReadFile(L"Weapon/" + name);


		String::Replace(&name, L".fbx", L"");
		String::Replace(&name, L".obj", L"");

		conv->ExportMaterial(L"Weapon/" + name, false);
		conv->ExportMesh(L"Weapon/" + name);
		SafeDelete(conv);
	}
}
