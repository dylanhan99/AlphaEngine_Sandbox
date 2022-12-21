// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"



// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	///////////////////////
	// Variable declaration

	int gGameRunning = 1;

	// Variable declaration end
	///////////////////////////


	/////////////////
	// Initialization

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);


	// Changing the window title
	AESysSetWindowTitle("My New Demo!");

	// reset the system modules
	AESysReset();

	// Initialization end
	/////////////////////



	////////////////////////////////
	// Creating the objects (Shapes)

	// Creating the objects (Shapes) end
	////////////////////////////////////



	////////////////////////////
	// Loading textures (images)

	// Loading textures (images) end
	//////////////////////////////////

	//////////////////////////////////
	// Creating Fonts	

	// Creating Fonts end
	//////////////////////////////////


	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		///////////////////
		// Game loop update

		// Game loop update end
		///////////////////////


		//////////////////
		// Game loop draw

		// Game loop draw end
		/////////////////////


		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}


	// free the system
	AESysExit();
}