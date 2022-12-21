		// Blending mode
		if (AEInputCheckCurr(AEVK_1))
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
		else if (AEInputCheckCurr(AEVK_2))
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		else if (AEInputCheckCurr(AEVK_3))
			AEGfxSetBlendMode(AE_GFX_BM_ADD);