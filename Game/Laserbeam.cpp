#include "stdafx.h"
#include "Laserbeam.h"
#include "Attachments.h"
#include "Player.h"

Laserbeam::Laserbeam()
{
}


Laserbeam::~Laserbeam()
{
	DeleteGO(m_skinModelRender);
}

bool Laserbeam::Start() {
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Laserbeam.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	m_Player = FindGO<Player>("Player");
	m_LaserPos = m_Player->GetPosition();
	m_LaserPos.x -= 115.0f;
	m_skinModelRender->SetPosition(m_LaserPos);
	m_moveSpeed.z = -500.0f;
	prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
	effect->Play(L"effect/Laserbeam.efk");
	CVector3 emitPos = m_LaserPos;
	CQuaternion efRot = CQuaternion::Identity;
	efRot.SetRotationDeg(CVector3::AxisX, 180.0f);
	effect->SetRotation(efRot);
	CVector3 scale = { 50.0f, 50.0f, 100.0f };
	effect->SetScale(scale);
	effect->SetPosition(emitPos);
	return true;
}

void Laserbeam::Update() {
	m_LaserPos += m_moveSpeed;
	m_skinModelRender->SetPosition(m_LaserPos);
	m_timer++;
	if (m_timer == 120) {
		DeleteGO(this);
	}
}

