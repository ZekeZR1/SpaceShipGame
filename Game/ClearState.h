#pragma once
class ClearState : public IGameObject
{
public:
	ClearState();
	~ClearState();
	void Update();
	//�v���C���̃X�e�[�W
	int nowStage = 0;
	//���N���A
	bool S00firstClear = true;
	bool S01firstClear = true;
	bool S02firstClear = true;
	bool S03firstClear = true;
	//�X�e�[�W��
	bool m_StageCleared[4] = { false };
	//
	int LostedPoint = 0;
	int DamagePoint = 0;

	bool menu = false;
};

