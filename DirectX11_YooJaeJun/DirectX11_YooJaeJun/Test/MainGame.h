#pragma once

class MainGame : public Scene
{
public:
	~MainGame();

	void Init()   override;
	void Update() override;
	void Render() override;
};

