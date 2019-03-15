#include "stdafx.h"
#include "Title.h"
#include "ShipState.h"
#include "GameOver2D.h"
#include "GameClear.h"
#include "GameCamera.h"
#include "Game.h"
#include "Fade.h"
#include "Story.h"
#include "How.h"
#include "SpaceMap.h"
#include "ShipCustomizeScene.h"
#include "tkEngine/sound/tkSoundSource.h"

Title::Title()
{
}


Title::~Title()
{
}

void Title::OnDestroy()
{	
	DeleteGO(m_spriteRender2);
	DeleteGO(m_spriteRender3);
	DeleteGO(m_spriteRender4);
	DeleteGO(m_spriteRender5);
	DeleteGO(m_spriteRender6);
	DeleteGO(m_spriteRender7);
	DeleteGO(m_spriteRender8);
	DeleteGO(m_spriteRender9);
	DeleteGO(m_bgm);
}
bool Title::Start()
{
	//BGM
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init("sound/title.wav");
	m_bgm->Play(true);
	m_intiBgmVolume = m_bgm->GetVolume();
	//Title背景
	m_spriteRender6 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender6->Init(L"sprite/GameTitle2.dds", 1280.0f, 720.0f);
	//選択Sprite
	m_spriteRender2 = NewGO<prefab::CSpriteRender>(0);
	pickpos.x -= 330.0f;
	pickpos.y -= 150.0f;
	m_spriteRender2->SetPosition(pickpos);
	m_spriteRender2->Init(L"sprite/pick.dds", 500,300);
	//操作方法文字
	m_spriteRender3 = NewGO<prefab::CSpriteRender>(0);
	howpos.x -= 350.0f;
	howpos.y -= 150.0f;
	m_spriteRender3->SetPosition(howpos);
	//スタート文字
	m_spriteRender4 = NewGO<prefab::CSpriteRender>(0);
	startpos.x -= 350.0f;
	startpos.y -= 50.0f;
	m_spriteRender4->SetPosition(startpos);
	//カスタマイズ文字 
	m_spriteRender5 = NewGO<prefab::CSpriteRender>(0);
	custompos.x -= 350.0f;
	custompos.y -= 250.0f;
	m_spriteRender5->SetPosition(custompos);
	//Aボタン説明
	m_spriteRender7 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender7->Init(L"sprite/Abutton.dds", 200.0f, 100.0f);
	Apos.y -= 300.0f;
	Apos.x += 500.0f;
	m_spriteRender7->SetPosition(Apos);
	//Xボタン説明
	m_spriteRender8 = NewGO<prefab::CSpriteRender>(0);
	Xpos.y -= 300.0f;
	Xpos.x += 500.0f;
	m_spriteRender8->SetPosition(Xpos);
	//DirectionalPad説明
	m_spriteRender9 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender9->Init(L"sprite/Dpad.dds", 200.0f, 100.0f);
	Dpos.y -= 300.0f;
	Dpos.x += 350.0f;
	m_spriteRender9->SetPosition(Dpos);
	//フェードイン
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();

	m_shipstate = FindGO<ShipState>("ShipState");
	return true;
}

void Title::Update() {
	switch (m_state) {
	case enState_FadeIn:
		GraphicsEngine().GetTonemap().Reset();
		if (!m_fade->IsFade()) {
			m_state = enState_InGame;
			m_bgm->Play(true);
		}
		break;
	case enState_InGame: {
		m_waitTimer += 1.5 * GameTime().GetFrameDeltaTime();
		if (m_waitTimer < 0.1f) {
			GraphicsEngine().GetTonemap().Reset();
		}
	}break;
	}
	if (Pad(0).IsTrigger(enButtonUp)) {
		if (scenepick != 1) {
			prefab::CSoundSource* m_sound;
			m_sound = NewGO<prefab::CSoundSource>(0);
			m_sound->Init("sound/button.wav");
			m_sound->Play(false);
			scenepick += 1;
			pickpos.y += 100.0f;
			m_spriteRender2->SetPosition(pickpos);
		}
	}
	if (Pad(0).IsTrigger(enButtonDown)) {
		if (scenepick != -1) {
			prefab::CSoundSource* m_sound;
			m_sound = NewGO<prefab::CSoundSource>(0);
			m_sound->Init("sound/button.wav");
			m_sound->Play(false);
			scenepick -= 1;
			pickpos.y -= 100.0f;
			m_spriteRender2->SetPosition(pickpos);
		}
	}

	if (scenepick == 0) {
		m_spriteRender3->Init(L"sprite/howpick.dds", 500, 300);
		m_spriteRender4->Init(L"sprite/startpickA.dds", 500, 300);
		m_spriteRender5->Init(L"sprite/customizepickA.dds", 500, 300);
	}
	else if (scenepick == 1) {
		m_spriteRender3->Init(L"sprite/howpickA.dds", 500, 300);
		m_spriteRender4->Init(L"sprite/startpick.dds", 500, 300);
		m_spriteRender5->Init(L"sprite/customizepickA.dds", 500, 300);
	}
	else if (scenepick == -1) {
		m_spriteRender3->Init(L"sprite/howpickA.dds", 500, 300);
		m_spriteRender4->Init(L"sprite/startpickA.dds", 500, 300);
		m_spriteRender5->Init(L"sprite/customizepick.dds", 500, 300);
	}
	//マップ選択シーンへ移行
	if (m_isWaitFadeout) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<SpaceMap>(0, "SpaceMap");
			m_shipstate->m_SState = m_shipstate->IN_MAP;
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsPress(enButtonA) && scenepick == 1) {
			prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
			s->Init("sound/start.wav");
			s->SetVolume(1.0f);
			s->Play(false);
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
		if (m_isWaitFadeout1) {
			m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
			if (!m_fade->IsFade()) {
				NewGO<How>(0);
				DeleteGO(this);
			}
		}
		else {
			if (Pad(0).IsPress(enButtonA) && scenepick == 0) {
				prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
				s->Init("sound/button.wav");
				s->SetVolume(1.0f);
				s->Play(false);
				m_isWaitFadeout1 = true;
				m_fade->StartFadeOut();
			}
		}
		//ShipCustomizeSceneへ移行
		if (m_isWaitFadeout3) {
			m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
			if (!m_fade->IsFade()) {
				NewGO<ShipCustomizeScene>(0);
				DeleteGO(this);
			}
		}
		else {
			if (Pad(0).IsTrigger(enButtonA) && scenepick == -1) {
				prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
				s->Init("sound/button.wav");
				s->SetVolume(1.0f);
				s->Play(false);
				m_isWaitFadeout3 = true;
				m_fade->StartFadeOut();
			}
		}
	}
}

void Title::PostRender(CRenderContext& rc)
{
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
