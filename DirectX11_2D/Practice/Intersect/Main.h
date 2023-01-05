#pragma once

class Main : public Scene
{
private:
	ObLine* l1;
	ObLine* l2;
	ObRect* rc;
	ObCircle* cc;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
