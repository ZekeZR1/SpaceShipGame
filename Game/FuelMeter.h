#pragma once
class FuelMeter : public IGameObject
{
public:
	FuelMeter();
	~FuelMeter();
	bool Start();
	void Update();
	void plusFuel();
	void useFuel();
	void useLaser();
	void useShield();

	prefab::CSpriteRender* m_spriteRender = nullptr;
	CQuaternion rotation = CQuaternion::Identity;
	float rot = 90.0f;
};

