#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include <time.h>
#include "Animation.h"

class Sprite2D;
class Sprite3D;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bbIsPressed);
	void HandleTouchEvents(int x, int y, bool IsPressed);
	void Update(float deltaTime);
	void Draw();
	

	static int wallet;
	static int pot;
	static int tempWallet;
	static int tempPot;


	static int WalletDec(int a);

	//void rollDice();

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>> m_listButton1;
	std::list<std::shared_ptr<Text>> m_listText1;
	std::list<std::shared_ptr<GameButton>> m_listChip;
	std::list <std::shared_ptr<Sprite2D>> m_listIcon;

	std::shared_ptr<Text> walletText;
	std::shared_ptr<Text> potText;



	//std::shared_ptr<Text>  m_score;

};

