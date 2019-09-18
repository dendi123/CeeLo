#pragma once
#include "Singleton.h"
#include "GameConfig.h"


class Application : public CSingleton<Application>
{
public:
	Application();
	~Application();
	void		Init();
	void		Update( GLfloat deltaTime);
	void		Render();
	void		HandleKeyEvent(unsigned char key, bool bIsPressed);
	void		HandleTouchEvent(GLint x, GLint y, bool bIsPressed);
	void		Exit();

private:
	

};

