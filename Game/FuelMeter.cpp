#include "stdafx.h"
#include "FuelMeter.h"
#include "GameClear.h"

FuelMeter::FuelMeter()
{
}


FuelMeter::~FuelMeter()
{
	DeleteGO(m_spriteRender);
}


bool FuelMeter::Start() {
	m_spriteRender = NewGO<prefab::CSpriteRender>(0,"FuelMeter");
	m_spriteRender->Init(L"sprite/FuelMeter1.dds", 410, 410);
	CVector3 pos = CVector3::Zero;
	pos.x = -400.0f;
	pos.y = -360.0f;
	m_spriteRender->SetPosition(pos);
	m_spriteRender->SetRotation(rotation);
	return true;
}

void FuelMeter::Update() {
	rotation.SetRotationDeg(CVector3::AxisZ, rot);
	m_spriteRender->SetRotation(rotation);
}

void FuelMeter::plusFuel() {
	rot -= 15.0f;
}

void FuelMeter::useFuel() {
	rot += 0.5f;
}

void FuelMeter::useLaser() {
	rot += 5.0f;
}

void FuelMeter::useShield() {
	rot += 0.2f;
}