/*!
* @brief	îwåi
*/

#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
}
BackGround::~BackGround()
{
	DeleteGO(m_skinModelRender);
}

bool BackGround::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/waprback2.cmo");
	m_skinModelRender->SetShadowCasterFlag(false);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_skinModelRender->SetPosition(pos);
	qRot.SetRotationDeg(CVector3::AxisX, 0.0f);
	m_skinModelRender->SetRotation(qRot);
	return true;
}

void BackGround::Update() {
	m_skinModelRender->SetPosition(pos);
}