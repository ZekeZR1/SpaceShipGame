/*!
* @brief	îwåi
*/

#pragma once

#include "tkEngine/physics/tkPhysicsStaticObject.h"

class BackGround : public IGameObject {
public:
	BackGround();
	~BackGround();
	bool Start() override;
	void Update();
	int m_time = 0;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 pos;
	CQuaternion qRot;
};