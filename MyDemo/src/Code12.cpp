		++counter;
		if(counter < 120)
			AEGfxTextureSet(pTex1, objtexX, objtexY);		// Same object, different texture
		else if(counter < 240)
			AEGfxTextureSet(pTex2, objtexX, objtexY);		// Same object, different texture
		else
		{
			AEGfxTextureSet(pTex1, objtexX, objtexY);		// Same object, different texture
			counter = 0;
		}