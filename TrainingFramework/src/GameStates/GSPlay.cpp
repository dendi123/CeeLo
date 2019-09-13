#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"



extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_play1");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	// Roll Button
	texture = ResourceManagers::GetInstance()->GetTexture("button_2");
	std::shared_ptr<GameButton> button1 = std::make_shared<GameButton>(model, shader, texture);
	button1->Set2DPosition(screenWidth / 2, 600);
	button1->SetSize(200, 50);
	button1->SetOnClick([](){
		//Animation::RollDice;
		
		int dice1,dice2, dice3;
		int max = 6, min = 1;
		static bool runOnce = true;

		time_t t;
		srand((unsigned)time(&t));

		dice1 = rand() % max + min;
		dice2 = rand() % max + min;
		dice3 = rand() % max + min;
		
		std::cout << "Roll: " << dice1 << dice2 << dice3;

	/*	if (runOnce)
		{
			std::cout << "Test:  " << value;
			runOnce = false;
		}*/
		});

	m_listButton1.push_back(button1);

	//text game title
	//shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	//std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	//m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	//m_score->Set2DPosition(Vector2(5, 25));

}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton1)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		break;
	}
	DWORD dwMousePosition;
	std::cout << dwMousePosition;
}

void GSPlay::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton1)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	//m_score->Draw();
	for (auto it : m_listButton1)
	{
		it->Draw();
	}
}

void GSPlay::SetNewPostionForBullet()
{
}

//void GSPlay::rollDice()
//{
//	int value;
//	int max = 6, min = 1;
//
//	value = rand() % (max - min + 1) + min;
//
//	std::cout << value;
//}