#include "stdafx.h"
#include "Notify.h"
#include "ClearState.h"

Notify::Notify()
{
}


Notify::~Notify()
{
	DeleteGO(m_spriteRender);
}

bool Notify::Start() {
	m_cstate = FindGO<ClearState>("ClearState");
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->SetPosition(m_pos);
	return true;
}


void Notify::NotifyLaser() {
	m_spriteRender->Init(L"sprite/Stage00Notify.dds", 500.0f, 800.0f);
	if (!(m_cstate->m_StageCleared[0])) {
		if (m_cstate->nowStage == 00) {
			m_spriteRender->Init(L"sprite/Stage00Notify.dds", 500.0f, 800.0f);
		}
	}
}


