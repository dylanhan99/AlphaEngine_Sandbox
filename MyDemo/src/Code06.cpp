		// Drawing object 3 - (Second)
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set position for object 3
		AEGfxSetPosition(100.0f, 60.0f);	
		// No texture for object 3
		AEGfxTextureSet(NULL, 0, 0);
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);