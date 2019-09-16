#include "GameButton.h"


GameButton::GameButton(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_pBtClick = nullptr;
	m_isHandle = false;
	m_isVisible = true;
	//m_isPressed = false;

}	

GameButton::~GameButton()
{
}

void GameButton::SetOnClick(void(*pBtClickFun)())
{
	//if(m_isVisible)
	m_pBtClick = pBtClickFun;
}

void GameButton::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
		m_isHandle = false;
		if ((x > m_Vec2DPos.x  - m_iWidth/2) && (x < m_Vec2DPos.x + m_iWidth / 2) && (y > m_Vec2DPos.y - m_iHeight / 2) && (y < m_Vec2DPos.y + m_iHeight / 2))
		{
			m_pBtClick();
			m_isHandle = true;
		}
}

bool GameButton::IsHandle()
{
	return m_isHandle;
}

bool GameButton::IsVisible()
{
	return m_isVisible;
}
bool GameButton::HideButton()
{
	m_isVisible = false;
	return m_isVisible;
}

bool GameButton :: ShowButton()
{
	m_isVisible = true;
	return m_isVisible;
}

//bool GameButton :: IsPressed()
//{
//	m_isPressed = true;
//	return m_isPressed;
//}
