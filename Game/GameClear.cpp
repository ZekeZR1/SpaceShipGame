#include "stdafx.h"
#include "GameClear.h"
#include "Game.h"
#include "Fade.h"
#include "Title.h"
#include "Story.h"
#include "Player.h"
#include "ClearState.h"
#include "ShipState.h"
#include "ShipCustomizeScene.h"
#include "Attachments.h"
#include "tkEngine/light/tkDirectionLight.h"


GameClear::GameClear()
{
}


GameClear::~GameClear()
{
	DeleteGO(m_backModel);
	DeleteGO(m_planetModel);
	DeleteGO(m_spriteRender0);
	DeleteGO(m_spriteRender2);
	DeleteGO(m_spriteRender3);
	DeleteGO(m_Noti1);
	DeleteGO(m_Noti2);
	DeleteGO(m_Noti3);
	DeleteGO(m_thisRank);
	DeleteGO(m_RankSprite);
	DeleteGO(m_bgm);
	DeleteGO(m_player);
	DeleteGO(m_attachments);
}

bool GameClear::Start() {

	tkEngine::MainCamera().SetNear(0.1f);
	tkEngine::MainCamera().SetFar(20000.0f);
	tkEngine::MainCamera().SetPosition({ 0.0f, 500.0f, 500.0f });
	tkEngine::MainCamera().SetTarget({ 0.0f,0.0f,0.0f });
	tkEngine::MainCamera().Update();
	m_player = NewGO<Player>(0, "Player");
	m_attachments = NewGO<Attachments>(0);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	//ƒ{ƒ^ƒ“
	m_spriteRender0 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender0->Init(L"sprite/XbuttonToCus.dds", 250.0f, 150.0f);
	Xpos.y -= 300.0f;
	Xpos.x -= 500.0f;
	m_spriteRender0->SetPosition(Xpos);
	m_spriteRender2 = NewGO<prefab::CSpriteRender>(0);
	Ypos.y -= 300.0f;
	Ypos.x += 500.0f;
	m_spriteRender2->SetPosition(Ypos);
	//ClearSprite
	m_spriteRender3 = NewGO<prefab::CSpriteRender>(0);
	Clearpos.x -= 15.0f;
	Clearpos.y += 300.0f;
	m_spriteRender3->SetPosition(Clearpos);
	//Notification
	m_Noti1 = NewGO<prefab::CSpriteRender>(0);
	Noti1Pos.x = 440.0f;
	Noti1Pos.y = 270.0f;
	m_Noti1->SetPosition(Noti1Pos);
	m_Noti2 = NewGO<prefab::CSpriteRender>(0);
	Noti2Pos.x = 440.0f;
	Noti2Pos.y = 110.0f;
	m_Noti2->SetPosition(Noti2Pos);
	m_Noti3 = NewGO<prefab::CSpriteRender>(0);
	Noti3Pos.x = 440.0f;
	Noti3Pos.y = -50.0f;
	m_Noti3->SetPosition(Noti3Pos);
	//Rank
	m_RankSprite = NewGO<prefab::CSpriteRender>(0);
	m_RankSprite->Init(L"sprite/RankSprite.dds", 800.0f, 500.0f);
	RankPos.x -= 290.0f;
	RankPos.y += 130.0f;
	m_RankSprite->SetPosition(RankPos);
	m_thisRank = NewGO<prefab::CSpriteRender>(0);
	thisRankPos.x -= 290.0f;
	thisRankPos.y -= 130.0f;
	m_thisRank->SetPosition(RankPos);
	//Space
	m_backModel = NewGO<prefab::CSkinModelRender>(0);
	m_backModel->Init(L"modelData/CubeSpace.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	m_backScale = { 10.0f,10.0f, 10.0f };
	m_backModel->SetScale(m_backScale);
	m_backRot.SetRotationDeg(CVector3::AxisX, -45.0f);
	m_backModel->SetRotation(m_backRot);
	//Planet
	m_planetModel = NewGO<prefab::CSkinModelRender>(0);
	m_planetPos.x -= 400.0f;
	m_planetPos.y -= 200.0f;
	m_planetModel->SetPosition(m_planetPos);
	m_planetScale = { 10.0f,10.0f, 10.0f };
	m_planetModel->SetScale(m_planetScale);
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init("sound/gameclearbgm.wav");
	m_bgm->SetVolume(0.6f);
	m_bgm->Play(true);
	m_intiBgmVolume = m_bgm->GetVolume();
	m_cstate = FindGO<ClearState>("ClearState");
	m_shipstate = FindGO<ShipState>("ShipState");
	Score = m_cstate->LostedPoint + m_cstate->DamagePoint;
	return true;
}


void GameClear::Update() {
	switch (m_state) {
	case enState_FadeIn:
		GraphicsEngine().GetTonemap().Reset();
		if (!m_fade->IsFade()) {
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

	if(Score < 10){
		m_thisRank->Init(L"sprite/RankS.dds", 800.0f, 500.0f);
	}
	else if(Score < 15){
		m_thisRank->Init(L"sprite/RankA.dds", 800.0f, 500.0f);
	}
	else if (Score < 20) {
		m_thisRank->Init(L"sprite/RankB.dds", 800.0f, 500.0f);
	}
	else if (Score < 30) {
		m_thisRank->Init(L"sprite/RankC.dds", 800.0f, 500.0f);
	}
	else {
		m_thisRank->Init(L"sprite/RankD.dds", 800.0f, 500.0f);
	}

	if (m_cstate->nowStage == 3) {
		m_spriteRender2->Init(L"sprite/YbuttonStory.dds", 250.0f, 150.0f);
		m_spriteRender3->Init(L"sprite/GCS.dds", 800.0f, 500.0f);
	}
	else {
		m_spriteRender2->Init(L"sprite/Ybutton.dds", 250.0f, 150.0f);
		m_spriteRender3->Init(L"sprite/StageClear.dds", 800.0f, 500.0f);
	}

	if (m_cstate->nowStage == 0) {
		m_planetModel->Init(L"modelData/ClearPlanet.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
		if (m_cstate->S00firstClear) {
			m_Noti1->Init(L"sprite/Noti1.dds", 400.0f, 200.0f);
			m_Noti2->Init(L"sprite/Noti2.dds", 400.0f, 200.0f);
			m_Noti3->Init(L"sprite/Noti3.dds", 400.0f, 200.0f);
		}
	}
	if (m_cstate->nowStage == 1) {
		m_planetModel->Init(L"modelData/ClearPlanet1.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
		if (m_cstate->S01firstClear) {
			m_Noti1->Init(L"sprite/Noti1.dds", 400.0f, 200.0f);
			m_Noti2->Init(L"sprite/Noti2.dds", 400.0f, 200.0f);
			m_Noti3->Init(L"sprite/Noti3.dds", 400.0f, 200.0f);
		}
	}
	if (m_cstate->nowStage == 2) {
		m_planetModel->Init(L"modelData/ClearPlanet2.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
		if (m_cstate->S02firstClear) {
			m_Noti1->Init(L"sprite/Noti1.dds", 400.0f, 200.0f);
			m_Noti2->Init(L"sprite/Noti2.dds", 400.0f, 200.0f);
			m_Noti3->Init(L"sprite/Noti3.dds", 400.0f, 200.0f);
		}
	}
	if (m_cstate->nowStage == 3) {
		m_planetModel->Init(L"modelData/ClearPlanet3.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
		if (m_cstate->S03firstClear) {
			Noti3Pos.x = 440.0f;
			Noti3Pos.y = 270.0f;
			m_Noti3->SetPosition(Noti3Pos);
			m_Noti3->Init(L"sprite/Noti3.dds", 400.0f, 200.0f);
		}
	}
	if (m_isWaitFadeout) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			if (m_cstate->nowStage != 3) {
				m_cstate->nowStage++;
			}
			NewGO<Game>(0, "Game");
			m_shipstate->m_SState = m_shipstate->IN_GAME;
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonY)) {
			if (m_isWaitFadeout1 == false) {
				prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
				s->Init("sound/start.wav");
				s->SetVolume(2.0f);
				s->Play(false);
				if (m_cstate->nowStage == 0) {
					m_cstate->S00firstClear = false;
					m_isWaitFadeout = true;
				}
				else if (m_cstate->nowStage == 1) {
					m_cstate->S01firstClear = false;
					m_isWaitFadeout = true;
				}
				else if (m_cstate->nowStage == 2) {
					m_cstate->S02firstClear = false;
					m_isWaitFadeout = true;
				}
				else if (m_cstate->nowStage == 3) {
					m_cstate->S03firstClear = false;
					m_isWaitFadeout2 = true;
				}
				m_fade->StartFadeOut();
			}
		}
		if (m_isWaitFadeout1) {
			m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
			if (!m_fade->IsFade()) {
				NewGO<ShipCustomizeScene>(0);
				m_shipstate->m_SState = m_shipstate->IN_MAP;
				DeleteGO(this);
			}
		}
		else {
			if (Pad(0).IsTrigger(enButtonX)) {
				if (m_isWaitFadeout == false) {
					prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
					s->Init("sound/start.wav");
					s->SetVolume(2.0f);
					s->Play(false);
					if (m_cstate->nowStage == 0) {
						m_cstate->S00firstClear = false;
					}
					else if (m_cstate->nowStage == 1) {
						m_cstate->S01firstClear = false;
					}
					else if (m_cstate->nowStage == 2) {
						m_cstate->S02firstClear = false;
					}
					else if (m_cstate->nowStage == 3) {
						m_cstate->S03firstClear = false;
					}
					m_isWaitFadeout1 = true;
					m_fade->StartFadeOut();
				}
			}
		}
		if (m_isWaitFadeout2) {
			m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
			if (!m_fade->IsFade()) {
				m_cstate->nowStage++;
				NewGO<Story>(0);
				m_shipstate->m_SState = m_shipstate->IN_MAP;
				DeleteGO(this);
			}
		}
		if (rr == 0.0f)
			rr = 360.0f;
		m_planetRot.SetRotationDeg(CVector3::AxisZ, rr);
		rr -= 0.08f;
		m_planetModel->SetRotation(m_planetRot);
	}
}

void GameClear::PostRender(CRenderContext& rc) {

	wchar_t text[256];
	swprintf_s(text, L"%d", (100 - (m_cstate->DamagePoint) * 3));
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	m_font.Begin(rc);
	m_font.Draw(text, { 250.0f, -305.0f }, { 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 5.0f }, 0.0f, 1.0f);
	m_font.End(rc);

	wchar_t text2[256];
	swprintf_s(text2, L"%d", (100 - (m_cstate->LostedPoint) * 5));
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	m_font.Begin(rc);
	m_font.Draw(text2, { 250.0f, -380.0f }, { 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 5.0f }, 0.0f, 1.0f);
	m_font.End(rc);
}