#pragma once

class Main : public Scene
{
private:
	ObImage*			mole;
	int					puzzleNum;
	vector<ObImage*>	puzzles;
	vector<Vector4>		randUv;
	vector<Vector4>		originUv;
	int					empty;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void SetPuzzle();
	void Shuffle();
};
