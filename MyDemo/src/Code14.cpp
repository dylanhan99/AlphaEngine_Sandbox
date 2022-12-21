		// Move the camera
		AEGfxGetCamPosition(&camX, &camY);
		if (AEInputCheckCurr(AEVK_W))
			AEGfxSetCamPosition(camX, camY + 2);
		else if (AEInputCheckCurr(AEVK_S))
			AEGfxSetCamPosition(camX, camY - 2);

		AEGfxGetCamPosition(&camX, &camY);
		if (AEInputCheckCurr(AEVK_A))
			AEGfxSetCamPosition(camX - 2, camY);
		else if (AEInputCheckCurr(AEVK_D))
			AEGfxSetCamPosition(camX + 2, camY);