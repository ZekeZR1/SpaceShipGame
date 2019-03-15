#pragma once
class Fade;
class ClearState;
class Story : public IGameObject	
{
public:
	Story();
	~Story();
	bool Start();
	void Update();

	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_Xbutton = nullptr;
	CVector3 Xpos = CVector3::Zero;
	prefab::CSpriteRender* m_Dpad = nullptr;
	CVector3 Dpos = CVector3::Zero;
	ClearState* m_cstate = nullptr;
	float m_waitTimer = 0.0f;
	Fade* m_fade = nullptr;
	enum  EnState {
		enState_FadeIn,
		enState_InGame,
	};
	EnState m_state = enState_FadeIn;
private:
	int m_time = 0;
	int m_time1 = 0;
	bool m_isWaitFadeout = false;
	bool m_isWaitFadeout2 = false;
	float m_intiBgmVolume = 0.0f;
	int EGOIST = 0;
	prefab::CSoundSource* m_bgm = nullptr;
};

