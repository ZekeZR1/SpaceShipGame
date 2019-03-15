#pragma once
class BackWall : public IGameObject
{
public:
	BackWall();
	~BackWall();
	bool Start();
	void Update();
	CQuaternion rot = CQuaternion::Identity;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	float rr = 0.0f;
};

