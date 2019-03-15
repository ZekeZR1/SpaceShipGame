#include "stdafx.h"
#include "plusGenerator.h"
#include "plusObj.h"
#include "ClearState.h"

plusGenerator::plusGenerator()
{
}


plusGenerator::~plusGenerator()
{
}

bool plusGenerator::Start(){
	m_timer = 0;
	m_cstate = FindGO<ClearState>("ClearState");
	return true;
}

void plusGenerator::Update() {
	if (!(m_cstate->menu)) {
		m_timer++;
	}
	if (m_timer == 70 && (m_cstate->nowStage == 0)) {
		m_timer = 0;
		plusObj* plusO = NewGO<plusObj>(0, "pObj");
		plusO->pos.z = -5000.0f;
		float t = Random().GetRandDouble();
		plusO->pos.y = CMath::Lerp(t, -670.0f, 700.0f);
		t = Random().GetRandDouble();
		plusO->pos.x = CMath::Lerp(t, -630.0f, 630.0f);
	}
	if (m_timer == 60 && (m_cstate->nowStage == 1)) {
		plusObj* plusO = NewGO<plusObj>(0, "pObj");
		plusO->pos.z = -5000.0f;
		float t = Random().GetRandDouble();
		plusO->pos.y = CMath::Lerp(t, -670.0f, 700.0f);
		t = Random().GetRandDouble();
		plusO->pos.x = CMath::Lerp(t, -630.0f, 630.0f);
		m_timer = 0;
	}
	if (m_timer == 60 && m_cstate->nowStage == 2) {
		plusObj* plusO = NewGO<plusObj>(0, "pObj");
		plusO->pos.z = -5000.0f;
		float t = Random().GetRandDouble();
		plusO->pos.y = CMath::Lerp(t, -670.0f, 700.0f);
		t = Random().GetRandDouble();
		plusO->pos.x = CMath::Lerp(t, -630.0f, 630.0f);
		m_timer = 0;
	}
	if (m_timer == 70 && m_cstate->nowStage == 3){
		plusObj* plusO = NewGO<plusObj>(0, "pObj");
		plusO->pos.z = -5000.0f;
		float t = Random().GetRandDouble();
		plusO->pos.y = CMath::Lerp(t, -670.0f, 700.0f);
		t = Random().GetRandDouble();
		plusO->pos.x = CMath::Lerp(t, -630.0f, 630.0f);
		m_timer = 0;
	}
}

void plusGenerator::PostRender(CRenderContext& rc) {
	/*
	wchar_t text[256];
	swprintf_s(text, L"%d", m_timer);
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	m_font.Begin(rc);
	m_font.Draw(text, { 800.0f, -250.0f }, { 0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 5.0f }, 0.0f, 1.0f);
	m_font.End(rc);
	*/
}