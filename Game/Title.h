#pragma once
class Player;
class Fade;
class ShipState;

class Title :  public IGameObject
{
public:
	Title();
	~Title();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void PostRender(CRenderContext& rc) override;

	ShipState* m_shipstate = nullptr;
private:
	bool m_isWaitFadeout = false;
	bool m_isWaitFadeout1 = false;
	bool m_isWaitFadeout2 = false;
	bool m_isWaitFadeout3 = false;
	CShaderResourceView m_texture;
	CSprite m_sprite;
	CVector3 titlepos = CVector3::Zero;
	CVector3 pickpos = CVector3::Zero;
	CVector3 startpos = CVector3::Zero;
	CVector3 custompos = CVector3::Zero;
	CVector3 howpos = CVector3::Zero;
	CVector3 Apos = CVector3::Zero;
	CVector3 Xpos = CVector3::Zero;
	CVector3 Dpos = CVector3::Zero;
	CQuaternion rotation = CQuaternion::Identity;
	prefab::CSpriteRender* m_spriteRender0 = nullptr;
	prefab::CSpriteRender* m_spriteRender1 = nullptr;
	prefab::CSpriteRender* m_spriteRender2 = nullptr;
	prefab::CSpriteRender* m_spriteRender3 = nullptr;
	prefab::CSpriteRender* m_spriteRender4 = nullptr;
	prefab::CSpriteRender* m_spriteRender5 = nullptr;
	prefab::CSpriteRender* m_spriteRender6 = nullptr;
	prefab::CSpriteRender* m_spriteRender7 = nullptr;
	prefab::CSpriteRender* m_spriteRender8 = nullptr;
	prefab::CSpriteRender* m_spriteRender9 = nullptr;
	Fade* m_fade = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSkinModelRender* m_skinModelRender1 = nullptr;
	float m_intiBgmVolume = 0.0f;
	int scenepick = 0;

	float m_waitTimer = 0.0f;
	enum  EnState {
		enState_FadeIn,
		enState_InGame,
	};
	EnState m_state = enState_FadeIn;
	int m_time = 0;
	int m_time1 = 0;

};

