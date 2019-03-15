#include "stdafx.h"
#include "HelthMeter.h"
#include "Player.h"
#include "minusObj.h"
#include "minusGenerator.h"
#include "GameOver2D.h"

HelthMeter::HelthMeter()
{
}


HelthMeter::~HelthMeter()
{
	DeleteGO(m_spriteRender);
}

bool HelthMeter::Start() {
	m_spriteRender = NewGO<prefab::CSpriteRender>(0, "FuelMeter");
	m_spriteRender->Init(L"sprite/HelthMeter1.dds", 400, 400);
	CVector3 pos = CVector3::Zero;
	pos.x = -400.0f;
	pos.y = -360.0f;
	m_spriteRender->SetPosition(pos);
	rotation.SetRotationDeg(CVector3::AxisZ, 0.0f);
	m_spriteRender->SetRotation(rotation);
	m_player = FindGO<Player>("Player");
	m_minus = FindGO<minusObj>("minusObj");
	return true;
}

void HelthMeter::Update() {
	rotation.SetRotationDeg(CVector3::AxisZ, rot);
	m_spriteRender->SetRotation(rotation);
}

void HelthMeter::LimitMeter() {
	rot += 0.5f;
}