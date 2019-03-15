#pragma once
#include "tkEngine/camera/tkSpringCamera.h"


class ShipState;
class ClearState;
class Fade;

class ShipCustomizeScene : public IGameObject
{
public:
	ShipCustomizeScene();
	~ShipCustomizeScene();
	bool Start();
	void Update();


	//ÉâÉCÉg
	prefab::CPointLight* ptLight;
	CVector3 ptLpos = CVector3::Zero;
	CVector3 attn = CVector3::Zero;

	//ÇŒÇÀÉJÉÅÉâ
	CVector3 m_toCameraPos;	
	CSpringCamera m_springCamera; 
	//BGM
	prefab::CSoundSource* m_bgm = nullptr;
	float m_intiBgmVolume = 0.0f;
	//Ship
	prefab::CSkinModelRender* m_ShipModel = nullptr;
	CVector3 m_ShipPos = CVector3::Zero;
	CVector3 m_ShipScale = { 1.0f,1.0f,1.0f };
	CQuaternion m_ShipRot = CQuaternion::Identity;
	//BackGround
	float rr = 0.0f;
	prefab::CSkinModelRender* m_BackGround = nullptr;
	CVector3 m_BackPos = CVector3::Zero;
	CVector3 m_BackScale = { 1.0f,1.0f,1.0f };
	CQuaternion m_BackRot = CQuaternion::Identity;
	//Attachment1 Model
	prefab::CSkinModelRender* Attachment1 = nullptr;
	CVector3 A1Pos = CVector3::Zero;
	CVector3 A1Scale = { 1.0f,1.0f,1.0f };
	CQuaternion A1Rot = CQuaternion::Identity;
	//A2
	prefab::CSkinModelRender* Attachment2 = nullptr;
	CVector3 A2Pos = CVector3::Zero;
	CVector3 A2Scale = { 1.0f,1.0f,1.0f };
	CQuaternion A2Rot = CQuaternion::Identity;
	//A3
	prefab::CSkinModelRender* Attachment3 = nullptr;
	CVector3 A3Pos = CVector3::Zero;
	CVector3 A3Scale = { 1.0f,1.0f,1.0f };
	CQuaternion A3Rot = CQuaternion::Identity;
	//Sprite
	prefab::CSpriteRender* m_Atch01Sprite = nullptr;
	CVector3 Atch01SpritePos = CVector3::Zero;
	prefab::CSpriteRender* m_Atch02Sprite = nullptr;
	CVector3 Atch02SpritePos = CVector3::Zero;
	prefab::CSpriteRender* m_Atch03Sprite = nullptr;
	CVector3 Atch03SpritePos = CVector3::Zero;
	prefab::CSpriteRender* m_NowA1Sprite = nullptr;
	CVector3 m_NowA1SpritePos = CVector3::Zero;
	prefab::CSpriteRender* m_NowA2Sprite = nullptr;
	CVector3 m_NowA2SpritePos = CVector3::Zero;
	prefab::CSpriteRender* m_NowA3Sprite = nullptr;
	CVector3 m_NowA3SpritePos = CVector3::Zero;
	prefab::CSpriteRender* m_spriteRender8 = nullptr;
	CVector3 Xpos = CVector3::Zero;
	prefab::CSpriteRender* m_spriteRender9 = nullptr;
	CVector3 Dpos = CVector3::Zero;
	prefab::CSpriteRender* m_InfoSprite = nullptr;
	CVector3 m_InfoPos = CVector3::Zero;
	int Line = 0;
	prefab::CSpriteRender* m_lineSprite = nullptr;
	CVector3 m_linePos = CVector3::Zero;
	prefab::CSpriteRender* m_BackSprite = nullptr;
	CVector3 BackSpritePos = CVector3::Zero;
	prefab::CSpriteRender* m_BackSprite2 = nullptr;
	CVector3 BackSpritePos2 = CVector3::Zero;
	//
	prefab::CSpriteRender* m_UsingSprite1 = nullptr;
	CVector3 UsingSpritePos1 = CVector3::Zero;
	prefab::CSpriteRender* m_UsingSprite2 = nullptr;
	CVector3 UsingSpritePos2 = CVector3::Zero;
	prefab::CSpriteRender* m_UsingSprite3 = nullptr;
	CVector3 UsingSpritePos3 = CVector3::Zero;

	float m_waitTimer = 0.0f;
	Fade* m_fade = nullptr;
	enum  EnState {
		enState_FadeIn,
		enState_InGame,
	};
	EnState m_state = enState_FadeIn;
	bool m_isWaitFadeout = false;
	bool m_isWaitFadeout2 = false;

	ShipState* m_ShipState = nullptr;
	ClearState* m_cstate = nullptr;
};

