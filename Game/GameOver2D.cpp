#include "stdafx.h"
#include "GameOver2D.h"
#include "Fade.h"
#include "Game.h"
#include "ShipState.h"
#include "ClearState.h"
#include "Title.h"

GameOver2D::GameOver2D()
{
}

GameOver2D::~GameOver2D()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_spriteRender0);
	DeleteGO(m_GameOverS);
	DeleteGO(m_backModel);
	DeleteGO(m_Ybutton);
	DeleteGO(m_ShipModel);
	DeleteGO(m_bgm);
}

bool GameOver2D::Start() {
	tkEngine::MainCamera().SetNear(0.1f);
	tkEngine::MainCamera().SetFar(20000.0f);
	tkEngine::MainCamera().SetPosition({ 0.0f, 500.0f, 500.0f });
	tkEngine::MainCamera().SetTarget({ 0.0f,0.0f,0.0f });
	//tkEngine::MainCamera().SetViewAngle(120.0f);
	tkEngine::MainCamera().Update();
	//ƒ{ƒ^ƒ“
	//X
	m_spriteRender0 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender0->Init(L"sprite/XbuttonToTitle.dds", 250.0f, 150.0f);
	Xpos.y -= 300.0f;
	Xpos.x -= 500.0f;
	m_spriteRender0->SetPosition(Xpos);
	//Y
	m_Ybutton = NewGO<prefab::CSpriteRender>(0);
	m_Ybutton->Init(L"sprite/YbuttonR.dds", 250.0f, 150.0f);
	Ypos.y -= 300.0f;
	Ypos.x += 500.0f;
	m_Ybutton->SetPosition(Ypos);
	//Space
	m_backModel = NewGO<prefab::CSkinModelRender>(0);
	m_backModel->Init(L"modelData/CubeSpace.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	m_backScale = { 10.0f,10.0f, 10.0f };
	m_backModel->SetScale(m_backScale);
	m_backRot.SetRotationDeg(CVector3::AxisX, -45.0f);
	m_backRot.SetRotationDeg(CVector3::AxisY, 90.0f);
	m_backModel->SetRotation(m_backRot);
	//Ship
	m_ShipModel = NewGO<prefab::CSkinModelRender>(0);
	m_ShipModel->Init(L"modelData/AnimSpaceShip.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	m_ShipPos.x += 50.0f;
	m_ShipPos.z += 350.0f;
	m_ShipPos.y += 350.0f;
	m_ShipModel->SetPosition(m_ShipPos);
	m_ShipRot.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_ShipRot.SetRotationDeg(CVector3::AxisY, -90.0f);
	m_ShipRot.SetRotationDeg(CVector3::AxisZ, -15.0f);
	m_ShipModel->SetRotation(m_ShipRot);
	//BlackHole
	prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
	CVector3 scale;
	scale = { 70.0f, 70.0f, 70.0f };
	effect->SetScale(scale);
	emitPos.x = -40.0;
	effect->SetPosition(emitPos);
	effect->Play(L"effect/BlackHole2.efk");
	//GameOverSprite
	m_GameOverS = NewGO<prefab::CSpriteRender>(0);
	GOpos.x -= 15.0f;
	GOpos.y += 250.0f;
	m_GameOverS->SetPosition(GOpos);

	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init("sound/gameover.wav");
	m_bgm->SetVolume(0.7f);

	m_shipstate = FindGO<ShipState>("ShipState");
	return true;
}

void GameOver2D::Update() {
	switch (m_state) {
	case enState_FadeIn:
		GraphicsEngine().GetTonemap().Reset();
		if (!m_fade->IsFade()) {
			m_state = enState_InGame;
			m_bgm->Play(true);
			m_intiBgmVolume = m_bgm->GetVolume();
		}
		break;
	case enState_InGame: {
		m_waitTimer += GameTime().GetFrameDeltaTime();
		if (m_waitTimer < 0.1f) {
			GraphicsEngine().GetTonemap().Reset();
		}
	}break;
	}
	m_ShipPos.x -= 1.0f;
	m_ShipPos.y -= 5.0f;
	m_ShipPos.z -= 5.0f;
	DelShipTime++;
	m_ShipModel->SetPosition(m_ShipPos);
	if (DelShipTime == 70) {
		prefab::CSoundSource* ss;
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init("sound/shipbomb.wav");
		ss->SetVolume(2.0f);
		ss->Play(false);
		m_ShipPos.z = -15000.0f;
		m_ShipModel->SetPosition(m_ShipPos);
	}
	if (DelShipTime == 100)
		m_GameOverS->Init(L"sprite/GameOverSprite.dds", 800.0f, 500.0f);

	if (m_isWaitFadeout) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<Game>(0, "Game");
			m_shipstate->m_SState = m_shipstate->IN_GAME;
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonY) && DelShipTime >= 70) {
			if (m_isWaitFadeout1 == false) {
				prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
				s->Init("sound/buff.wav");
				s->Play(false);
				m_isWaitFadeout = true;
				m_fade->StartFadeOut();
			}
		}
	}
	if (m_isWaitFadeout1) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<Title>(0);
			m_shipstate->m_SState = m_shipstate->IN_MAP;
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonX) && DelShipTime >= 70) {
			if (m_isWaitFadeout == false) {
				prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
				s->Init("sound/repair.wav");
				s->Play(false);
				m_isWaitFadeout1 = true;
				m_fade->StartFadeOut();
			}
		}
	}
}