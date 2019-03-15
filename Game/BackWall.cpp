#include "stdafx.h"
#include "BackWall.h"


BackWall::BackWall()
{
}


BackWall::~BackWall()
{
	DeleteGO(m_skinModelRender);
}


bool BackWall::Start() {
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/BackWall1.cmo", nullptr, 0, CSkinModel::enFbxUpAxisZ);
	CVector3 pos = CVector3::Zero;
	pos.z = -5000.0f;
	CVector3 scale = { 30.0f, 30.0f, 30.0f };
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(pos);
	m_skinModelRender->SetRotation(rot);
	return true;
}

void BackWall::Update() {
}