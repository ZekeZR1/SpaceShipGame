#include "stdafx.h"
#include "How.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"

How::How()
{
}

How::~How()
{
	DeleteGO(m_spriteRender);
}

bool How::Start() {
	m_fade = FindGO<Fade>("Fade");
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/howtoplay.dds", 1280.0f, 720.0f);
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;
	return true;
}

void How::Update() {

	switch (m_state) {
	case enState_FadeIn:
		GraphicsEngine().GetTonemap().Reset();
		if (!m_fade->IsFade()) {
			m_state = enState_InGame;
		}
		break;
	case enState_InGame: {
		m_waitTimer +=  1.5 * GameTime().GetFrameDeltaTime();
		if (m_waitTimer < 0.1f) {
			GraphicsEngine().GetTonemap().Reset();
		}
	}break;
	}
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Title>(0);
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonX)) {
			m_sound = NewGO<prefab::CSoundSource>(0);
			m_sound->Init("sound/button.wav");
			m_sound->Play(false);
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}

void How::PostRender(CRenderContext& rc)
{
}