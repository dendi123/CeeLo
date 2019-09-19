#pragma once
#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include <random>
#include <time.h>
#include <functional>
#include <string.h>
#include <Sprite2D.h>
#include <algorithm>
#include <dos.h>
#include "soloud.h"
#include "soloud_wav.h"
#include "GSPlay.h"
#include <thread>

class GSRoll :
	public GameStateBase
{
public:
	GSRoll();
	~GSRoll();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	static int RollDice();
	static void ConvertToImage(int a, int position);
	static int CalScore(std::string m_unCalScore);

	void test();

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton2;
	std::list<std::shared_ptr<Text>> m_listText2;
	std::list <std::shared_ptr<Sprite2D>> m_listIcon1;

	/*std::shared_ptr<Text> m_dendi;
	std::shared_ptr<Text> goodLuck;*/

	//std::list<std::shared_ptr<Sprite2D>> m_listDice;
	//std::shared_ptr<Text>  m_Text_gameName;
	static SoLoud::Soloud* soloud;
	SoLoud::Wav rollsong;

	std::shared_ptr<Text> m_pot;
	std::shared_ptr<Text> m_wallet;

	


};

