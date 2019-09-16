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

	// Reset Button
	texture = ResourceManagers::GetInstance()->GetTexture("button_Q");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 - 120, 600);
	button->SetSize(200, 50);
	button->SetOnClick([](){
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Roll);
		});
	m_listButton1.push_back(button);

	// Wage Button
	texture = ResourceManagers::GetInstance()->GetTexture("button_Q");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 120, 600); // 400
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Roll);
	});
	m_listButton1.push_back(button);

	// Reset Title

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("boton");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "Reset", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 165, 610));
	m_listText1.push_back(text);

	// Wager Title

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	text = std::make_shared<Text>(shader, font, "Wager", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 + 70, 610));
	m_listText1.push_back(text);

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
		if ((it)->IsVisible())
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;
		}
	}
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
	
	for (auto it : m_listButton1)
	{
		if ((it)->IsVisible())
		{
			it->Draw();
		}
	}
	for (auto it : m_listText1)
	{
		it->Draw();
	}
}
	