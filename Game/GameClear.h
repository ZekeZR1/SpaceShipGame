#pragma once
class Fade;
class Player;
class Attachments;
class ClearState;
class ShipState;

class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;

	int x = 0;
	int Score = 0;
	Player* m_player = nullptr;
	Attachments* m_attachments = nullptr;
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_spriteRender1 = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;
	prefab::CSkinModelRender* m_backModel = nullptr;
	CVector3 m_backPos = CVector3::Zero;
	CQuaternion m_backRot = CQuaternion::Identity;
	CVector3 m_backScale;
	prefab::CSkinModelRender* m_planetModel = nullptr;
	float rr = 0.0f;
	CVector3 m_planetPos = CVector3::Zero;
	CVector3 m_planetScale;
	CQuaternion m_planetRot = CQuaternion::Identity;
	prefab::CSkinModelRender* m_ShipModel = nullptr;
	CVector3 m_ShipPos = CVector3::Zero;
	CVector3 m_ShipScale;
	CQuaternion m_ShipRot = CQuaternion::Identity;
	prefab::CDirectionLight* m_lig;			//ライト。
	CVector3 m_lightDir;					//ライトの方向。
	prefab::CSpriteRender* m_spriteRender0 = nullptr;
	prefab::CSpriteRender* m_spriteRender2 = nullptr;
	prefab::CSpriteRender* m_spriteRender3 = nullptr;
	prefab::CSpriteRender* m_Noti1 = nullptr;
	prefab::CSpriteRender* m_Noti2 = nullptr;
	prefab::CSpriteRender* m_Noti3 = nullptr;
	prefab::CSpriteRender* m_RankSprite = nullptr;
	prefab::CSpriteRender* m_thisRank = nullptr;
	CVector3 Noti1Pos = CVector3::Zero;
	CVector3 Noti2Pos = CVector3::Zero;
	CVector3 Noti3Pos = CVector3::Zero;
	CVector3 RankPos = CVector3::Zero;
	CVector3 thisRankPos = CVector3::Zero;
	CVector3 Xpos = CVector3::Zero;
	CVector3 Ypos = CVector3::Zero;
	CVector3 Clearpos = CVector3::Zero;
	float m_waitTimer = 0.0f;
	Fade* m_fade = nullptr;
	enum  EnState {
		enState_FadeIn,
		enState_InGame,
	};
	EnState m_state = enState_FadeIn;
	ClearState* m_cstate = nullptr;
	ShipState* m_shipstate = nullptr;
	int m_time = 0;
	int m_ChangeTimer = 0;
	bool m_isWaitFadeout = false;
	bool m_isWaitFadeout1 = false;
	bool m_isWaitFadeout2 = false;
	float m_intiBgmVolume = 0.0f;
	//Text
	CSprite m_sprite;
	CFont m_font;
	CFont m_fontTest;
	CSprite m_sprite1;
	CFont m_font1;
	CFont m_fontTest1;
};

