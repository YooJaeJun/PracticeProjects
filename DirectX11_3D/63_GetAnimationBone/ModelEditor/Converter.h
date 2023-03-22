#pragma once

class Converter
{
public:
	Converter();
	~Converter();

	void ReadFile(wstring file);

public:
	void ExportMesh(wstring savePath);

private:
	void ReadBoneData(aiNode* node, int index, int parent);
	void ReadMeshData(aiNode* node, int bone);
	void ReadSkinData();
	void WriteMeshData(wstring savePath);

public:
	void ExportMaterial(wstring savePath, bool bOverwrite = true);

private:
	void ReadMaterialData();
	void WriteMaterialData(wstring savePath);
	string WriteTexture(string saveFolder, string file);

public:
	void ClipList(vector<wstring>* list);
	void ExportAnimClip(UINT index, wstring savePath);

private:
	struct asClip* ReadClipData(aiAnimation* animation);
	void ReadKeyframeData(struct asClip* clip, aiNode* node, vector<struct asClipNode>& aiNodeInfos);
	void WriteClipData(struct asClip* clip, wstring savePath);

private:
	wstring file;

	Assimp::Importer* importer;
	const aiScene* scene;

	vector<struct asBone *> bones;
	vector<struct asMesh *> meshes;
	vector<struct asMaterial *> materials;
};