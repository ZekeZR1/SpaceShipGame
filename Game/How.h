#pragma once
class Game;
class Fade;

class How : public IGameObject
{
public:
	How();
	~How();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;

private:
	prefab::CSoundSource* m_sound = nullptr;
	prefab::CSpriteRender* m_spriteRender = nullptr;
	float m_waitTimer = 0.0f;
	Fade* m_fade = nullptr;
	enum  EnState {
		enState_FadeIn,
		enState_InGame,
	};
	EnState m_state = enState_FadeIn;
	bool m_isWaitFadeout = false;
};

