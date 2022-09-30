#pragma once

// CRTP 패턴 이용. strip 타입에 따른 vertex 개수 설정할 수 있게 함
// 1. 각 하위 클래스가 다른 값을 가지나 호출하는 이름은 같게.
// 2. static멤버함수, 비 static멤버함수에서 모두 사용 가능하게.
template<typename T>
struct StaticVertexCount
{
	static int& Trianglestrip()
	{
		static int vertexCount;
		return vertexCount;
	}
	static int& Linestrip()
	{
		static int vertexCount;
		return vertexCount;
	}
};

enum class ZOrder
{
	none,
	shadow,
	weapon,
	object,
	bullet,
	effect,
	UI,
};

class ObLine;
enum class Space
{
	world,
	screen, // 가운데가 0,0인
};
enum class Collider
{
	none,
	line,
	triangle,
	rect,
	circle, // 가운데가 0,0인
	star
};
class GameObject
{
	//static member
private:
	static ID3D11Buffer*	WVPBuffer;
	static ID3D11Buffer*	colorBuffer;
	static ObLine*			axisObject;

protected:
	static Shader*			basicShader;
	static Shader*			imageShader;
	static Shader*			tileMapShader;

	//static member function
public:
	static void CreateStaticMember();
	static void DeleteStaticMember();

	//member
private:
	Matrix		S, R, T, R2, RT, Pi, WVP;
	Matrix*		P;
	Vector2		position;

protected:
	Matrix		W;

public:
	bool        isVisible;
	bool        isFilled;
	Vector2		pivot;
	Vector2		scale;
	float		rotation;
	float		rotation2;
	Matrix		RX;
	Matrix		RY;
	float		rotationX;
	float		rotationY;
	bool		isAxis;
	Color       color;
	Space		space;
	Collider	collider;
	bool		colOnOff;
	ZOrder		zOrder;

	//member function
public:
	GameObject();
	virtual ~GameObject() {};

	virtual void Update();
	virtual void Render();
	ColPos Intersect(Vector2 coord);
	ColPos Intersect(GameObject* ob);
	ColPos IntersectScreenMouse(Vector2 coord);

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

