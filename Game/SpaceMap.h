#pragma once
#include "tkEngine/camera/tkSpringCamera.h"

class Earth;
class Mastered;
class Attachments;
class Fade;
class Player;
class ClearState;
class ShipState;

class SpaceMap : public IGameObject
{
public:
	SpaceMap();
	~SpaceMap();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;
	Player* m_player = nullptr;
	Attachments* m_attachments = nullptr;
	int nStage = 0;
	prefab::CSoundSource* m_bgm = nullptr;
	//Planet01
	prefab::CSkinModelRender* m_PlanetModel0 = nullptr;
	CVector3 P0Pos = CVector3::Zero;
	CVector3	P0Scale = { 1.0f, 1.0f, 1.0f };
	CQuaternion P0Rot = CQuaternion::Identity;
	float rr0 = 0.0f;
	//Planet02
	prefab::CSkinModelRender* m_PlanetModel2 = nullptr;
	CVector3 P2Pos = CVector3::Zero;
	CVector3	P2Scale = { 1.0f, 1.0f, 1.0f};
	CQuaternion P2Rot = CQuaternion::Identity;
	//Planet03
	prefab::CSkinModelRender* m_PlanetModel3 = nullptr;
	CVector3 P3Pos = CVector3::Zero;
	CVector3	P3Scale = { 1.0f, 1.0f, 1.0f };
	CQuaternion P3Rot = CQuaternion::Identity;
	//Planet04(Goal)
	prefab::CSkinModelRender* m_PlanetModel4 = nullptr;
	CVector3 P4Pos = CVector3::Zero;
	CVector3	P4Scale = { 1.0f, 1.0f, 1.0f };
	CQuaternion P4Rot = CQuaternion::Identity;
	//マップ選択
	int m_map = 0;
	prefab::CSpriteRender* m_StageSprite = nullptr;
	prefab::CSpriteRender* m_Snum = nullptr;
	//ステージクリアされていな時に表示
	prefab::CSpriteRender* m_PleaseClearS00 = nullptr;
	CVector3 m_PClearPos = CVector3::Zero;

	//カメラ
	CVector3 m_toCameraPos;	//	CSpringCamera m_springCamera; //ばねカメラ。
	CSpringCamera m_springCamera; //ばねカメラ。

	//背景
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 MapPos = CVector3::Zero;
	CVector3 MapScale;
	CQuaternion qRot = CQuaternion::Identity;
	//Earth
	Earth* m_earth = nullptr;
	//フェード
	float m_waitTimer = 0.0f;
	Fade* m_fade = nullptr;
	enum  EnState {
		enState_FadeIn,
		enState_InGame,
	};
	EnState m_state = enState_FadeIn;
	int m_time = 0;
	bool m_isWaitFadeout = false;
	bool m_isWaitFadeout2 = false;
	bool m_isWaitFadeout3 = false;
	float m_intiBgmVolume = 0.0f;

	//文字表示
	CSprite m_sprite;
	CFont m_font;
	CFont m_fontTest;
	int m_Test = 0;

	//Button
	prefab::CSpriteRender* m_spriteRender9 = nullptr;
	CVector3 Dpos = CVector3::Zero;
	prefab::CSpriteRender* m_spriteRender10 = nullptr;
	CVector3 Bpos = CVector3::Zero;
	prefab::CSpriteRender* m_spriteRender7 = nullptr;
	CVector3 Apos = CVector3::Zero;
	prefab::CSpriteRender* m_spriteRender8 = nullptr;
	CVector3 Xpos = CVector3::Zero;
	
	ClearState* m_cstate;
	ShipState* m_shipstate;
	bool m_PCText = false;
};

