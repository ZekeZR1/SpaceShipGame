#include "stdafx.h"
#include "Param2D.h"
#include "Fade.h"

Param2D::Param2D()
{
}


Param2D::~Param2D()
{
	DeleteGO(m_spriteRender);
}

bool Param2D::Start() {


	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/paramText.dds", 250, 250);
	pos.x = -385.0f;
	pos.y = -330.0f;
	m_spriteRender->SetPosition(pos);
	return true;
}
