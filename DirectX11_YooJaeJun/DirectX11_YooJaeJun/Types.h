#pragma once

class Scene	// �������̽� - ���������Լ� Ŭ���� - �߻�Ŭ����
{
public:
	virtual ~Scene() {};

	// ���� ���� �Լ� = 0

	// �� �ʱ�ȭ
	virtual void Init() = 0;
	// �� ����
	virtual void Update() = 0;
	// �� ���
	virtual void Render() = 0;
};


template<typename T>
class Singleton
{
public:
	virtual ~Singleton() {}
	static T* GetInstance() 
	{
		static T* Instance = new T;
		return Instance;
	}
	void DeleteSingleton()
	{
		delete GetInstance;
	}
};
