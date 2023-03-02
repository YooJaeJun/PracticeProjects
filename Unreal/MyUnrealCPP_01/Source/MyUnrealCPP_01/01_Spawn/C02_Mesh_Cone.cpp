// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Spawn/C02_Mesh_Cone.h"
#include "Global.h"

AC02_Mesh_Cone::AC02_Mesh_Cone()
{
	UStaticMesh* mesh = nullptr;
	CHelpers::GetAsset<UStaticMesh>(&mesh, TEXT("StaticMesh'/Game/Meshes/Cone.Cone'"));
	Mesh->SetStaticMesh(mesh);
}