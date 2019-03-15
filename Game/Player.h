#pragma once
#include "tkEngine/character/tkCharacterController.h"

class HelthMeter;
class ClearState;
class ShipState;

class Player : public IGameObject 
{
public:
	Player();
	~Player();
	bool Start();
	void Update();	
	void AnimationControl();
	void Move();
	void Skill();
	
	ShipState* m_ShipState = nullptr;
	ClearState* m_cstate = nullptr;
	//CAnimation m_animation;
	float m_moveSpeedWhenStartJump;			
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CQuaternion rotation = CQuaternion::Identity;
	CCharacterController charaCon;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_speed = CVector3::Zero;
	CVector3 moveSpeed = CVector3::Zero;
	CVector3 m_scale;
	CVector3 emitPos;
	HelthMeter* m_hpmeter = nullptr;
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	enum SState {
		IN_GAME,
		IN_MAP,
		IN_GAMECLEAR,
		IN_GAMEOVER,
	};


	/*
	enum EnAnimationClip {
		enAnimationClip_Right,
		enAnimationClip_Idle,
		enAnimationClip_Num,
	};
	CAnimationClip m_animClips[enAnimationClip_Num];
	*/
};

