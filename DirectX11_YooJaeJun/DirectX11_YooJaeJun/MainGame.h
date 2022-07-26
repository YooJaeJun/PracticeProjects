#pragma once
// #define mode_basicShape
// #define mode_clock
#define mode_axis

class MainGame : public Scene
{
private:
	ObRect rc;
	ObStar st;
	ObCircle cc;
	const int planetNum = 11;
	ObCircle planet[11];
#ifdef mode_clock
	ObLine lnHour;
	ObLine lnMinute;
	ObLine lnSecond;
	SYSTEMTIME localTime;
#endif

public:
	~MainGame();

	void Init()   override;
	void Update() override;
	void Render() override;
};