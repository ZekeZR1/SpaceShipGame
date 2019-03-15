#pragma once
class minusObj;
class ClearState;

class minusGenerator :public IGameObject
{
public:
	minusGenerator();
	~minusGenerator();
	bool Start();
	void Update();
	minusObj* minusO = nullptr;
	minusObj* minusO1 = nullptr;
	int m_timer = 0;
	ClearState* m_cstate = nullptr;
};

