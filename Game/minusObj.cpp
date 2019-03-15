#include "stdafx.h"
#include "minusObj.h"
#include "Player.h"
#include "HelthMeter.h"
#include "Laserbeam.h"
#include "ClearState.h"
#include "ShipState.h"
#include "FuelMeter.h"

minusObj::minusObj()
{
}


minusObj::~minusObj()
{
	DeleteGO(m_skinModelRender);
}

bool minusObj::Start() {
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Stone.cmo");
	m_cstate = FindGO<ClearState>("ClearState");
	if (m_cstate->nowStage == 3) {
		pos.z = -4500.0f;
	}
	else {
		pos.z = -5000.0f;
	}
	m_skinModelRender->SetPosition(pos);
	m_helthm = FindGO<HelthMeter>("HPMeter");
	CVector3 scale = { 5.5f, 5.5f, 5.5f };
	m_skinModelRender->SetScale(scale);
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_skinModelRender->SetRotation(qRot);
	m_player = FindGO<Player>("Player");
	m_laserbeam = FindGO<Laserbeam>("Laserbeam");
	m_cstate = FindGO<ClearState>("ClearState");
	m_ShipState = FindGO<ShipState>("ShipState");
	return true;
}

void minusObj::Update() {
	if (!m_cstate->menu) {
		pos += moveSpeed;
		m_skinModelRender->SetPosition(pos);
		m_timer++;
		if (m_cstate->nowStage == 0) {
			if (m_timer == 200) {
				DeleteGO(this);
			}
		}
		else {
			if (m_timer == 150) {
				DeleteGO(this);
			}
		}
	}
	//プレイヤーと当たった時
	QueryGOs<Player>("Player", [&](Player* player)->bool {
		CVector3 diffp = player->GetPosition() - pos;
		if (diffp.Length() < 230.0f) {
			prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
			effect->Play(L"effect/Test02.efk");
			CVector3 emitPos = pos;
			CVector3 scale = { 50.0f, 50.0f, 50.0f };
			effect->SetScale(scale);
			effect->SetPosition(emitPos);
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init("sound/bomb4.wav");
			ss->Play(false);
			if (m_ShipState->m_BarrierActive) {
				if (FindGO<FuelMeter>("FMeter")->rot < 90.0f) {
					m_cstate->DamagePoint += 1;
					m_helthm->rot += 2.0f;
				}
			}else if (m_helthm->rot <= 180.0f) {
				if (m_helthm->rot <= 165) {
					m_helthm->rot += 15.0f;
					m_cstate->DamagePoint += 2;
				}
				else {
					double r = 180.0f - m_helthm->rot;
					m_helthm->rot += r + 1.0f;
				}
			}
			DeleteGO(this);
			return false;
		}
		return true;
	});
	//レーザに焼き払われた時
	QueryGOs<Laserbeam>("Laserbeam", [&](Laserbeam* laser)->bool {
		CVector3 diffl = laser->m_LaserPos - pos;
		if (diffl.Length() < 250.0f) {	
			prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
			effect->Play(L"effect/Test02.efk");
			CVector3 emitPos = pos;
			CVector3 scale = { 50.0f, 50.0f, 50.0f };
			effect->SetScale(scale);
			effect->SetPosition(emitPos);
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init("sound/bomb4.wav");
			ss->Play(false);
			DeleteGO(this);					
			return false;
		}
		return true;
	});
}


