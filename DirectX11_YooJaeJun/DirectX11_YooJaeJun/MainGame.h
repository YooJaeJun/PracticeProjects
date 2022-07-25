#pragma once

class MainGame : public Scene
{
private:
	ObRect rc;
	ObStar st;
	ObCircle cc1, cc2;
	ObLine lnHour;
	ObLine lnMinute;
	ObLine lnSecond;

	SYSTEMTIME localTime;

public:
	~MainGame();

	void Init()   override;
	void Update() override;
	void Render() override;
};