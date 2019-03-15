#pragma once
class ClearState;
class Notify : public IGameObject
{
public:
	Notify();
	~Notify();
	bool Start();
	void NotifyLaser();

	ClearState* m_cstate = nullptr;
	prefab::CSpriteRender* m_spriteRender = nullptr;
	CVector3 m_pos = CVector3::Zero;
};

