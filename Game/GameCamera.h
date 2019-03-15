/*!
* @brief	�Q�[���J�����B
*/

#pragma once

#pragma once

#include "Player.h"
#include "tkEngine/camera/tkSpringCamera.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	Player* m_player;
	CVector3 m_toCameraPos;	
	CSpringCamera m_springCamera;
};


//#include "tkEngine/camera/tkSpringCamera.h"

//class Player;

/*!
* @brief	�Q�[���J�����B
*/
/*
class GameCamera : public IGameObject {
public:
	bool Start() override final;
	void Update() override final;
	*/
	/*!
	*@brief	���_���擾�B
	*/
/*
	CVector3 GetPosition() const
	{
		return m_springCamera.GetPosition();
	}
	*/
	/*!
	*@brief	�����_���擾�B
	*/
	/*
	CVector3 GetTarget() const
	{
		return m_springCamera.GetTarget();
	}
private:


private:
	CSpringCamera m_springCamera;				//!<�o�l�J�����B
	Player* m_player = nullptr;				//!<�v���C���B
	float m_toCameraPosDist;					//!<�����_���王�_�܂ł̋����B
};
*/