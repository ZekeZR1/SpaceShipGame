#pragma once
class ShipState;
class Player;
class Attachments : public IGameObject	
{
public:
	Attachments();
	~Attachments();
	bool Start();
	void Update();

	ShipState* m_ShipState = nullptr;
	Player* m_Player = nullptr;
	//Attachment1 Model
	prefab::CSkinModelRender* Attachment1 = nullptr;
	CVector3 A1Pos = CVector3::Zero;
	CVector3 setA1Pos = CVector3::Zero;
	CVector3 A1Scale = { 1.0f,1.0f,1.0f };
	CQuaternion A1Rot = CQuaternion::Identity;
	//A2
	prefab::CSkinModelRender* Attachment2 = nullptr;
	CVector3 A2Pos = CVector3::Zero;
	CVector3 setA2Pos = CVector3::Zero;
	CVector3 A2Scale = { 1.0f,1.0f,1.0f };
	CQuaternion A2Rot = CQuaternion::Identity;
	//A3
	prefab::CSkinModelRender* Attachment3 = nullptr;
	CVector3 A3Pos = CVector3::Zero;
	CVector3 setA3Pos = CVector3::Zero;
	CVector3 A3Scale = { 1.0f,1.0f,1.0f };
	CQuaternion A3Rot = CQuaternion::Identity;

	enum SState {
		IN_GAME,
		IN_MAP,
		IN_GAMECLEAR,
		IN_GAMEOVER,
	};
};

