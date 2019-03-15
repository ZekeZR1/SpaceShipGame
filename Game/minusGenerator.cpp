#include "stdafx.h"
#include "minusGenerator.h"
#include "minusObj.h"
#include "ClearState.h"

minusGenerator::minusGenerator()
{
}


minusGenerator::~minusGenerator()
{
	QueryGOs<minusObj>("minusObj", [&](minusObj* minuso)->bool {
		DeleteGO(minuso);
		return true;
	});
}

bool minusGenerator::Start() {
	m_cstate = FindGO<ClearState>("ClearState");
	return true;
}

void minusGenerator::Update() {
	if (!m_cstate->menu) {
		m_timer++;
	}
	if (m_timer == 6 && (m_cstate->nowStage == 0)) {
		minusObj* minusO = NewGO<minusObj>(0, "minusObj");
		float t = Random().GetRandDouble();
		minusO->pos.y = CMath::Lerp(t, -670.0f, 700.0f);
		t = Random().GetRandDouble();
		minusO->pos.x = CMath::Lerp(t, -700.0f, 700.0f);
		minusO->moveSpeed.z = 30.0f;
		m_timer = 0;
	}
	if (m_timer == 5 && (m_cstate->nowStage == 1)) {
		minusObj* minusO = NewGO<minusObj>(0, "minusObj");
		float t = Random().GetRandDouble();
		minusO->pos.y = CMath::Lerp(t, -670.0f, 700.0f);
		t = Random().GetRandDouble();
		minusO->pos.x = CMath::Lerp(t, -700.0f, 700.0f);
		minusO->moveSpeed.z = 40.0f;
		minusO->moveSpeed.y = 2.0f;
		m_timer = 0;
	}
	if (m_timer == 5 && (m_cstate->nowStage == 2)) {
		minusObj* minusO = NewGO<minusObj>(0, "minusObj");
		float t = Random().GetRandDouble();
		minusO->pos.y = CMath::Lerp(t, -670.0f, 700.0f);
		t = Random().GetRandDouble();
		minusO->pos.x = CMath::Lerp(t, -700.0f, 700.0f);
		minusO->moveSpeed.z = 70.0f;
		m_timer = 0;
	}
	if (m_timer == 7 && (m_cstate->nowStage == 3)) {
		minusO = NewGO<minusObj>(0, "minusObj");
		float t = Random().GetRandDouble();
		minusO->pos.y = CMath::Lerp(t, -670.0f, 700.0f);
		t = Random().GetRandDouble();
		minusO->pos.x = CMath::Lerp(t, -700.0f, 400.0f);
		minusO->moveSpeed.z = 50.0f;
		minusO->moveSpeed.x = 7.0f;
		minusO1 = NewGO<minusObj>(0, "minusObj");
		t = Random().GetRandDouble();
		minusO1->pos.y = CMath::Lerp(t, -670.0f, 700.0f);
		t = Random().GetRandDouble();
		minusO1->pos.x = CMath::Lerp(t, -400.0f, 700.0f);
		minusO1->moveSpeed.z = 50.0f;
		minusO1->moveSpeed.x = -7.0f;
		m_timer = 0;
	}
}