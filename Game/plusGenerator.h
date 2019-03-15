#pragma once
class ClearState;
class plusGenerator : public IGameObject
{
public:
	plusGenerator();
	~plusGenerator();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;
private:
	unsigned int m_timer;
	ClearState* m_cstate = nullptr;
	//•¶Žš•\Ž¦
	CSprite m_sprite;
	CFont m_font;
	CFont m_fontTest;
	int m_Test = 0;
};

