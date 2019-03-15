/*!
* @brief	ゲームカメラ。
*/
#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
namespace {
	float TARGET_OFFSET_Y = 60.0f;
}
GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	m_toCameraPos.Set(0.0f, 0.0f, 600.0f);
	m_player = FindGO<Player>("Player");
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);

	m_springCamera.Init(
		MainCamera(),		
		2000.0f,			//カメラの移動速度の最大値。
		true,				//カメラと地形とのあたり判定を取るか
		30.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);
	return true;
}
void GameCamera::Update()
{
	//注視点を計算する。
	CVector3 target = m_player->m_position;
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 50.0f;
	target.z += 100.0f;
	CVector3 toCameraPosOld = m_toCameraPos;
	//パッドの入力を使ってカメラを回す。
	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	qRot.Multiply(m_toCameraPos);
	//
	CVector3 toPosDir1 = m_toCameraPos;
	toPosDir1.Normalize();
	if (toPosDir1.x	< -0.4f) {
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir1.x > 0.4f) {
		m_toCameraPos = toCameraPosOld;
	}
	//

	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(m_toCameraPos);
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.4f) {
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.4f) {
		m_toCameraPos = toCameraPosOld;
	}

	CVector3 pos = target + m_toCameraPos;
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);

	m_springCamera.Update();
}
