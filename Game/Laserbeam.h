#pragma once
class Attachments;
class Player;

class Laserbeam : public IGameObject
{
public:
	Laserbeam();
	~Laserbeam();
	bool Start();
	void Update();

	Player* m_Player = nullptr;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_LaserPos = CVector3::Zero;	
	CVector3 m_moveSpeed = CVector3::Zero;	
	int m_timer = 0;					
	const CVector3& GetPosition() const
	{
		return m_LaserPos;
	}
};

