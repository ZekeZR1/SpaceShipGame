#pragma once
class BackGround;
class ClearState;
class BackGenerator : public IGameObject
{
public:
	BackGenerator();
	~BackGenerator();
	bool Start();
	void Update();

	int m_timer = 69;
	CVector3 m_firstBackpos;
	BackGround* m_back = nullptr;
	BackGround* backg = nullptr;
	CVector3 m_backpos = CVector3::Zero;
	BackGround* backg1 = nullptr;
	CVector3 m_backpos1 = CVector3::Zero;
	BackGround* backg2 = nullptr;
	CVector3 m_backpos2 = CVector3::Zero;
	ClearState* m_cstate = nullptr;
};

