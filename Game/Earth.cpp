#include "stdafx.h"
#include "Earth.h"


Earth::Earth()
{
}


Earth::~Earth()
{
	DeleteGO(m_skinModelRender);
}


bool Earth::Start() {
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Earth.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	EarthPos.x += 300.0f;
	m_skinModelRender->SetPosition(EarthPos);
	return true;
}

void Earth::Update() {
	if (rr == 360.0f)
		rr = 0.0f;
	qRot.SetRotationDeg(CVector3::AxisY, rr);
	rr += 1.0f;
	m_skinModelRender->SetRotation(qRot);
}