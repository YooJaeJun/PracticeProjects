#pragma once

class MainGame : public Scene
{
private:
	ObRect rc;
	ObStar st;
	ObCircle cc;

public:
	~MainGame();

	void Init()   override;
	void Update() override;
	void Render() override;
};

