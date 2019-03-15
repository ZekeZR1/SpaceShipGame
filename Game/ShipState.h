#pragma once
class ShipState : public IGameObject
{
public:
	ShipState();
	~ShipState();

	enum SState {
		IN_GAME,
		IN_MAP,
		IN_GAMECLEAR,
		IN_GAMEOVER,
	};
	SState m_SState= IN_MAP;

	bool m_ingame = false;
	bool m_1isNormal = true;
	bool m_1isLaserCannon = false;
	bool m_2isNormal = true;
	bool m_2isBarrier = false;
	bool m_BarrierActive = false;
	bool m_3isNormal = true;
	bool m_3isGraCon = false;
};

