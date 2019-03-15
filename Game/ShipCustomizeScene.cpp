#include "stdafx.h"
#include "ShipCustomizeScene.h"
#include "ShipState.h"
#include "ClearState.h"
#include "Title.h"
#include "Fade.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"

ShipCustomizeScene::ShipCustomizeScene()
{
}


ShipCustomizeScene::~ShipCustomizeScene()
{
	DeleteGO(ptLight);
	DeleteGO(m_lineSprite);
	DeleteGO(m_BackGround);
	DeleteGO(m_ShipModel);
	DeleteGO(Attachment1);
	DeleteGO(Attachment2);
	DeleteGO(Attachment3);
	DeleteGO(m_NowA1Sprite);
	DeleteGO(m_NowA2Sprite);
	DeleteGO(m_NowA3Sprite);
	DeleteGO(m_spriteRender8);
	DeleteGO(m_spriteRender9);
	DeleteGO(m_InfoSprite);
	DeleteGO(m_BackSprite);
	DeleteGO(m_BackSprite2);
	DeleteGO(m_UsingSprite1);
	DeleteGO(m_UsingSprite2);
	DeleteGO(m_UsingSprite3);
	DeleteGO(m_bgm);
}

bool ShipCustomizeScene::Start() {
	//カメラ
	tkEngine::MainCamera().SetNear(0.1f);
	tkEngine::MainCamera().SetFar(20000.0f);
	tkEngine::MainCamera().SetPosition({ 300.0f, 700.0f, 500.0f });
	m_toCameraPos.Set(-20.0f, 5.0f, 100.0f);
	m_springCamera.Init(
		MainCamera(),
		1000.0f,
		true,
		5.0f
	);
	tkEngine::MainCamera().Update();
	//BGM
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init("sound/custombgm1.wav");
	//現在のShipとクリア状況
	m_ShipState = FindGO<ShipState>("ShipState");
	m_cstate = FindGO<ClearState>("ClearState");
	//ポイントライト
	ptLight = NewGO<prefab::CPointLight>(0);
	ptLight->SetPosition(ptLpos);
	ptLight->SetColor({ 10.5f, 10.5f, 10.5f, 1.0f });
	attn.x = 500.0f;		
	attn.y = 100.0f;
	ptLight->SetAttn(attn);
	//背景
	m_BackGround = NewGO<prefab::CSkinModelRender>(0);
	m_BackGround->Init(L"modelData/CustomizeSceneBack.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	m_BackGround->SetPosition(m_BackPos);
	m_BackScale = { 1.0f, 1.0f, 1.0f };
	m_BackGround->SetScale(m_BackScale);
	//カスタマイズ用Ship
	m_ShipModel = NewGO<prefab::CSkinModelRender>(0, "Ship");
	m_ShipModel->Init(L"modelData/AnimSpaceShip.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	m_ShipPos.x -= 30.0f;
	m_ShipModel->SetPosition(m_ShipPos);
	m_ShipScale = { 0.3f, 0.3f, 0.3f };
	m_ShipModel->SetScale(m_ShipScale);
	m_ShipRot.SetRotationDeg(CVector3::AxisY, 180.0f);
	m_ShipModel->SetRotation(m_ShipRot);
	//Attachmentのモデル
	//新しいモデルを作成する際はNormalAttachmentをインポートして座標を合わせて作成して下さい
	//A1
	Attachment1 = NewGO<prefab::CSkinModelRender>(0, "Atch1");
	A1Pos.x = 3.0f;
	Attachment1->SetPosition(A1Pos);
	A1Scale = { 0.3f, 0.3f, 0.3f };
	Attachment1->SetScale(A1Scale);
	A1Rot.SetRotationDeg(CVector3::AxisY, 180.0f);
	Attachment1->SetRotation(A1Rot);
	//A2
	Attachment2 = NewGO<prefab::CSkinModelRender>(0, "Atch2");
	A2Pos.x = -25.0f;
	Attachment2->SetPosition(A2Pos);
	A2Scale = { 0.3f, 0.3f, 0.3f };
	Attachment2->SetScale(A2Scale);
	A2Rot.SetRotationDeg(CVector3::AxisY, 180.0f);
	Attachment2->SetRotation(A2Rot);
	//A3
	Attachment3 = NewGO<prefab::CSkinModelRender>(0, "Atch3");
	A3Pos.x =  3.0f;
	A3Pos.y = -23.0f;
	Attachment3->SetPosition(A3Pos);
	A3Scale = { 0.3f, 0.3f, 0.3f };
	Attachment3->SetScale(A3Scale);
	A3Rot.SetRotationDeg(CVector3::AxisY, 180.0f);
	Attachment3->SetRotation(A3Rot);
	//Sprite
	//Back
	m_BackSprite = NewGO<prefab::CSpriteRender>(0);
	m_BackSprite->Init(L"sprite/CutomizeBackSprite.dds", 800.0f, 500.0f);
	BackSpritePos.x -= 250.0f;
	BackSpritePos.y = 60.0f;
	m_BackSprite->SetPosition(BackSpritePos);
	//Back2
	m_BackSprite2 = NewGO<prefab::CSpriteRender>(0);
	m_BackSprite2->Init(L"sprite/UsingAtchSpriteBack.dds", 480.0f, 300.0f);
	BackSpritePos2.x -= 100.0f;
	BackSpritePos2.y = -170.0f;
	m_BackSprite2->SetPosition(BackSpritePos2);
	//UsingSprite
	m_UsingSprite1 = NewGO<prefab::CSpriteRender>(0);
	UsingSpritePos1.x -= 100.0f;
	UsingSpritePos1.y = -170.0f;
	m_UsingSprite1->SetPosition(UsingSpritePos1);
	//2
	m_UsingSprite2 = NewGO<prefab::CSpriteRender>(0);
	UsingSpritePos2.x -= 100.0f;
	UsingSpritePos2.y = -170.0f;
	m_UsingSprite2->SetPosition(UsingSpritePos2);
	//3
	m_UsingSprite3 = NewGO<prefab::CSpriteRender>(0);
	UsingSpritePos3.x -= 100.0f;
	UsingSpritePos3.y = -170.0f;
	m_UsingSprite3->SetPosition(UsingSpritePos3);
	//Line
	m_lineSprite = NewGO<prefab::CSpriteRender>(0);
	m_linePos.x -= 250.0f;
	m_linePos.y = 30.0f;
	m_lineSprite->SetPosition(m_linePos);
	m_lineSprite->Init(L"sprite/Line1.dds", 800.0f, 500.0f );
	//NowAttachmentSprite
	m_NowA1Sprite = NewGO<prefab::CSpriteRender>(0);
	m_NowA1SpritePos.x = -250.0f;
	m_NowA1SpritePos.y = 60.0f;
	m_NowA1Sprite->SetPosition(m_NowA1SpritePos);
	//NowA2
	m_NowA2Sprite = NewGO<prefab::CSpriteRender>(0);
	m_NowA2SpritePos.x = -250.0f;
	m_NowA2SpritePos.y = -70.0f;
	m_NowA2Sprite->SetPosition(m_NowA2SpritePos);
	//NowA3
	m_NowA3Sprite = NewGO<prefab::CSpriteRender>(0);
	m_NowA3SpritePos.x = -250.0f;
	m_NowA3SpritePos.y = -190.0f;
	m_NowA3Sprite->SetPosition(m_NowA3SpritePos);
	//Attachment Infomation
	m_InfoSprite = NewGO<prefab::CSpriteRender>(0);
	m_InfoPos.x = 405.0f;
	m_InfoPos.y = 250.0f;
	m_InfoSprite->SetPosition(m_InfoPos);
	//DirectionalPad説明
	m_spriteRender9 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender9->Init(L"sprite/Dpad.dds", 200.0f, 100.0f);
	Dpos.y -= 300.0f;
	Dpos.x += 350.0f;
	m_spriteRender9->SetPosition(Dpos);
	//Xボタン説明
	m_spriteRender8 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender8->Init(L"sprite/Xbutton.dds", 200.0f, 100.0f);
	Xpos.y -= 300.0f;
	Xpos.x += 500.0f;
	m_spriteRender8->SetPosition(Xpos);
	//フェード
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}


void ShipCustomizeScene::Update() {
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
	//カメラ
	CVector3 target = m_ShipPos;
	target.x += 65.0f;
	target.y += 10.0f;
	target.z += 30.0f;
	CVector3 toCameraPosOld = m_toCameraPos;
	float x = 0.0f;
	float y = 0.0f;
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	qRot.Multiply(m_toCameraPos);
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(m_toCameraPos);
	CVector3 pos = target + m_toCameraPos;
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	m_springCamera.Update();
	
	//パッド操作処理
	if (Pad(0).IsTrigger(enButtonDown)) {
		if (Line != 2) {
			Line++;
		}
		prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
		s->Init("sound/button.wav");
		s->Play(false);
	}
	if (Pad(0).IsTrigger(enButtonUp)) {
		if (Line != 0) {
			Line--;
		}
		prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
		s->Init("sound/button.wav");
		s->Play(false);
	}
	if (Pad(0).IsTrigger(enButtonRight) && Line == 0) {
		if (m_cstate->m_StageCleared[0]) {
			m_ShipState->m_1isLaserCannon = true;
			m_ShipState->m_1isNormal = false;

		}
		prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
		s->Init("sound/button.wav");
		s->Play(false);
	}
	if (Pad(0).IsTrigger(enButtonLeft) && Line == 0) {
		m_ShipState->m_1isLaserCannon = false;
		m_ShipState->m_1isNormal = true;
		prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
		s->Init("sound/button.wav");
		s->Play(false);
	}

	if (Pad(0).IsTrigger(enButtonRight) && Line == 1) {
		if (m_cstate->m_StageCleared[1]) {
			m_ShipState->m_2isBarrier = true;
			m_ShipState->m_2isNormal = false;
		}
		prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
		s->Init("sound/button.wav");
		s->Play(false);
	}
	if (Pad(0).IsTrigger(enButtonLeft) && Line == 1) {
		m_ShipState->m_2isBarrier = false;
		m_ShipState->m_2isNormal = true;
		prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
		s->Init("sound/button.wav");
		s->Play(false);
	}
	if (Pad(0).IsTrigger(enButtonRight) && Line == 2) {
		if (m_cstate->m_StageCleared[2]) {
			m_ShipState->m_3isGraCon = true;
			m_ShipState->m_3isNormal = false;
		}
		prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
		s->Init("sound/button.wav");
		s->Play(false);
	}
	if (Pad(0).IsTrigger(enButtonLeft) && Line == 2) {
		m_ShipState->m_3isGraCon = false;
		m_ShipState->m_3isNormal = true;
		m_InfoSprite->Init(L"sprite/False.dds", 400.0f, 200.0f);
		prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
		s->Init("sound/button.wav");
		s->Play(false);
	}
	//
	if (m_isWaitFadeout) {
		m_bgm->SetVolume(m_intiBgmVolume*(1.0f - m_fade->GetCurrentAlpha()));
		if (!m_fade->IsFade()) {
			NewGO<Title>(0);
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonX)) {
			prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
			s->Init("sound/button.wav");
			s->Play(false);
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
	//Lineの位置
	if (Line == 0) {
		m_linePos.y = 60.0f;
		m_lineSprite->SetPosition(m_linePos);
	}
	if (Line == 1) {
		m_linePos.y = -65.0f;
		m_lineSprite->SetPosition(m_linePos);
	}
	if (Line == 2) {
		m_linePos.y = -190.0f;
		m_lineSprite->SetPosition(m_linePos);
	}
	//InfoSprite
	if (!(m_cstate->m_StageCleared[Line])) {
		m_InfoSprite->Init(L"sprite/NormalInfo.dds", 500.0f, 250.0f);
	}
	else if (Line == 0 && m_ShipState->m_1isLaserCannon) {
		m_InfoSprite->Init(L"sprite/LaserInfo.dds", 500.0f, 250.0f);
	}
	else if (Line == 1 && m_ShipState->m_2isBarrier) {
		m_InfoSprite->Init(L"sprite/ShieldInfo.dds", 500.0f, 250.0f);
	}
	else if (Line == 2 && m_ShipState->m_3isGraCon) {
		m_InfoSprite->Init(L"sprite/GraConInfo.dds", 500.0f, 250.0f);
	}
	else {
		m_InfoSprite->Init(L"sprite/False.dds", 500.0f, 250.0f);
	}
	//Attachment1の切り替え
	if (m_ShipState->m_1isLaserCannon) {
		Attachment1->Init(L"modelData/LaserCannon.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
		m_NowA1Sprite->Init(L"sprite/LaserATCS.dds", 800.0f, 500.0f);
		m_UsingSprite1->Init(L"sprite/Using01.dds", 480.0f, 300.0f);
	}
	else if (m_ShipState->m_1isNormal) {
		Attachment1->Init(L"modelData/NormalShipAttachment.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
		m_NowA1Sprite->Init(L"sprite/NormalATCS.dds", 800.0f, 500.0f);
		m_UsingSprite1->Init(L"sprite/False.dds", 480.0f, 300.0f);
	}
	//Attachment2の切り替え
	
	if (m_ShipState->m_2isBarrier) {
		Attachment2->Init(L"modelData/BarrierAttachment.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
		m_NowA2Sprite->Init(L"sprite/ShieldATCS.dds", 800.0f, 500.0f);
		m_UsingSprite2->Init(L"sprite/Using02.dds", 480.0f, 300.0f);
	}
	else if (m_ShipState->m_2isNormal) {
		Attachment2->Init(L"modelData/NormalShipAttachment.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
		m_NowA2Sprite->Init(L"sprite/NormalATCS.dds", 800.0f, 500.0f);
		m_UsingSprite2->Init(L"sprite/False.dds", 480.0f, 300.0f);
	}
	//Attachment3の切り替え
	if (m_ShipState->m_3isGraCon) {
		Attachment3->Init(L"modelData/GravityAttachment.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
		m_NowA3Sprite->Init(L"sprite/GraConATCS.dds", 800.0f, 500.0f);
		m_UsingSprite3->Init(L"sprite/Using03.dds", 480.0f, 300.0f);
	}
	else if (m_ShipState->m_3isNormal) {
		Attachment3->Init(L"modelData/NormalShipAttachment.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
		m_NowA3Sprite->Init(L"sprite/NormalATCS.dds", 800.0f, 500.0f);
		m_UsingSprite3->Init(L"sprite/False.dds", 480.0f, 300.0f);
	}
	
	//背景回転
	if (rr == 360.0f)
		rr = 0.0f;
	m_BackRot.SetRotationDeg(CVector3::AxisY, rr);
	rr -= 0.1f;
	m_BackGround->SetRotation(m_BackRot);

}
