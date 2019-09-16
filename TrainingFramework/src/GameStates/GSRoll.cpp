#include "GSRoll.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

std::list<std::shared_ptr<Sprite2D>> m_listDice;

int turn;
int bankScore, playerScore;
int currentBScore, currentPscore;
int bankAttempts, playerAttempts = 1;

//bool isPressed = false;
//bool runOnce = true;

std::mt19937::result_type seed = time(0);

GSRoll::GSRoll()
{

}


GSRoll::~GSRoll()
{
}

int GSRoll::CalScore(std::string m_unCalScore)
{
	std::vector<int> array;
	int score;

	int num1 = std::count(m_unCalScore.begin(), m_unCalScore.end(), '1');
	array.push_back(num1);
	int num2 = std::count(m_unCalScore.begin(), m_unCalScore.end(), '2');
	array.push_back(num2);
	int num3 = std::count(m_unCalScore.begin(), m_unCalScore.end(), '3');
	array.push_back(num3);
	int num4 = std::count(m_unCalScore.begin(), m_unCalScore.end(), '4');
	array.push_back(num4);
	int num5 = std::count(m_unCalScore.begin(), m_unCalScore.end(), '5');
	array.push_back(num5);
	int num6 = std::count(m_unCalScore.begin(), m_unCalScore.end(), '6');
	array.push_back(num6);

	if (num4 == 1 && num5 == 1 && num6 == 1) score = 20;
	else if (num6 == 3 || num5 == 3 || num4 == 3 || num3 == 3)
	{
		for (int i = 0; i < array.size(); ++i)
		{
			if (array.at(i) == 3) score = (i+1) * 3;
		}
	}
	else if (num2 == 3) score = 8;
	else if (num1 == 3) score = 7;
	else if (num6 == 2 || num5 == 2 || num4 == 2 || num3 == 2 || num2 == 2 || num1 == 2)
	{
		for (int i = 0; i < array.size(); ++i)
		{
			if (array.at(i) == 1) score = (i+1);
		}
	}
	else if (num1 == 1 && num2 == 1 && num3 == 1) score = -1;
	else score = 0;

	return score;
}
int GSRoll::RollDice()
{
	//static bool runOnce = true;
	std::string unCalscore;

	auto dice_rand = bind(std::uniform_int_distribution<int>(1, 6) , std::mt19937(seed));

	int dice1 = dice_rand();
	unCalscore.push_back((dice1%10) +'0');
	int dice2 = dice_rand();
	unCalscore.push_back((dice2%10) + '0');
	int dice3 = dice_rand();
	unCalscore.push_back((dice3%10) + '0');

	//std::cout << unCalscore << std::endl;

	//if(runOnce)
	//{
		//std::cout << CalScore(unCalscore) << std::endl;
		ConvertToImage(dice1, 1);
		ConvertToImage(dice2, 2);
		ConvertToImage(dice3, 3);
		//if (CalScore(unCalscore) != 0) runOnce = false;
	//}
		return CalScore(unCalscore);
}

void GSRoll::ConvertToImage(int a, int position)
{
	std::string dots;
	Vector2 m_DicePos;

	switch (a)
	{
	case 1:
		dots = "1_dot";
		break;
	case 2:
		dots = "2_dots";
		break;
	case 3:
		dots = "3_dots";
		break;
	case 4:
		dots = "4_dots";
		break;
	case 5:
		dots = "5_dots";
		break;
	case 6:
		dots = "6_dots";
		break;
	default:
		break;
	}

	switch (position)
	{
	case 1:
		m_DicePos = Vector2(390, 200);
		break;
	case 2:
		m_DicePos = Vector2(590, 200);
		break;
	case 3:
		m_DicePos = Vector2(490, 400);
		break;
	default:
		break;
	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(dots);

	std::shared_ptr<Sprite2D> dice = std::make_shared<Sprite2D>(model, shader, texture);
	dice->Set2DPosition(m_DicePos);
	dice->SetSize(128, 128);
	m_listDice.push_back(dice);
}

//void GSRoll::BankTurn()
//{
//	int curBScore;
//	int BAttempts = 1;
//	while (BAttempts <= 7)
//	{
//		curBScore=RollDice();
//		std::cout << "Bank: " << "No: " << BAttempts << " " << "Value: " << curBScore << std::endl;
//		if (curBScore == 0)
//		{
//			Update(RollDice());
//			curBScore = RollDice();
//			std::cout << "Bank: " << "No: " << BAttempts << " " << "Value: " << curBScore << std::endl;
//			BAttempts++;
//		}
//		else
//		{
//			std::cout << "Bank: " << "No: " << BAttempts << " " << "Value: " << curBScore << std::endl;
//			break;
//		}
//	}
//	bankScore = curBScore;
//	std::cout << "Bank: " << bankScore << std::endl;
//	++turn;
//}
void GSRoll::Init()
{

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_play1");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Roll button

	texture = ResourceManagers::GetInstance()->GetTexture("button_Q");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 600); //285
	button->SetSize(200, 50);
	button->SetOnClick([]()
	{
		RollDice();
	});
	m_listButton2.push_back(button);

	//RollDice();
	//Sleep(3000);
	//m_listDice.clear();
	//RollDice();


	
}	

void GSRoll::Exit()
{
}


void GSRoll::Pause()
{

}

void GSRoll::Resume()
{

}


void GSRoll::HandleEvents()
{

}

void GSRoll::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSRoll::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton2)
	{
		if ((it)->IsVisible())
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;
		}
	}
}

void GSRoll::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton2)
	{
		it->Update(deltaTime);
	}

	for (auto it : m_listDice)
	{
		it->Update(deltaTime);
	}

	if (turn == 0)
	{
		do
		{
			RollDice();
			currentBScore = RollDice();
			if (currentBScore != 0)
			{
				std::cout << "Bank: " << "No: " << bankAttempts << " " << "Value: " << currentBScore << std::endl;
				bankScore = currentBScore;
				break;
			}
			else
			{
				m_listDice.clear();
				std::cout << "Bank: " << "No: " << bankAttempts << " " << "Value: " << currentBScore << std::endl;
				RollDice();
				currentBScore = RollDice();
				bankAttempts++;
			}

		} while (bankAttempts <= 7);
		turn++;
	}

}

void GSRoll::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton2)
	{
		if ((it)->IsVisible())
		{
			it->Draw();
		}
	}
	for (auto it : m_listText2)
	{
		it->Draw();
	}
	for (auto it : m_listDice)
	{
		it->Draw();
	}
}
