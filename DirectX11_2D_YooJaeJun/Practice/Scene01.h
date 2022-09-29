#pragma once
class Scene01 : public Scene
{
public:
	Player* pl;

public:
	Scene01();
	~Scene01();

	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

