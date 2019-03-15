#pragma once
class ClearState : public IGameObject
{
public:
	ClearState();
	~ClearState();
	void Update();
	//プレイ中のステージ
	int nowStage = 0;
	//初クリア
	bool S00firstClear = true;
	bool S01firstClear = true;
	bool S02firstClear = true;
	bool S03firstClear = true;
	//ステージ放
	bool m_StageCleared[4] = { false };
	//
	int LostedPoint = 0;
	int DamagePoint = 0;

	bool menu = false;
};

