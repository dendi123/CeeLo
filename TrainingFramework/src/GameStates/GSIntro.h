#pragma once
#include "gamestatebase.h"
#include "soloud.h"
#include "soloud_wav.h"

class GSIntro :
	public GameStateBase
{
public:
	GSIntro();
	~GSIntro();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPresed);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_logo;
	float m_time;

	static SoLoud::Soloud *soloud;
	SoLoud::Wav introsong;
};

