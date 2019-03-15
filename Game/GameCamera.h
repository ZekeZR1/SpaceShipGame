/*!
* @brief	ゲームカメラ。
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
* @brief	ゲームカメラ。
*/
/*
class GameCamera : public IGameObject {
public:
	bool Start() override final;
	void Update() override final;
	*/
	/*!
	*@brief	視点を取得。
	*/
/*
	CVector3 GetPosition() const
	{
		return m_springCamera.GetPosition();
	}
	*/
	/*!
	*@brief	注視点を取得。
	*/
	/*
	CVector3 GetTarget() const
	{
		return m_springCamera.GetTarget();
	}
private:


private:
	CSpringCamera m_springCamera;				//!<バネカメラ。
	Player* m_player = nullptr;				//!<プレイヤ。
	float m_toCameraPosDist;					//!<注視点から視点までの距離。
};
*/