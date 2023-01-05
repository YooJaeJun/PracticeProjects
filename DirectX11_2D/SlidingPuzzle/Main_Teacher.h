#pragma once
class Main : public Scene
{
private:
	ObImage* bg; //�ϼ���
	ObImage*** puzzle;
	int				puzzleNum;

	Int2			zero;

public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void ShufflePuzzle();
	void CompletePuzzle();
	void CreatePuzzle();
	void DeletePuzzle();
};
