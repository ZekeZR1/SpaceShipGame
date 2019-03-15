#include "stdafx.h"
#include "plusObj.h"
#include "Player.h"
#include "FuelMeter.h"
#include "GameClear.h"
#include "ClearState.h"

plusObj::plusObj()
{
}


plusObj::~plusObj()
{
	DeleteGO(m_skinModelRender);
}

bool plusObj::Start() {
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/plus.cmo"); //, nullptr, 0, CSkinModel::enFbxUpAxisY);
	CVector3 scale = { 10.0f, 10.0f, 10.0f };
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(pos);
	player = FindGO<Player>("Player");
	m_cstate = FindGO<ClearState>("ClearState");
	return true;
}

void plusObj::Update() {
	prefab::CSoundSource* ss;
	//回転
	if (rr == 360.0f)
		rr = 0.0f;
	qRot.SetRotationDeg(CVector3::AxisY, rr);
	rr += 10.0f;
	m_skinModelRender->SetRotation(qRot);
	//移動
	if (!(m_cstate->menu)) {
		pos.z += 30.0f;
		m_skinModelRender->SetPosition(pos);
		m_timer++;
		if (m_timer == 178) {
			m_cstate->LostedPoint++;
			DeleteGO(this);
		}
	}
	//プレイヤーと当たった時1
	QueryGOs<Player>("Player", [&](Player* player)->bool {
		CVector3 diffp = player->GetPosition() - pos;
		if (diffp.Length() < 230.0f) {
			//エフェクト
			prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
			effect->Play(L"effect/charge01.efk");
			CVector3 emitPos = pos;
			CVector3 scale = { 50.0f, 50.0f, 50.0f };
			effect->SetScale(scale);
			//emitPos.y += 10.0f;
			effect->SetPosition(emitPos);
			//SE
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init("sound/charge.wav");
			ss->Play(false);
			//処理
			FindGO<FuelMeter>("FMeter")->plusFuel();

			DeleteGO(this);
			return false;
		}
		return true;
	});
}