#pragma once

class Fade;
class ShipState;
class ClearState;

class GameOver2D : public IGameObject
{
public:
	GameOver2D();
	~GameOver2D();
	bool Start();
	void Update();
	//‚à‚Í‚â2D‚Å‚Í‚È‚¢
	prefab::CSkinModelRender* m_ShipModel = nullptr;
	CVector3 m_ShipPos = CVector3::Zero;
	CVector3 m_ShipScale;
	CQuaternion m_ShipRot = CQuaternion::Identity;
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_GameOverS = nullptr;
	CVector3 GOpos = CVector3::Zero;
	prefab::CSoundSource* m_bgm = nullptr;
	prefab::CSpriteRender* m_spriteRender0 = nullptr;
	CVector3 Xpos = CVector3::Zero;
	prefab::CSkinModelRender* m_backModel = nullptr;
	CVector3 m_backPos = CVector3::Zero;
	CQuaternion m_backRot = CQuaternion::Identity;
	CVector3 m_backScale;
	CVector3 emitPos = CVector3::Zero;
	prefab::CSpriteRender* m_Ybutton = nullptr;
	CVector3 Ypos = CVector3::Zero;
	int m_timer = 59;
	int DelShipTime = 0;
	float m_waitTimer = 0.0f;
	Fade* m_fade = nullptr;
	enum  EnState {
		enState_FadeIn,
		enState_InGame,
	};
	EnState m_state = enState_FadeIn;
	int m_time = 0;
	bool m_isWaitFadeout = false;
	bool m_isWaitFadeout1 = false;
	float m_intiBgmVolume = 0.0f;
	ShipState* m_shipstate = nullptr;
	ClearState* m_cstate = nullptr;
};

