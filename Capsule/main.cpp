#include "AEEngine.h"
#include "MovingGuyScript.h"

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

	MovingGuyScript script1;

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

	script1.Init();

	while (m_GameRunning)
	{
		AESysFrameStart();
		AEInputUpdate();

		script1.Update();

		script1.Draw();

		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			m_GameRunning = 0;
	}

	script1.Terminate();

	AESysExit();
}