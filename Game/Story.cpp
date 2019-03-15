#include "stdafx.h"
#include "Story.h"
#include "SpaceMap.h"
#include "Title.h"
#include "Fade.h"
#include "ClearState.h"

Story::Story()
{
}


Story::~Story()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_Dpad);
	DeleteGO(m_Xbutton);
	DeleteGO(m_bgm);
}


bool Story::Start() {
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init("sound/storybgm.wav");
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	//DirectionalPadê‡ñæ
	m_Dpad = NewGO<prefab::CSpriteRender>(0);
	m_Dpad->Init(L"sprite/DpadS.dds", 200.0f, 100.0f);
	Dpos.y -= 300.0f;
	Dpos.x += 350.0f;
	m_Dpad->SetPosition(Dpos);
	//XÉ{É^Éìê‡ñæ
	m_Xbutton = NewGO<prefab::CSpriteRender>(0);
	m_Xbutton->Init(L"sprite/Xbutton.dds", 200.0f, 100.0f);
	Xpos.y -= 300.0f;
	Xpos.x += 555.0f;
	m_Xbutton->SetPosition(Xpos);
	//Fade
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;
	m_cstate = FindGO<ClearState>("ClearState");
	return true;
}


void Story::Update() {
	switch (m_state) {
	case enState_FadeIn:
		GraphicsEngine().GetTonemap().Reset();
		if (!m_fade->IsFade()) {
			m_bgm->Play(true);
			m_intiBgmVolume = m_bgm->GetVolume();
			m_state = enState_InGame;
		}
		break;
	case enState_InGame: {
		m_waitTimer += GameTime().GetFrameDeltaTime();
		if (m_waitTimer < 0.1f) {
			GraphicsEngine().GetTonemap().Reset();
		}
	}break;
	}

	if (Pad(0).IsPressAnyKey()) {
		prefab::CSoundSource* m_sound = nullptr;
		m_sound = NewGO<prefab::CSoundSource>(0);
		m_sound->Init("sound/button.wav");
		m_sound->Play(false);
	}
	if (m_isWaitFadeout) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<SpaceMap>(0);
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonX)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
	if (Pad(0).IsTrigger(enButtonRight)) {
		if (EGOIST != 1)
			EGOIST++;
	}
	if (Pad(0).IsTrigger(enButtonLeft)) {
		if (EGOIST != 0)
			EGOIST--;
	}
	if (m_cstate->nowStage == 0) {
		if (EGOIST == 0) {
			m_spriteRender->Init(L"sprite/Story01_1.dds", 1280.0f, 720.0f);
		}
		else if (EGOIST == 1) {
			m_spriteRender->Init(L"sprite/Story01_2.dds", 1280.0f, 720.0f);
		}
	}
	if (m_cstate->nowStage == 1) {
		if(EGOIST == 0)
			m_spriteRender->Init(L"sprite/Story02_1.dds", 1280.0f, 720.0f);
		else
			m_spriteRender->Init(L"sprite/Story02_2.dds", 1280.0f, 720.0f);
	}
	if (m_cstate->nowStage == 2) {
		m_spriteRender->Init(L"sprite/Story03_1.dds", 1280.0f, 720.0f);
	}
	if (m_cstate->nowStage == 3) {
		m_spriteRender->Init(L"sprite/Story04_1.dds", 1280.0f, 720.0f);
	}
	if (m_cstate->nowStage == 4) {
		m_spriteRender->Init(L"sprite/Story05_1.dds", 1280.0f, 720.0f);
	}
}
