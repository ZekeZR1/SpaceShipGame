#pragma once
class Earth : public IGameObject
{
public:
	Earth();
	~Earth();
	bool Start();
	void Update();

	float rr = 0.0f;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 EarthPos = CVector3::Zero;
	CQuaternion qRot = CQuaternion::Identity;
};

