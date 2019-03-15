#include "stdafx.h"
#include "BackDummy.h"

BackDummy::BackDummy()
{
}


BackDummy::~BackDummy()
{
}
bool BackDummy::Start() {
	m_skinModelData.Load(L"modelData/waprback2.cmo");
	m_skinModel.Init(m_skinModelData);
	pos.x = -500.0f;
	pos.y = 110.0f;
	pos.z = -4500.0f;
	qRot.SetRotationDeg(CVector3::AxisX, 0.0f);
	m_phyStaticObject.CreateMeshObject(m_skinModel, pos, qRot);
	return true;
}