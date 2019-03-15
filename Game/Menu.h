#pragma once
class ClearState;
class ShipState;
class Game;
class Menu : public IGameObject
{
public:
	Menu();
	~Menu();
	bool Start();
	void Update();
	prefab::CSpriteRender* m_spriteRenderer = nullptr;
	CVector3 m_pos = CVector3::Zero;
	prefab::CSpriteRender* m_pickSprite = nullptr;
	CVector3 m_pickpos = CVector3::Zero;
	int pick = 0;
	ClearState* m_cstate = nullptr;
	Game* m_game = nullptr;
	ShipState* m_shipstate = nullptr;
};

