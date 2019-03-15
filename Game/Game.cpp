#include "stdafx.h"
#include "SpaceMap.h"
#include "Title.h"
#include "Game.h"
#include "Player.h"
#include "Attachments.h"
#include "ShipState.h"
#include "BackGround.h"
#include "BackGenerator.h"
#include "GameClear.h"
#include "Menu.h"
#include "Fade.h"
#include "plusObj.h"
#include "minusObj.h"
#include "minusGenerator.h"
#include "plusGenerator.h"
#include "FuelMeter.h"
#include "BackWall.h"
#include "HelthMeter.h"
#include "Param2D.h"
#include "GameOver2D.h"
#include "BackWall.h"
#include "ClearState.h"
#include "Laserbeam.h"
#include "BackDummy.h"

Game::Game()
{
}


Game::~Game(){
	QueryGOs<plusObj>("pObj", [&](plusObj* pobj)->bool {
		DeleteGO(pobj);
		return true;
	});
	QueryGOs<minusObj>("mObj", [&](minusObj* mobj)->bool {
		DeleteGO(mobj);
		return true;
	});
}

bool Game::Start()
{
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(30000.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();

	m_gameCamera = NewGO<GameCamera>(0, "GameCamera");

	m_state = enState_FadeIn;
	m_cstate = FindGO<ClearState>("ClearState");
	m_bgm = NewGO<prefab::CSoundSource>(0);
	if (m_cstate->nowStage == 0) {
		m_bgm->Init("sound/stage00.wav");
	}
	else if (m_cstate->nowStage == 1) {
		m_bgm->Init("sound/stage01.wav");
	}
	else if (m_cstate->nowStage == 2) {
		m_bgm->Init("sound/stage02.wav");
	}
	else if (m_cstate->nowStage == 3) {
		m_bgm->Init("sound/stage03.wav");
	}
	m_shipse = NewGO<prefab::CSoundSource>(0);
	m_shipse->Init("sound/shipse.wav");
	m_shipse->SetVolume(5.0f);
	 
	m_player = NewGO<Player>(0, "Player");
	m_attachments = NewGO<Attachments>(0);
	m_backGenerator = NewGO<BackGenerator>(0, "bGenerator");
	m_minus = NewGO<minusGenerator>(0, "mGenerator");
	NewGO<plusGenerator>(0, "pGenerator");
	NewGO<FuelMeter>(0, "FMeter");
	NewGO<HelthMeter>(0, "HPMeter");
	NewGO<Param2D>(0, "param2d");
	m_backdummy = NewGO<BackDummy>(0);
	m_MeterSprite = NewGO<prefab::CSpriteRender>(0);
	m_MeterSprite->Init(L"sprite/MeterBack.dds", 350.0f, 350.0f);
	MeterPos.x = -400.0f;
	MeterPos.y = -360.0f;
	m_MeterSprite->SetPosition(MeterPos);
	m_PlayingSprite = NewGO<prefab::CSpriteRender>(0);
	m_PlayingSprite->Init(L"sprite/PlayingStage.dds", 400.0f, 200.0f);
	PlayingPos.x = 440.0f;
	PlayingPos.y = 270.0f;
	m_PlayingSprite->SetPosition(PlayingPos);
	m_StageSprite = NewGO<prefab::CSpriteRender>(0);
	m_JumpSprite = NewGO<prefab::CSpriteRender>(0);
	JumpPos.y -= 400.0f;
	JumpPos.x += 545.0f;
	m_JumpSprite->SetPosition(JumpPos);
	StagePos.x = 600.0f;
	StagePos.y = 270.0f;
	m_StageSprite->SetPosition(StagePos);

	m_bwall = NewGO<BackWall>(0, "bwall");

	m_cstate->LostedPoint = 0;
	m_cstate->DamagePoint = 0;
	m_shipstate = FindGO<ShipState>("ShipState");
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}

void Game::Update() {
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

	nStage = m_cstate->nowStage;
	m_attachments->setA1Pos.x = 115.0f;
	m_attachments->setA2Pos.x = 0.0f;
	m_attachments->setA3Pos.x = 115.0f;
	m_attachments->setA3Pos.y = 80.0f;

	if (nStage == 0) {
		m_jumptimer1++;
		if (m_jumptimer <= 20) {
			m_JumpSprite->Init(L"sprite/jump0.dds", 800.0f, 500.0f);
		}
		if (m_jumptimer > 20) {
			m_JumpSprite->Init(L"sprite/jump1.dds", 800.0f, 500.0f);
		}
		if (m_jumptimer == 23) {
			m_jumptimer = 0;
		}
		if (m_jumptimer1 >= 100) {
			m_JumpSprite->Init(L"sprite/False.dds", 800.0f, 500.0f);
		}
		else {
			m_jumptimer++;

		}
	}
	else {
		m_JumpSprite->Init(L"sprite/False.dds", 800.0f, 500.0f);
	}
	if (Pad(0).IsTrigger(enButtonStart)) {
		prefab::CSoundSource* ss;
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init("sound/button.wav");
		ss->Play(false);
		if (!m_isWaitFadeout || !m_isWaitFadeout2) {
			if (!m_cstate->menu) {
				m_menu = NewGO<Menu>(0, "Menu");
				m_cstate->menu = true;
			}
			else {
				DeleteGO(m_menu);
				m_cstate->menu = false;
			}
		}
	}

	if (nStage == 0) {
		m_StageSprite->Init(L"sprite/00Text.dds", 500.0f, 300.0f);

	}
	else if (nStage == 1) {
		m_StageSprite->Init(L"sprite/01Text.dds", 500.0f, 300.0f);
	}
	else if (nStage == 2) {
		m_StageSprite->Init(L"sprite/02Text.dds", 500.0f, 300.0f);
	}
	else if (nStage == 3) {
		m_StageSprite->Init(L"sprite/03Text.dds", 500.0f, 300.0f);
	}

	if (m_isWaitFadeout2 == true) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			if (!m_isWaitFadeout)
				NewGO<GameClear>(0);
			m_shipstate->m_SState = m_shipstate->IN_GAMECLEAR;
			DeleteGO(this);
		}
	}
	else {
		if (FindGO<FuelMeter>("FMeter")->rot <= -90.0f ) {
			if (!m_isWaitFadeout)
				m_isWaitFadeout2 = true;
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init("sound/start.wav");
			ss->SetVolume(2.0f);
			ss->Play(false);
			m_cstate->m_StageCleared[nStage] = true;
			m_cstate->menu = false;
			m_fade->StartFadeOut();
		}
	}
	if (m_isWaitFadeout) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<GameOver2D>(0);
			m_shipstate->m_SState = m_shipstate->IN_GAMEOVER;
			DeleteGO(this);
		}
	}
	else {
		if (FindGO<HelthMeter>("HPMeter")->rot > 180.0f) {
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init("sound/shipbomb.wav");
			ss->SetVolume(2.0f);
			ss->Play(false);
			if(!m_isWaitFadeout2)
				m_isWaitFadeout = true;
			m_cstate->menu = false;
			m_fade->StartFadeOut();
		}
	}
	if (m_isWaitFadeoutTi == true) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<Title>(0);
			m_shipstate->m_SState = m_shipstate->IN_MAP;
			DeleteGO(this);
		}
	}
	else {
		if (goTitle) {
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init("sound/start.wav");
			ss->SetVolume(2.0f);
			ss->Play(false);
			m_isWaitFadeoutTi = true;
			m_fade->StartFadeOut();
		}
	}
	if (m_isWaitFadeoutRe == true) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<Game>(0, "Game");
			DeleteGO(this);
		}
	}
	else {
		if (goRetry) {
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init("sound/start.wav");
			ss->SetVolume(2.0f);
			ss->Play(false);
			m_isWaitFadeoutRe = true;
			m_fade->StartFadeOut();
		}
	}
	if (m_isWaitFadeoutMap == true) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<SpaceMap>(0, "SpaceMap");
			m_shipstate->m_SState = m_shipstate->IN_MAP;
			DeleteGO(this);
		}
	}
	else {
		if (goMap) {
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init("sound/start.wav");
			ss->SetVolume(2.0f);
			ss->Play(false);
			m_isWaitFadeoutMap = true;
			m_fade->StartFadeOut();
		}
	}
}

void Game::Render(CRenderContext& rc)
{
	(void)rc;
}

void Game::PostRender(CRenderContext& rc) {
	/*
	wchar_t text[256];
	swprintf_s(text, L"%d", m_cstate->LostedPoint + m_cstate->DamagePoint);
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	m_font.Begin(rc);
	m_font.Draw(text, { 800.0f, -250.0f }, { 0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 5.0f }, 0.0f, 1.0f);
	m_font.End(rc);
	*/
}

void Game::OnDestroy() {
	plusGenerator* pgenerator = FindGO<plusGenerator>("pGenerator");
	DeleteGO(pgenerator);
	minusGenerator* mgenerator = FindGO<minusGenerator>("mGenerator");
	DeleteGO(mgenerator);
	QueryGOs<Laserbeam>("Laserbeam", [&](Laserbeam* lbeam)->bool {
		DeleteGO(lbeam);
		return true;
	});
	QueryGOs<Menu>("Menu", [&](Menu* menu)->bool {
		DeleteGO(menu);
		return true;
	});
	m_cstate->menu = false;
	DeleteGO(m_player);
	HelthMeter* hmeter = FindGO<HelthMeter>("HPMeter");
	DeleteGO(hmeter);
	FuelMeter* fmeter = FindGO<FuelMeter>("FMeter");
	DeleteGO(fmeter);
	Param2D* p2d = FindGO<Param2D>("param2d");
	DeleteGO(p2d);
	DeleteGO(m_attachments);
	DeleteGO(m_backGenerator);
	DeleteGO(m_bwall);
	DeleteGO(m_gameCamera);
	DeleteGO(m_bgm);
	DeleteGO(m_shipse);
	DeleteGO(m_MeterSprite);
	DeleteGO(m_PlayingSprite);
	DeleteGO(m_backdummy);
	DeleteGO(m_StageSprite);
	DeleteGO(m_JumpSprite);
}