#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/graphics/font/tkFont.h"
#include "GameCamera.h"

class Fade;
class BackGround;
class BackGenerator;
class BackWall;
class minsuObj;
class plusObj;
class FuelMeter;
class Player;
class Attachments;
class minusGenerator;
class plusGenerator;
class HelthMeter;
class FuelMeter;
class SpaceMap;
class ClearState;
class ShipState;
class Notify;
class BackDummy;
class Menu;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;
	void OnDestroy() override;
	void Render(CRenderContext& rc);

	int nStage = 0;
	SpaceMap* m_spacemap = nullptr;
	//BackGround* m_background = nullptr;
	BackDummy* m_backdummy = nullptr;
	BackGenerator* m_backGenerator = nullptr;
	BackWall* m_bwall = nullptr;
	GameCamera* m_gameCamera = nullptr;
	ShipState* m_shipstate = nullptr;
	Player* m_player = nullptr;
	Attachments* m_attachments = nullptr;
	plusGenerator* m_plus = nullptr;
	minusGenerator* m_minus = nullptr;
	HelthMeter* m_helth = nullptr;
	FuelMeter* m_fuel = nullptr;
	prefab::CDirectionLight* m_lig;
	CVector3 m_lightDir;
	CVector3 m_pos = CVector3::Zero;
	CVector3 m_backPos = CVector3::Zero;
	CVector3 m_backscale;
	prefab::CSoundSource* m_bgm = nullptr;
	prefab::CSoundSource* m_shipse = nullptr;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSpriteRender* m_MeterSprite = nullptr;
	CVector3 MeterPos = CVector3::Zero;
	prefab::CSpriteRender* m_PlayingSprite = nullptr;
	CVector3 PlayingPos = CVector3::Zero;
	prefab::CSpriteRender* m_JumpSprite = nullptr;
	int m_jumptimer = 0;
	int m_jumptimer1 = 0;
	CVector3 JumpPos = CVector3::Zero;
	prefab::CSpriteRender* m_StageSprite = nullptr;
	CVector3 StagePos = CVector3::Zero;
	float m_waitTimer = 0.0f;	
	Fade* m_fade = nullptr;
	enum  EnState {
		enState_FadeIn,
		enState_InGame,
	};
	EnState m_state = enState_FadeIn;
	int m_time = 0;
	int m_time1 = 0;
	bool m_isWaitFadeout = false;
	bool m_isWaitFadeout2 = false;
	bool m_isWaitFadeoutTi = false;
	bool m_isWaitFadeoutRe = false;
	bool m_isWaitFadeoutMap = false;
	bool goTitle = false;
	bool goRetry = false;
	bool goMap = false;
	float m_intiBgmVolume = 0.0f;

	ClearState* m_cstate = nullptr;
	Menu* m_menu = nullptr;
	//•¶Žš•\Ž¦
	CSprite m_sprite;
	CFont m_font;
	CFont m_fontTest;
	int m_Test = 0;
};

