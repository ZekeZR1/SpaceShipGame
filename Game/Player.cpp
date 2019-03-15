#include "stdafx.h"
#include "Player.h"
#include "Title.h"
#include "HelthMeter.h"
#include "FuelMeter.h"
#include "ShipState.h"
#include "Laserbeam.h"
#include "ClearState.h"

Player::Player()
{
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
}

bool Player::Start() {
	//m_animClips[enAnimationClip_Idle].Load(L"animData/AnimSpaceShipIdle.tka");
	//m_animClips[enAnimationClip_Idle].SetLoopFlag(true);	
	//m_animClips[enAnimationClip_Right].Load(L"animData/AnimSpaceShipRight.tka");
	//m_animClips[enAnimationClip_Right].SetLoopFlag(true);

	m_position.y += 120.0f;
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/AnimSpaceShip.cmo", nullptr, 0, CSkinModel::enFbxUpAxisY);
	m_skinModelRender->SetRotation(rotation);
	m_hpmeter = FindGO<HelthMeter>("HPMeter");
	m_ShipState = FindGO<ShipState>("ShipState");
	m_cstate = FindGO<ClearState>("ClearState");
	charaCon.Init(
		25.0f,
		100.0f,
		m_position
	);
	return true;
}


void Player::AnimationControl() {
	//m_skinModelRender->PlayAnimation(enAnimationClip_Idle);

	/*
	if (Pad(0).IsPress(enButtonRight)) {
		m_skinModelRender->PlayAnimation(enAnimationClip_Right);
	}else{
		m_skinModelRender->PlayAnimation(enAnimationClip_Idle);
	}
	*/
}

void Player::Move() {
	prefab::CSoundSource* ss;
	float fSpeed = 12.0f;
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	if (Pad(0).IsPress(enButtonB)) {
		if (FindGO<FuelMeter>("FMeter")->rot < 90.0f) {
			ss = NewGO<prefab::CSoundSource>(0);
			//ss->Init("sound/magic4.wav");
			ss->Init("sound/baseSe.wav");
			ss->Play(false);
			fSpeed *= 2.0f;
			FindGO<FuelMeter>("FMeter")->useFuel();
		}
	}
	if (Pad(0).IsPress(enButtonLeft)) { 
		if (m_position.x > 475.0f) {
			moveSpeed.x = 0.0f;
		}else {
			moveSpeed.x = fSpeed;
		}
	}
	if (Pad(0).IsPress(enButtonRight)) {  
		if (m_position.x < -480.0f) {
			moveSpeed.x = 0.0f;
		}else {
			moveSpeed.x -= fSpeed;
		}
	}
	if (Pad(0).IsPress(enButtonDown)) {
		if (m_position.z > 200) {
			moveSpeed.z = 0.0f;
		}else {
			moveSpeed.z = fSpeed;
		}
	}
	if (Pad(0).IsPress(enButtonUp)) {
		if (m_position.z < -3000.0f) {
			moveSpeed.z = 0.0f;
		}else {
			moveSpeed.z = -fSpeed;
		}
	}
	if (Pad(0).IsTrigger(enButtonA)) {	
		moveSpeed.y = 30.0f;
	}
	if (m_position.y > 555.0f) {
	moveSpeed.y = -1.5f;
	}
	if (m_position.y < -650.0f) {
		m_hpmeter->LimitMeter();
	}

	moveSpeed.y -= 1.5f;
	m_position = charaCon.Execute(1.0f, moveSpeed);
	m_skinModelRender->SetPosition(m_position);
}

void Player::Skill() {
	if (Pad(0).IsTrigger(enButtonRB1)) {
		if (m_ShipState->m_1isLaserCannon) {
			if (FindGO<FuelMeter>("FMeter")->rot <= 85.0f) {
				NewGO<Laserbeam>(0, "Laserbeam");
				prefab::CSoundSource* m_sound;
				m_sound = NewGO<prefab::CSoundSource>(0);
				m_sound->Init("sound/laser5.wav");
				m_sound->Play(false);
				FindGO<FuelMeter>("FMeter")->useLaser();
			}
		}
	}
	if (Pad(0).IsPress(enButtonLB1)) {
		if (m_ShipState->m_2isBarrier) {
			if (FindGO<FuelMeter>("FMeter")->rot < 90.0f) {
				m_ShipState->m_BarrierActive = true;
				FindGO<FuelMeter>("FMeter")->useShield();
				prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
				CVector3 scale = { 600.0f, 600.0f, 600.0f };
				effect->SetScale(scale);
				effect->Play(L"effect/ShieldKai.efk");
				emitPos = GetPosition();
				effect->SetPosition(emitPos);
				prefab::CSoundSource* ss;
				ss = NewGO<prefab::CSoundSource>(0);
				ss->Init("sound/shieldSe.wav");
				ss->Play(false);
			}
		}
	}
	else {
		m_ShipState->m_BarrierActive = false;
	}
	if (Pad(0).IsPress(enButtonX)) {
		if (m_ShipState->m_3isGraCon) {
			moveSpeed.y -= 4.0f;
		}
	}
}
void Player::Update() {
	switch (m_ShipState->m_SState) {
	case IN_GAME:
		if (!m_cstate->menu) {
			Move();
			Skill();
			m_scale = { 1.0f,1.0f,1.0f };
			m_skinModelRender->SetScale(m_scale);
			//AnimationControl();
		}
		break;
	case IN_MAP:
		m_skinModelRender->SetPosition(m_position);
		m_scale = { 0.3f,0.3f,0.3f };
		m_skinModelRender->SetScale(m_scale);
		rotation.SetRotationDeg(CVector3::AxisY, 180.0f);
		m_skinModelRender->SetRotation(rotation);
		break;
	case IN_GAMEOVER:
		break;
	case IN_GAMECLEAR:
		m_position.z = -50.0f;
		m_position.x = 250.0f;
		m_position.y = -25.0f;
		m_skinModelRender->SetPosition(m_position);
		break;
	}
}