#pragma once
class Main : public Scene
{
private:
	ObImage* bg; //완성본
	ObImage*** puzzle;
	int				puzzleNum;

	Int2			zero;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void ShufflePuzzle();
	void CompletePuzzle();
	void CreatePuzzle();
	void DeletePuzzle();
};
