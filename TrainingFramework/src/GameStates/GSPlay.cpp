#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "string.h"



extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

int GSPlay::wallet = 100;
int GSPlay::tempWallet = wallet;
int GSPlay::pot = 0;
int GSPlay::tempPot = 0;

SoLoud::Soloud* GSPlay::soloud = new SoLoud::Soloud;

GSPlay::GSPlay()
{
	Sleep(1000); 
} 


GSPlay::~GSPlay()
{

}

int GSPlay::WalletDec(int a)
{
	wallet = wallet - a;
	return wallet;
}

void GSPlay::Init()
{

	soloud->init();
	playsong.load("../Data/sfx/ggbet.mp3");
	soloud->play(playsong);

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
		wallet = tempWallet;
		pot = tempPot;
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Roll);
		});
	m_listButton1.push_back(button);

	// Wage Button
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 120, 600); // 400
	button->SetSize(200, 50); // 200 , 50
	button->SetOnClick([]() {
		if (pot > 0)
		{
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Roll);
		}
	});
	m_listButton1.push_back(button);




	// Chip 10

	texture = ResourceManagers::GetInstance()->GetTexture("chip10");
	std::shared_ptr<GameButton> chip = std::make_shared<GameButton>(model, shader, texture);
	chip->Set2DPosition(170, screenHeight / 2);
	chip->SetSize(150, 150);
	chip->SetOnClick([]()
	{
		if (wallet >= 10)
		{
		wallet = wallet - 10;
		pot = pot + 10;
		}
	});
	m_listChip.push_back(chip);

	// Chip 25

	texture = ResourceManagers::GetInstance()->GetTexture("chip20");
	chip = std::make_shared<GameButton>(model, shader, texture);
	chip->Set2DPosition(370, screenHeight / 2);
	chip->SetSize(150, 150);
	chip->SetOnClick([]()
	{
		if (wallet >= 20)
		{
			wallet = wallet - 20;
			pot = pot + 20;
		}
	});
	m_listChip.push_back(chip);

	// Chip 50

	texture = ResourceManagers::GetInstance()->GetTexture("chip50");
	chip = std::make_shared<GameButton>(model, shader, texture);
	chip->Set2DPosition(570, screenHeight / 2);
	chip->SetSize(150, 150);
	chip->SetOnClick([]()
	{
		if (wallet >= 50)
		{
			wallet = wallet - 50;
			pot = pot + 50;
		}
	});
	m_listChip.push_back(chip);

	// Chip 100
	texture = ResourceManagers::GetInstance()->GetTexture("chip100");
	chip = std::make_shared<GameButton>(model, shader, texture);
	chip->Set2DPosition(770, screenHeight / 2);
	chip->SetSize(150, 150);
	chip->SetOnClick([]()
	{
		if (wallet >= 100)
		{
			wallet = wallet - 100;
			pot = pot + 100;
		}
	});
	m_listChip.push_back(chip);

	// Icon

	texture = ResourceManagers::GetInstance()->GetTexture("wallet");
	std::shared_ptr<Sprite2D> icon = std::make_shared<Sprite2D>(model, shader, texture);
	icon->Set2DPosition(495, 55);
	icon->SetSize(220, 80);
	m_listIcon.push_back(icon);




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

	// Big Title

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font1 = ResourceManagers::GetInstance()->GetFont("botonB");
	text = std::make_shared<Text>(shader, font1, "Place Your Bet", TEXT_COLOR::WHILE, 2);
	text->Set2DPosition(Vector2(335, 150));
	m_listText1.push_back(text);

	// Wallet

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	walletText = std::make_shared<Text>(shader, font, "", TEXT_COLOR::WHILE, 1);
	walletText->Set2DPosition(Vector2(455, 65));


	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	potText = std::make_shared<Text>(shader, font, "", TEXT_COLOR::WHILE, 1);
	potText->Set2DPosition(Vector2(780, 65));

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

void GSPlay::HandleTouchEvents(int x, int y, bool IsPressed)
{
	for (auto it : m_listButton1)
	{
		if ((it)->IsVisible())
		{
			(it)->HandleTouchEvents(x, y, IsPressed);
			if ((it)->IsHandle())
			{
				soloud->deinit();
				break;
			}
		}
	}

	for (auto it : m_listChip)
	{
			(it)->HandleTouchEvents(x, y, IsPressed);
				if ((it)->IsHandle()) break;
	}
}

void GSPlay::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton1)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listChip)
	{
		it->Update(deltaTime);
	}

	std::stringstream stream;
	stream << wallet;
	std::string temp = "" + stream.str();
	walletText->setText(temp);

	std::stringstream stream1;
	stream1 << pot;
	std::string temp1 = "Pot: " + stream1.str();
	potText->setText(temp1);
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
	for (auto it : m_listIcon)
	{
		it->Draw();
	}
	for (auto it : m_listText1)
	{
		it->Draw();
	}
	for (auto it : m_listChip)
	{
		it->Draw();
	}

	walletText->Draw();
	potText->Draw();

}

