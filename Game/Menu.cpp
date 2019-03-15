#include "stdafx.h"
#include "Menu.h"
#include "Title.h"
#include "Game.h"
#include "ClearState.h"
#include "ShipState.h"
Menu::Menu()
{
}


Menu::~Menu()
{
	DeleteGO(m_spriteRenderer);
	DeleteGO(m_pickSprite);
}

bool Menu::Start() {
	m_spriteRenderer = NewGO<prefab::CSpriteRender>(0);
	m_spriteRenderer->Init(L"sprite/Menu.dds", 500.0f, 800.0f);
	m_spriteRenderer->SetPosition(m_pos);
	m_pickSprite= NewGO<prefab::CSpriteRender>(0);
	m_pickSprite->Init(L"sprite/MenuPick.dds", 500.0f, 800.0f);
	m_pickSprite->SetPosition(m_pickpos);
	m_cstate = FindGO<ClearState>("ClearState");
	m_game = FindGO<Game>("Game");
	m_shipstate = FindGO<ShipState>("ShipState");
	return true;
}

void Menu::Update() {
		if (Pad(0).IsTrigger(enButtonUp)) {
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init("sound/button.wav");
			ss->Play(false);
			if (pick != 0) {
				m_pickpos.y += 110.0f;
				pick--;
			}
		}
		if (Pad(0).IsTrigger(enButtonDown)) {
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init("sound/button.wav");
			ss->Play(false);
			if (pick != 2) {
				m_pickpos.y -= 110.0f;
				pick++;
			}
		}
		if (Pad(0).IsTrigger(enButtonA)) {
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init("sound/button.wav");
			ss->Play(false);
			if (pick == 0) {
				m_game->goTitle = true;
			}
			else if (pick == 1) {
				m_game->goMap = true;
			}
			else if (pick == 2) {
				m_game->goRetry = true;
			}
			m_cstate->menu = false;
			DeleteGO(this);
		}
		m_pickSprite->SetPosition(m_pickpos);
}