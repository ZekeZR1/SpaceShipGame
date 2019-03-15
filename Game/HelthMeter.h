#pragma once
class Player;
class minusObj;
class HelthMeter : public IGameObject
{
public:
	HelthMeter();
	~HelthMeter();
	bool Start();
	void Update();
	void LimitMeter();
	prefab::CSpriteRender* m_spriteRender = nullptr;
	Player* m_player = nullptr;
	minusObj* m_minus = nullptr;
	CQuaternion rotation = CQuaternion::Identity;
	double rot = 0.0f;
};

