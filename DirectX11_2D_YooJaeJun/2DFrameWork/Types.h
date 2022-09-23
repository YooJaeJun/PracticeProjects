#pragma once

struct Int2
{
	int x;
	int y;
	Int2() : x(0), y(0) {}
	Int2(const int x, const int y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(Int2 dest)
	{
		return (x == dest.x && y == dest.y);
	}
	bool operator!=(Int2 dest)
	{
		return (x != dest.x || y != dest.y);
	}
};

// 추가 이유
// 1. 들로네 삼각분할 시 MST 이용 위해 노드 별 간선을 map형태로 저장해야 됨
// 2. map에서 항이 2개 이상인 key 저장 위해선 operator<()가 있어야 함
// 3. 기존 Vector2는 operator<() 가 없어서 저장하지 못해 추가
struct Float2
{
	float x;
	float y;
	Float2() : x(0.0f), y(0.0f) {}
	Float2(const Float2& other) : x(other.x), y(other.y) {}
	Float2(const Vector2& other) : x(other.x), y(other.y) {}
	Float2(const float x, const float y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator<(const Float2& other) const
	{
		return x < other.x || (!(other.x < x) && y < other.y);
	}
	bool operator>(const Float2& other) const
	{
		return x > other.x || (!(other.x > x) && y > other.y);
	}
};

template <typename T>
class Singleton
{
	//static
private:
	static T* instance;

public:
	static T* GetInstance()
	{
		if (!instance)
			instance = new T;

		return instance;
	};

	//member
public:
	virtual ~Singleton() {};
	void DeleteSingleton()
	{
		delete instance;
		instance = nullptr;
	};
};

template <typename T>
T* Singleton<T>::instance = nullptr;
//씬타입으로는 객체를만들수 없다.
class Scene
{
public:
	virtual ~Scene() {};
	//초기화
	virtual void Init() = 0;
	//해제
	virtual void Release() = 0;
	//Loop
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	//Window Resize
	virtual void ResizeScreen() = 0;
};

class Application
{
	friend class Direct3D11;
	friend class Window;
	friend class Gui;

	//getter만 두고 접근가능
private:

	float		x, y;
	float		width;
	float		height;
	HINSTANCE	instance;
	HWND		handle;
	wstring		appName;
	bool		fullScreen;

public:
	bool		vSync;
	Color		background;
	int			fixFrame;
	float		deltaScale;
	float		soundScale;

public:
	Application() :instance(nullptr), handle(nullptr), vSync(false), fullScreen(false)
		, appName(L" "), width(1280.0f), height(720.0f), background(Color(0.7f, 0.7f, 0.7f, 1.0f))
		, fixFrame(200), deltaScale(1.0f), soundScale(1.0f), x(0.0f), y(0.0f) {}
	float	GetWidth() { return width; }
	float	GetHeight() { return height; }
	float	GetHalfWidth() { return width / 2.0f; }
	float	GetHalfHeight() { return height / 2.0f; }
	void	InitWidthHeight(float width, float height) { this->width = width; this->height = height; }

	void	SetInstance(HINSTANCE instance)
	{
		if (!this->instance)
			this->instance = instance;
	}
	void	SetAppName(wstring appName)
	{
		if (this->appName == L" ")
			this->appName = appName;
	}
	//해상도변경은 D3D의 리사이즈 함수 이용!
};