#pragma once
class Random : public Singleton<Random>
{
private:
	default_random_engine* randomEngine;

public:
	Random();
	~Random();
	// �޸� �ּ� �ּ� ���� 4����Ʈ. CPU�� 4����Ʈ�� �д´�.
	int Int(int min = 0, int max = 1);
	float Float(float min = 0.0f, float max = 1.0f);
};

