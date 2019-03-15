#pragma once
class Player;
class plusGenerator;
class HelthMeter;
class ClearState;

class plusObj : public IGameObject
{
public:
	plusObj();
	~plusObj();
	bool Start();
	void Update();

	CQuaternion qRot;
	float rr = 0.0f;
	int m_timer = 0;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 pos = CVector3::Zero;
	Player* player = nullptr;
	ClearState* m_cstate = nullptr;
};

