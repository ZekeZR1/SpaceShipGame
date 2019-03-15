#pragma once

class Fade;

class Param2D : public IGameObject
{
public:
	Param2D();
	~Param2D();
	bool Start();

	float m_waitTimer = 0.0f;
	prefab::CSpriteRender* m_spriteRender = nullptr;
	CVector3 pos = CVector3::Zero;
	Fade* m_fade = nullptr;
	enum  EnState {
		enState_FadeIn,
		enState_InGame,
	};
	EnState m_state = enState_FadeIn;
	int m_time = 0;
	bool m_isWaitFadeout = false;
};

