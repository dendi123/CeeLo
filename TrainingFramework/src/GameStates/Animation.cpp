#include "Animation.h"

Animation::Animation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float delayTime)
	: Sprite2D(model, shader, texture), m_numFrames(numFrames), m_delayTime(delayTime)
{

}

Animation::~Animation()
{}

void Animation::PlayAnimation()
{
	m_currentFrame = 0;
	m_currentDisplayTime = 0.0f;
}

void Animation::Update(float deltatTime)
{
	m_currentDisplayTime += deltatTime;
	if (m_currentDisplayTime >= m_delayTime)
	{
		m_currentFrame++;
		if (m_currentFrame > m_numFrames)
		{
			m_currentFrame = 0;
		}
	}
}

void Animation::RollDice()
{
	int value;
	int max = 6, min = 1;
	static bool runOnce = true;

	//value = rand() % (max - min + 1) + min;

	time_t t;
	srand((unsigned)time(&t));

	value = rand() % max + min;

	if (runOnce)
	{
		std::cout << "Test:  " << value;
		runOnce = false;
	}
}
