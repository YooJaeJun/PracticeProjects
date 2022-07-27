#pragma once
// #define mode_basicShape
// #define mode_shapeDrawing
// #define mode_clock
// #define mode_axis
#define mode_bulletStorm

class Enemy;
class Bullet;

class MainGame : public Scene
{
private:
#ifdef mode_basicShape
	ObRect rc;
	ObStar st;
	ObCircle cc;
#endif
#ifdef mode_shapeDrawing
	float posX = 230.0f;
	float posY = 200.0f;
	float scaleX = 0.7f;
	float scaleY = 0.7f;
	float seta = 1.0f;
	float posHumanX = 500;
	float posHumanY = 400;
	float R = ToRadian;
#endif
#ifdef mode_clock
	ObLine lnHour;
	ObLine lnMinute;
	ObLine lnSecond;
	SYSTEMTIME localTime;
#endif
#ifdef mode_axis
	const int planetNum = 11;
	ObCircle planet[11];
#endif
#ifdef mode_bulletStorm
	const int bulletNum = 60;
	shared_ptr<Enemy> enemy;
	vector<shared_ptr<Bullet>> bullet;
	bool qState = false, eState = false;
	ObLine line;

#endif

public:
	~MainGame();

	void Init()   override;
	void Update() override;
	void Render() override;
};