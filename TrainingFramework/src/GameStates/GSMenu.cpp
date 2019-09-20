#include "GSMenu.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

SoLoud::Soloud* GSMenu::soloud = new SoLoud::Soloud;

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	soloud->init();
	menusong.load("../Data/sfx/xoso.mp3");
	soloud->play(menusong);


	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_VAB");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 10, 290); //285
	button->SetSize(250, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	// credit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_C");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 10, 405); // 400
	button->SetSize(250, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Credit);
	});
	m_listButton.push_back(button);


	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_Q");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 10, 520); //515
	button->SetSize(250, 100);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	// VAB game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("boton");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "Verus A Bank", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 95, 300)); //295
	m_listText.push_back(text);

	// Credit game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	text = std::make_shared<Text>(shader, font, "Credit", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth/2 - 40, 415)); //410
	m_listText.push_back(text);

	// Quit game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	text = std::make_shared<Text>(shader, font, "Quit", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 25, 530)); //525
	m_listText.push_back(text);
	//m_Text_gameName = std::make_shared< Text>(shader, font, "Verus A Bank", TEXT_COLOR::WHILE, 1.0);
	
	menusong.load("../Data/sfx/xoso.mp3");
	Resume();
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{
	soloud->init();
	soloud->play(menusong);
}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		if ((it)->IsVisible())
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle())
			{
				menusong.stop();
				soloud->deinit();
				break;
			}
		}
	}
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		if((it)->IsVisible())
		{ 
			it->Draw();
		}
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
	//m_Text_gameName->Draw();
}

