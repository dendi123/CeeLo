#include "targetver.h"
#include "Shaders.h"
#include "Application.h"
#include "utilities.h"
#include "time.h"

GLint screenWidth = 960;
GLint screenHeight = 640;

	
GLint Init(ESContext* esContext)
{
	time_t t;
	srand(time(&t));
	Application::GetInstance()->Init();
	return 0;
}

void Draw(ESContext* esContext)
{
	Application::GetInstance()->Render();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, GLfloat deltaTime)
{
	Application::GetInstance()->Update(deltaTime);
}

void Key(ESContext* esContext, unsigned char key, bool bbIsPresseded)
{
	Application::GetInstance()->HandleKeyEvent(key, bbIsPresseded);
}

void Mouse(ESContext* esContext, GLint x, GLint y, bool bbIsPressed)//bool bbIsPresseded
{
	Application::GetInstance()->HandleTouchEvent(x, y, bbIsPressed);
}

void CleanUp()
{
	Application::GetInstance()->Exit();
	Application::FreeInstance();
}

GLint _tmain(GLint argc, _TCHAR* argv[])
{

	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "Demo Game", screenWidth, screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterMouseFunc(&esContext, Mouse);
	esMainLoop(&esContext);
	esRegisterKeyFunc(&esContext, Key);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	//MemoryDump();
	//printf("Press any key...\n");
	//_getch();

	return 0;
}

//#endif