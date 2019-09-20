#pragma once
#include "Sprite2D.h"
#include <time.h>

class Animation : public Sprite2D
{
private:
	int m_numFrames;
	int m_currentFrame;
	float m_delayTime;
	float m_currentDisplayTime;

public:
	Animation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float delayTime);
	~Animation();

	void Update(float deltaTime) override;
	void PlayAnimation();
	void RollDice();
};

