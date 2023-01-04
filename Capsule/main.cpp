#include "AEEngine.h"
#include "MovingGuyScript.h"
#include "ProceduralGeneration.h"

#define PROCEDURAL 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	///////////////////////
	// Variable declaration

	int m_GameRunning = 1;

#ifdef PROCEDURAL

#else
	MovingGuyScript script1;
#endif // PROCEDURAL

	// Variable declaration end
	///////////////////////////


	/////////////////
	// Initialization
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);
	// Changing the window title
	AESysSetWindowTitle("Capsule");
	//set background color
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	// reset the system modules
	AESysReset();
	// Initialization end
	/////////////////////

#ifdef PROCEDURAL
	ProceduralGeneration::Init();
#else
	script1.Init();
#endif // PROCEDURAL


	while (m_GameRunning)
	{
		AESysFrameStart();
		AEInputUpdate();

#ifdef PROCEDURAL
		ProceduralGeneration::Update();
		ProceduralGeneration::Draw();
#else
		script1.Update();
		script1.Draw();
#endif // PROCEDURAL


		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			m_GameRunning = 0;
	}
#ifdef PROCEDURAL
	ProceduralGeneration::Terminate();
#else
	script1.Terminate();
#endif // PROCEDURAL

	AESysExit();
}