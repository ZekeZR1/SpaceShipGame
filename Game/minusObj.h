#pragma once
class Player;
class minusGenerator;
class HelthMeter;
class Laserbeam;
class ClearState;
class ShipState;

class minusObj : public IGameObject
{
public:
	minusObj();
	~minusObj();
	//bool Start() override;
	bool Start();
	//void Update()override;
	void Update();
	
	int m_timer = 0;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 pos = CVector3::Zero;
	CVector3 spawnPos = CVector3::Zero;
	CVector3 moveSpeed = CVector3::Zero;
	Player* m_player = nullptr;
	Laserbeam* m_laserbeam = nullptr;
	HelthMeter* m_helthm = nullptr;
	ClearState* m_cstate = nullptr;
	ShipState* m_ShipState = nullptr;
	//CPhysicsStaticObject m_phyStaticObject;
};

