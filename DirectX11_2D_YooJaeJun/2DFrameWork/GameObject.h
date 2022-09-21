#pragma once
class ObLine;
enum class SPACE
{
	WORLD,
	SCREEN, // 가운데가 0,0인
};
enum class COLLIDER
{
	NONE,
	LINE,
	TRIANGLE,
	RECT,
	CIRCLE, // 가운데가 0,0인
	STAR
};
class GameObject
{
	//static member
private:
	static ID3D11Buffer*	WVPBuffer;
	static ID3D11Buffer*	colorBuffer;

protected:
	static Shader*			basicShader;
	static Shader*			imageShader;

	//static member function
public:
	static void CreateStaticMember();
	static void DeleteStaticMember();

	//member
private:
	Matrix		S, R, T, R2, RT, Pi, WVP;
	Matrix*		P;
	Vector2		position;
	static ObLine* axisObject;

protected:
	Matrix		W;

public:
	Vector2		pivot;
	Vector2		scale;
	float		rotation;
	float		rotation2;
	bool		isAxis;
	bool        isVisible;
	bool        isFilled;
	Color       color;

	SPACE		space;
	COLLIDER	collider;
	bool		colOnOff;

	Matrix		RX, RY;
	float		rotationX;
	float		rotationY;

	//member function
public:
	GameObject();
	virtual ~GameObject() {};

	virtual void Update();
	virtual void Render();
	colPos Intersect(Vector2 coord);
	colPos Intersect(GameObject* ob);
	colPos IntersectScreenMouse(Vector2 coord);

	//getter setter
public:
	//위치 받아오기
	Vector2 GetLocalPos()	{ return position;}
	Vector2 GetWorldPos()	{ 
		return Vector2(RT._41, RT._42); 
	}
	Vector2 GetWorldPivot() { return Vector2(W._41, W._42); }
	//위치를 고정할때 =
	void	SetLocalPos(Vector2 location)	{ position = location; }
	void	SetLocalPosX(float lcationX)	{ position.x = lcationX; }
	void	SetLocalPosY(float lcationY)	{ position.y = lcationY; }
	void	SetWorldPos(Vector2 worldPos);
	void	SetWorldPosX(float worldPosX);
	void	SetWorldPosY(float worldPosY);
	//이동시킬때 +=
	void	MoveLocalPos(Vector2 Velocity)	{ position += Velocity; }
	void	MoveWorldPos(Vector2 Velocity);
	//월드기준 방향
	Vector2 GetRight()	{ return Vector2(RT._11, RT._12); }
	Vector2 GetUp()		{ return Vector2(RT._21, RT._22); }
	//부모행렬 만들기
	void	SetParentRT(GameObject& src)	{ P = &src.RT; }
	void	SetParentT(GameObject& src)	{ P = &src.T; }
};

