		char strBuffer[100];
		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "Frame Time:  %.6f", AEFrameRateControllerGetFrameTime());

		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxPrint(fontId, strBuffer, -0.95, -0.95, 1.0f, 1.f, 1.f, 1.f);