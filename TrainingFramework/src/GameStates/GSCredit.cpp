#include "GSCredit.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

//SoLoud::Soloud* GSIntro::soloud = new SoLoud::Soloud;

GSCredit::GSCredit()
{

}


GSCredit::~GSCredit()
{
}


void GSCredit::Init()
{
	/*soloud->init();
	introsong.load("../Data/sfx/Ceb.mp3");
	soloud->play(introsong);*/

	 //image

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("credit");
	
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	// back

	texture = ResourceManagers::GetInstance()->GetTexture("back");
	std::shared_ptr<GameButton> m_Back = std::make_shared<GameButton>(model, shader, texture);
	m_Back->Set2DPosition(50 , 50); //285
	m_Back->SetSize(68, 68);
	m_Back->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
	});
	m_listButton.push_back(m_Back);



}

void GSCredit::Exit()
{

}


void GSCredit::Pause()
{

}

void GSCredit::Resume()
{

}


void GSCredit::HandleEvents()
{

}

void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		if ((it)->IsVisible())
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle())
			{
				break;
			}
		}
	}
}

void GSCredit::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	//m_Back->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	//if
}

void GSCredit::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
