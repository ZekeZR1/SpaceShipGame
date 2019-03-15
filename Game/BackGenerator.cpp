#include "stdafx.h"
#include "BackGenerator.h"
#include "BackGround.h"
#include "ClearState.h"
BackGenerator::BackGenerator()
{
}


BackGenerator::~BackGenerator()
{
	DeleteGO(backg);
	DeleteGO(backg1);
	DeleteGO(backg2);
}

bool BackGenerator::Start() {
	backg = NewGO<BackGround>(0, "BackG");
	backg->pos = { -500.0f, 100.0f, -4500.0f };
	backg1 = NewGO<BackGround>(0, "BackG");
	backg1->pos = { -500.0f, 100.0f, -11500.0f };
	backg2 = NewGO<BackGround>(0, "BackG");
	backg2->pos = { -500.0f, 100.0f, -18500.0f };
	m_cstate = FindGO<ClearState>("ClearState");
	return true;
}

void BackGenerator::Update() {
	backg->pos.z += 100.0f;
	backg1->pos.z += 100.0f;
	backg2->pos.z += 100.0f;

	if (backg->pos.z >= 7000) {
		backg->pos.z = -10000.0f;
	}
	if (backg1->pos.z >= 7000) {
		backg1->pos.z = -10000.0f;
	}
	if (backg2->pos.z >= 7000) {
		backg2->pos.z = -10000.0f;
	}
	
	/*Ç‹Ç∆Ç‡Ç…ìÆÇ≠èÛë‘
	m_timer++;
	if (m_timer == 70) {
		m_timer = 0;
		BackGround* backg = NewGO<BackGround>(0, "BackG");
		m_timer = 0;
	}
	*/
}