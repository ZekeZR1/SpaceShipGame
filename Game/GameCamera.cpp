/*!
* @brief	�Q�[���J�����B
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
		2000.0f,			//�J�����̈ړ����x�̍ő�l�B
		true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩
		30.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
	);
	return true;
}
void GameCamera::Update()
{
	//�����_���v�Z����B
	CVector3 target = m_player->m_position;
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 50.0f;
	target.z += 100.0f;
	CVector3 toCameraPosOld = m_toCameraPos;
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//Y������̉�]
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

	//X������̉�]�B
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
