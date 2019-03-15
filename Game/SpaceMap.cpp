#include "stdafx.h"
#include "SpaceMap.h"
#include "Earth.h"
#include "Game.h"
#include "Title.h"
#include "Story.h"
#include "Fade.h"
#include "GameCamera.h"
#include "ClearState.h"
#include "Attachments.h"
#include "Player.h"
#include "ShipState.h"

SpaceMap::SpaceMap()
{
}

SpaceMap::~SpaceMap()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_player);
	DeleteGO(m_PlanetModel0);
	DeleteGO(m_PlanetModel2);
	DeleteGO(m_PlanetModel3);
	DeleteGO(m_PlanetModel4);
	DeleteGO(m_StageSprite);
	DeleteGO(m_PleaseClearS00);
	DeleteGO(m_Snum);
	DeleteGO(m_bgm);
	DeleteGO(m_earth);
	DeleteGO(m_spriteRender7);
	DeleteGO(m_spriteRender8);
	DeleteGO(m_spriteRender9);
	DeleteGO(m_spriteRender10);
	DeleteGO(m_attachments);
}

bool SpaceMap::Start() {
	//バネカメラ
	tkEngine::MainCamera().SetNear(0.1f);
	tkEngine::MainCamera().SetFar(20000.0f);
	tkEngine::MainCamera().SetPosition({ 0.0f, 500.0f, 500.0f });
	m_toCameraPos.Set(0.0f, 50.0f, 100.0f);
	m_springCamera.Init(
		MainCamera(),		
		1000.0f,		
		true,				
		5.0f			
	);
	tkEngine::MainCamera().Update();
	//Attachments
	m_attachments = NewGO<Attachments>(0);
	//背景
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/CubeSpace.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	qRot.SetRotationDeg(CVector3::AxisY, 180.0f);
	m_skinModelRender->SetRotation(qRot);
	//BGM
	m_bgm = NewGO<prefab::CSoundSource>(0, "bgm");
	m_bgm->Init("sound/mapscene.wav");
	//Planets
	m_earth = NewGO<Earth>(0);
	//Planet0
	m_PlanetModel0 = NewGO<prefab::CSkinModelRender>(0);
	P0Pos.z -= 350.0f;
	m_PlanetModel0->SetPosition(P0Pos);
	//Planet02
	m_PlanetModel2 = NewGO<prefab::CSkinModelRender>(0);
	P2Pos.z -= 300.0f;
	P2Pos.x -= 500.0f;
	m_PlanetModel2->SetPosition(P2Pos);
	//Planet03
	m_PlanetModel3 = NewGO<prefab::CSkinModelRender>(0);
	P3Pos.x -= 800.0f;
	P3Pos.y += 100.0f;
	P3Pos.z += 100.0f;
	m_PlanetModel3->SetPosition(P3Pos);
	//Planet04
	m_PlanetModel4 = NewGO<prefab::CSkinModelRender>(0);
	P4Pos.z += 600.0f;
	P4Pos.x -= 300.0f;
	P4Pos.y += 400.0f;
	m_PlanetModel4->SetPosition(P4Pos);
	//StageSprite
	m_StageSprite = NewGO<prefab::CSpriteRender>(0);
	CVector3 StagePos = CVector3::Zero;
	StagePos.x += 100.0f;
	StagePos.y += 20.0f;
	m_StageSprite->SetPosition(StagePos);
	//選択ステージ番号
	m_Snum = NewGO<prefab::CSpriteRender>(0);
	CVector3 m_SnPos = CVector3::Zero;
	m_SnPos.x += 300.0f;
	m_SnPos.y += 20.0f;
	m_Snum->SetPosition(m_SnPos);
	//DirectionalPad説明
	m_spriteRender9 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender9->Init(L"sprite/Dpad.dds", 200.0f, 100.0f);
	Dpos.y -= 300.0f;
	Dpos.x += 30.0f;
	m_spriteRender9->SetPosition(Dpos);
	//Aボタン説明
	m_spriteRender7 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender7->Init(L"sprite/Abutton.dds", 200.0f, 100.0f);
	Apos.y -= 300.0f;
	Apos.x += 200.0f;
	m_spriteRender7->SetPosition(Apos);
	//Bボタン説明
	m_spriteRender10 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender10->Init(L"sprite/Bbutton.dds", 200.0f, 100.0f);
	Bpos.y -= 298.0f;
	Bpos.x += 380.0f;
	m_spriteRender10->SetPosition(Bpos);
	//Xボタン説明
	m_spriteRender8 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender8->Init(L"sprite/Xbutton.dds", 200.0f, 100.0f);
	Xpos.y -= 300.0f;
	Xpos.x += 580.0f;
	m_spriteRender8->SetPosition(Xpos);
	//フェードイン
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	//クリア状況
	m_cstate = FindGO<ClearState>("ClearState");
	//船状況
	m_shipstate = FindGO<ShipState>("ShipState");
	//ステージ未開放スプライト
	m_PleaseClearS00 = NewGO<prefab::CSpriteRender>(0);
	//Player
	m_player = NewGO<Player>(0, "Player");
	return true;
}


void SpaceMap::Update() {
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

	//開放されていないステージを見えないようにする
	if (m_cstate->m_StageCleared[0]) {
		m_PlanetModel0->Init(L"modelData/Planet0.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	else {
		m_PlanetModel0->Init(L"modelData/Planet0Seacret.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	if (m_cstate->m_StageCleared[1]) {
		m_PlanetModel2->Init(L"modelData/Planet02.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	else {
		m_PlanetModel2->Init(L"modelData/Planet0Seacret.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	if (m_cstate->m_StageCleared[2]) {
		m_PlanetModel3->Init(L"modelData/Planet03.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	else {
		m_PlanetModel3->Init(L"modelData/Planet0Seacret.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	if (m_cstate->m_StageCleared[3]) {
		m_PlanetModel4->Init(L"modelData/Planet04.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	else {
		m_PlanetModel4->Init(L"modelData/Planet0Seacret.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}

	//選択中のStage番号を表示
	if (m_cstate->nowStage != 4) {
		m_StageSprite->Init(L"sprite/StageText.dds", 600.0f, 300.0f);
	}
	else {
		m_StageSprite->Init(L"sprite/False.dds", 600.0f, 300.0f);

	}
	if (m_cstate->nowStage == 4) {
		m_StageSprite->Init(L"sprite/GameClearSprite.dds", 600.0f, 300.0f);
	}
	else if (m_cstate->nowStage == 0) {
		m_Snum->Init(L"sprite/00Text.dds", 500.0f, 300.0f);
	}
	else if (m_cstate->nowStage == 1) {
		m_Snum->Init(L"sprite/01Text.dds", 500.0f, 300.0f);
	}
	else if (m_cstate->nowStage == 2) {
		m_Snum->Init(L"sprite/02Text.dds", 500.0f, 300.0f);
	}
	else if (m_cstate->nowStage == 3) {
		m_Snum->Init(L"sprite/03Text.dds", 500.0f, 300.0f);
	}
	if (m_cstate->nowStage == 4) {
		m_Snum->Init(L"sprite/False.dds", 500.0f, 300.0f);
	}

	nStage = m_cstate->nowStage;
	if (Pad(0).IsTrigger(enButtonRight)) {
		prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
		s->Init("sound/button.wav");
		s->Play(false);
		if (m_cstate->nowStage != 4) {
			if(m_cstate->m_StageCleared[nStage])
			m_cstate->nowStage++;
		}
	}
	if (Pad(0).IsTrigger(enButtonLeft)) {
		prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
		s->Init("sound/button.wav");
		s->Play(false);
		if (m_cstate->nowStage != 0) {
			m_cstate->nowStage--;
		}
	}
	//Shipの配置
	if (m_cstate->nowStage == 0) {
		m_player->m_position =	m_earth->EarthPos;
		m_player->m_position.y += 60.0f;
	}else if (m_cstate->nowStage == 1) {
		m_player->m_position = P0Pos;
		m_player->m_position.y += 60.0f;
	}else if (m_cstate->nowStage == 2) {
		m_player->m_position = P2Pos;
		m_player->m_position.y += 60.0f;
	}
	else if (m_cstate->nowStage == 3) {
		m_player->m_position = P3Pos;
		m_player->m_position.y += 60.0f;
	}
	else if (m_cstate->nowStage == 4) {
		m_player->m_position = P4Pos;
		m_player->m_position.y += 60.0f;
	}
	//カメラターゲット
	CVector3 target = m_player->m_position;
	target.x -= 50.0f;
	target.z += 100.0f;
	CVector3 toCameraPosOld = m_toCameraPos;
	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	qRot.Multiply(m_toCameraPos);
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(m_toCameraPos);
	CVector3 pos = target + m_toCameraPos;
	CVector3 toPosDir1 = m_toCameraPos;
	toPosDir1.Normalize();
	if (toPosDir1.x	< -0.7f) {
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir1.x > 0.7f) {
		m_toCameraPos = toCameraPosOld;
	}
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.6f) {
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.6f) {
		m_toCameraPos = toCameraPosOld;
	}
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	m_springCamera.Update();

	//ステージのストーリー
	if (m_isWaitFadeout3) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<Story>(0);
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonB)) {
			prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
			s->Init("sound/button.wav");
			s->Play(false);
			if(!m_isWaitFadeout && !m_isWaitFadeout2)
				m_isWaitFadeout3 = true;
				m_fade->StartFadeOut();
			}
		}
	
	//Planets回転
	//P0
	if (rr0 == 360.0f)
		rr0 = 0.0f;
	P0Rot.SetRotationDeg(CVector3::AxisY, rr0);
	rr0 += 0.5f;
	m_PlanetModel0->SetRotation(P0Rot);
	m_PlanetModel2->SetRotation(P0Rot);
	m_PlanetModel3->SetRotation(P0Rot);
	m_PlanetModel4->SetRotation(P0Rot);
	//マップ選択
	if (m_isWaitFadeout) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<Game>(0, "Game");
			m_shipstate->m_SState = m_shipstate->IN_GAME;
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonA)) {
			prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
			s->Init("sound/start.wav");
			s->SetVolume(1.0f);
			s->Play(false);
			if (m_cstate->nowStage == 0) {
				if (!m_isWaitFadeout2 && !m_isWaitFadeout3) {
					m_isWaitFadeout = true;
					m_fade->StartFadeOut();
				}
			}
			else if (m_cstate->nowStage == 1) {
				if (m_cstate->m_StageCleared[0]) {
					if (!m_isWaitFadeout2 && !m_isWaitFadeout3) {
						m_isWaitFadeout = true;
						m_fade->StartFadeOut();
					}
				}
			}
			else if (m_cstate->nowStage == 2) {
				if (m_cstate->m_StageCleared[1]) {
					if (!m_isWaitFadeout2 && !m_isWaitFadeout3) {
						m_isWaitFadeout = true;
						m_fade->StartFadeOut();
					}
				}
			}
			else if (m_cstate->nowStage == 3) {
				if (m_cstate->m_StageCleared[2]) {
					if (!m_isWaitFadeout2 && !m_isWaitFadeout3) {
						m_isWaitFadeout = true;
						m_fade->StartFadeOut();
					}
				}
			}
		}
	}
	
	//Back (TitleScene)
	if (m_isWaitFadeout2) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<Title>(0);
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonX)) {
			prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
			s->Init("sound/start.wav");
			s->SetVolume(1.0f);
			s->Play(false);
			if(!m_isWaitFadeout && !m_isWaitFadeout3)
			m_isWaitFadeout2 = true;
			m_fade->StartFadeOut();
		}
	}
}

void SpaceMap::PostRender(CRenderContext& rc)
{
}
