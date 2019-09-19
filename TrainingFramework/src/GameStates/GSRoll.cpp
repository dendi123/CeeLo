#include "GSRoll.h"
#include <dos.h>



extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

std::list<std::shared_ptr<Sprite2D>> m_listDice;
std::vector<int> array;

int dice1, dice2, dice3;
int turn = -1;
int bankScore, playerScore;
int currentBScore, currentPscore = -1;
int bankAttempts = 0, playerAttempts = 0;

//bool isPressed = false;
bool runOnce = true;
bool wait = false;
bool isClicked = false;

int tempPot;

SoLoud::Soloud* GSRoll::soloud = new SoLoud::Soloud;

std::shared_ptr<Text> m_dendi;
std::shared_ptr<Text> goodLuck;

SoLoud::Wav roll;

GSRoll::GSRoll()
{

}


GSRoll::~GSRoll()
{
}

int GSRoll::CalScore(std::string m_unCalScore)
{
	int score;
	array.clear();

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
int dice_rand()
{
	return rand() % 6 + 1;
}
int GSRoll::RollDice()
{
	soloud->init();
	roll.load("../Data/sfx/rol.mp3");
	//static bool runOnce = true;

	//std::mt19937::result_type seed = time(0);
	std::string unCalscore;

	//auto dice_rand = bind(std::uniform_int_distribution<int>(1, 6) , std::mt19937(seed));

	dice1 = dice_rand();
	unCalscore.push_back((dice1%10) +'0');
	dice2 = dice_rand();
	unCalscore.push_back((dice2%10) + '0');
	dice3 = dice_rand();
	unCalscore.push_back((dice3%10) + '0');
	std::cout << "ROLL";
	std::cout << "Dice :" << dice1 << std::endl;
	std::cout << "Dice :" << dice2 << std::endl;
	std::cout << "Dice :" << dice3 << std::endl;

	ConvertToImage(dice1, 1);
	ConvertToImage(dice2, 2);
	ConvertToImage(dice3, 3);

	
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
		m_DicePos = Vector2(390, 255);
		break;
	case 2:
		m_DicePos = Vector2(590, 255);
		break;
	case 3:
		m_DicePos = Vector2(490, 375);
		break;
	default:
		break;
	}

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(dots);

	std::shared_ptr<Sprite2D> dice = std::make_shared<Sprite2D>(model, shader, texture);
	dice->Set2DPosition(m_DicePos);
	dice->SetSize(90, 90);
	m_listDice.push_back(dice);
}

void GSRoll::Init()
{
	tempPot = GSPlay::pot;

	//soloud->init();
	//rollsong.load("../Data/sfx/xoso.mp3");
	//Resume();

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_play1");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Roll button

	texture = ResourceManagers::GetInstance()->GetTexture("button_R");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 600); //285
	button->SetSize(200, 50);
	//button->HideButton();
	button->SetOnClick([]()
	{
		if (runOnce)
		{
			turn++;
			runOnce = false;
		}
		else
		{
			isClicked = true;
			if (wait == false)
			{
				std::cout << "disdaaaaaaaaaaaaaaaaaaaaaaot";
				if (playerAttempts <= 7)
				{
					currentPscore = RollDice();
					playerAttempts++;
					wait = true;
				}
			}
			if (turn == 3)
			{
				turn = -1;
				tempPot = GSPlay::pot;
				m_listDice.clear();
				m_dendi->setText("    Press Roll to Start Game ");
				goodLuck->setText("");

				wait = false;
				currentPscore = -1;
				isClicked = false;
				runOnce = true;
				bankAttempts = 0;
				playerAttempts = 0;

				GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
			}
		}

		
	});
	m_listButton2.push_back(button);

	// Icon

	texture = ResourceManagers::GetInstance()->GetTexture("table_top");
	std::shared_ptr<Sprite2D> icon = std::make_shared<Sprite2D>(model, shader, texture);
	icon->Set2DPosition(screenWidth / 2, screenHeight / 2);
	icon->SetSize(797, 447);
	m_listIcon1.push_back(icon);

	texture = ResourceManagers::GetInstance()->GetTexture("dendi");
	icon = std::make_shared<Sprite2D>(model, shader, texture);
	icon->Set2DPosition(screenWidth / 2, 76);
	icon->SetSize(137, 155);
	m_listIcon1.push_back(icon);

	texture = ResourceManagers::GetInstance()->GetTexture("bubble");
	icon = std::make_shared<Sprite2D>(model, shader, texture);
	icon->Set2DPosition(665, 40);
	icon->SetSize(320, 67);
	m_listIcon1.push_back(icon);

	 //text title

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font3 = ResourceManagers::GetInstance()->GetFont("boton");
	m_dendi = std::make_shared<Text>(shader, font3, "    Press Roll to Start Game ", TEXT_COLOR::RED, 0.8); //"Press Roll to Start Game" //My Score is: 20.Good Luck
	m_dendi->Set2DPosition(Vector2(565, 40));
	//m_listText2.push_back(dendi);

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	m_wallet = std::make_shared<Text>(shader, font3, "", TEXT_COLOR::WHILE, 1);
	m_wallet->Set2DPosition(Vector2(50, 570));

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	m_pot = std::make_shared<Text>(shader, font3, "", TEXT_COLOR::WHILE, 1);
	m_pot->Set2DPosition(Vector2(50, 600));

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	goodLuck = std::make_shared<Text>(shader, font3, "", TEXT_COLOR::RED, 0.8);
	goodLuck->Set2DPosition(Vector2(565, 50));
}	

void GSRoll::Exit()	
{
	rollsong.stop();
	soloud->deinit();
}


void GSRoll::Pause()
{

}

void GSRoll::Resume()
{
	soloud->init();
	soloud->play(rollsong);
}


void GSRoll::HandleEvents()
{
//	if (turn == 2)
//	{
//		if (playerScore > bankScore)
//		{
//			GSPlay::tempPot = GSPlay::tempPot * 2;
//			GSPlay::wallet = GSPlay::wallet + GSPlay::tempPot;
//		}
//		else if (playerScore < bankScore)
//		{
//			GSPlay::wallet = GSPlay::wallet - GSPlay::pot;
//			GSPlay::pot = GSPlay::tempPot;
//
//		}
//		else
//		{
//			GSPlay::wallet = GSPlay::wallet;
//			GSPlay::pot = GSPlay::tempPot;
//		}
//	}
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

	std::stringstream stream;
	stream << GSPlay::wallet;
	std::string temp = "Wallet: " + stream.str();
	m_wallet->setText(temp);

	std::stringstream stream1;
	stream1 << GSPlay::pot;
	std::string temp1 = "Pot: " + stream1.str();
	m_pot->setText(temp1);

	if (turn == 0)
	{
		do
		{
			currentBScore = RollDice();
			std::cout << "Bank: " << "No: " << bankAttempts << " " << "Value: " << currentBScore << std::endl;
			if (currentBScore != 0)
			{
				break;
			}
			bankAttempts++;
		} while (bankAttempts <= 7);
		bankScore = currentBScore;
		turn++;

		std::stringstream stream;
		stream << bankScore; //"My Score is: 20.Good Luck"
		std::string temp = "  My Score is: " + stream.str() +" . Good Luck ";
		m_dendi->setText(temp);
		m_dendi->Set2DPosition(565, 30);


		std::string temp1 = " Press Roll to begin your turn ";
		goodLuck->setText(temp1);
		goodLuck->Set2DPosition(565, 50);
	}
	else if (turn == 1)
	{
		//Sleep(1000);
		if (isClicked)
		{
			goodLuck->setText("");
			m_dendi->Set2DPosition(565, 40);

			if (currentPscore != 0)
			{
				playerScore = currentPscore;


				//std::stringstream stream1;
				//stream1 << playerScore; //"My Score is: 20.Good Luck"
				//std::string temp = "  Your Score is: " + stream1.str() + " . Nice Try ";
				//m_dendi->setText(temp);

				turn++;
			}
			else
			{
				if (playerAttempts < 7)
				{
					//std::cout << playerAttempts;
					std::string temp = " Roll Again. Almost There ";
					m_dendi->setText(temp);
					wait = false;
				}
				else
				{
					std::stringstream stream2;
					stream2 << 0; //"My Score is: 20.Good Luck"
					std::string temp1 = "  Your Score is: " + stream2.str() + " . Nice Try ";
					m_dendi->setText(temp1);
				}
			}
		}
	}


	if (turn == 2)
	{
		//Sleep(1000);
		std::stringstream stream1;
		std::stringstream stream2;

		stream1 << playerScore;
		stream2 << bankScore;

		if (playerScore > bankScore)
		{
			tempPot = tempPot * 2;
			GSPlay::wallet = GSPlay::wallet + tempPot;
			GSPlay::tempWallet = GSPlay::wallet;
			GSPlay::pot = GSPlay::tempPot;

	
			std::string temp1 = "Your Score: " + stream1.str() + " > " + "My Score: " + stream2.str();
			m_dendi->setText(temp1);
			m_dendi->Set2DPosition(565, 30);

			std::string temp2 = "YOU WON. Roll to Play Again";
			goodLuck->setText(temp2);
			goodLuck->Set2DPosition(565, 50);

			//runOnce = true;
			turn++;

		}
		else if (playerScore < bankScore)
		{
			GSPlay::tempWallet = GSPlay::wallet;
			GSPlay::pot = GSPlay::tempPot;

			std::string temp1 = "Your Score: " + stream1.str() + " < " + "My Score: " + stream2.str();
			m_dendi->setText(temp1);
			m_dendi->Set2DPosition(565, 30);

			std::string temp2 = "YOU LOST. Roll to Play Again";
			goodLuck->setText(temp2);
			goodLuck->Set2DPosition(565, 50);

			//runOnce = true;
			turn++;

				//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
				//soloud->deinit();
			//turn++;
		}
		else if (playerScore == bankScore)
		{
			GSPlay::tempWallet = GSPlay::wallet + tempPot;
			GSPlay::pot = GSPlay::tempPot;

			std::string temp1 = "Your Score: " + stream1.str() + " = " + "My Score: " + stream2.str();
			m_dendi->setText(temp1);
			m_dendi->Set2DPosition(565, 30);

			std::string temp2 = "Roll to Play Again";
			goodLuck->setText(temp2);
			goodLuck->Set2DPosition(565, 50);

			//runOnce = true;
			turn++;

		}

	}

	//std::cout << turn;

	//if (turn == 4)
	//{
	//	turn = 0;
	//}
	//



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
	for (auto it : m_listIcon1)
	{
		it->Draw();
	}
	for (auto it : m_listDice)
	{
		it->Draw();
	}
	//for (auto it : m_listText2)
	//{
	//	it->Draw();
	//}

	m_wallet->Draw();
	m_pot->Draw();
	m_dendi->Draw();
	goodLuck->Draw();

	

}
