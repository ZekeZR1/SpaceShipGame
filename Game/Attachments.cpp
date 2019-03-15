#include "stdafx.h"
#include "Attachments.h"
#include "ShipState.h"
#include "Player.h"

Attachments::Attachments()
{
}


Attachments::~Attachments()
{
	DeleteGO(Attachment1);
	DeleteGO(Attachment2);
	DeleteGO(Attachment3);
}

bool Attachments::Start() {
	m_ShipState = FindGO<ShipState>("ShipState");
	m_Player = FindGO<Player>("Player");
	//A1
	Attachment1 = NewGO<prefab::CSkinModelRender>(0, "Atch1");
	//A2
	Attachment2 = NewGO<prefab::CSkinModelRender>(0, "Atch2");
	//A3
	Attachment3 = NewGO<prefab::CSkinModelRender>(0, "Atch3");

	return true;
}           

void Attachments::Update() {
	switch (m_ShipState->m_SState) {
	case IN_GAME:
		A1Pos = m_Player->GetPosition();
		A1Pos.x -= setA1Pos.x;
		Attachment1->SetPosition(A1Pos);
		A2Pos = m_Player->GetPosition();
		A2Pos.x -= setA2Pos.x;
		Attachment2->SetPosition(A2Pos);
		A3Pos = m_Player->GetPosition();
		A3Pos.x -= setA3Pos.x;
		A3Pos.y -= setA3Pos.y;
		break;

	case IN_MAP:
		A1Scale = { 0.3f,0.3f,0.3f };
		A1Pos = m_Player->GetPosition();
		A1Pos.x += 35.0f;
		Attachment1->SetPosition(A1Pos);
		A1Rot.SetRotationDeg(CVector3::AxisY, 180.0f);
		Attachment1->SetRotation(A1Rot);
		Attachment1->SetScale(A1Scale);

		A2Pos = m_Player->GetPosition();
		A2Rot.SetRotationDeg(CVector3::AxisY, 180.0f);
		Attachment2->SetRotation(A2Rot);
		Attachment2->SetPosition(A2Pos);
		Attachment2->SetScale(A1Scale);

		A3Pos = m_Player->GetPosition();
		A3Pos.x += 31.0f;
		A3Pos.y -= 25.0f;
		A3Rot.SetRotationDeg(CVector3::AxisY, 180.0f);
		Attachment3->SetRotation(A3Rot);
		Attachment3->SetScale(A1Scale);
		break;
	case IN_GAMECLEAR:
		A1Pos = m_Player->GetPosition();
		A1Pos.x -= 125.0f;
		Attachment1->SetPosition(A1Pos);
		A2Pos = m_Player->GetPosition();
		A2Pos.x -= 0.0f;
		Attachment2->SetPosition(A2Pos);
		A3Pos = m_Player->GetPosition();
		A3Pos.x -= 120.0f;
		A3Pos.y -= 100.0f;
		break;
	}

	Attachment3->SetPosition(A3Pos);
	if (m_ShipState->m_1isLaserCannon) {
		Attachment1->Init(L"modelData/LaserCannon.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	if (m_ShipState->m_1isNormal) {
		Attachment1->Init(L"modelData/NormalShipAttachment.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	//Attachment2‚ÌØ‚è‘Ö‚¦
	if (m_ShipState->m_2isBarrier) {
	Attachment2->Init(L"modelData/BarrierAttachment.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	if (m_ShipState->m_2isNormal) {
		Attachment2->Init(L"modelData/NormalShipAttachment.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	//Attachment3‚ÌØ‚è‘Ö‚¦
	if (m_ShipState->m_3isGraCon) {
	Attachment3->Init(L"modelData/GravityAttachment.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
	if (m_ShipState->m_3isNormal) {
		Attachment3->Init(L"modelData/NormalShipAttachment.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	}
}