#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
class BackDummy : public IGameObject
{
public:
	BackDummy();
	~BackDummy();
	bool Start();
	CSkinModel 	m_skinModel;		
	CSkinModelData	m_skinModelData;
	CVector3 pos = CVector3::Zero;
	CQuaternion qRot = CQuaternion::Identity;
	CPhysicsStaticObject m_phyStaticObject;	
};

