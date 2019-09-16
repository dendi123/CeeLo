#pragma once 
#include "Sprite2D.h"

class GameButton : public Sprite2D
{
public:
	GameButton(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~GameButton();
	void	SetOnClick(void	(*pBtClick)());
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();
	bool	IsVisible();
	bool	HideButton();
	bool	ShowButton();
	//bool IsPressed();

private:
	void	(*m_pBtClick)();
	bool	m_isHandle;
	bool	m_isVisible;
	//bool	m_isPressed;
	

};
