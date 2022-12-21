		// Drawing object 1
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set position for object 1
		AEGfxSetPosition(0.0f, 0.0f);
		// No texture for object 1
		AEGfxTextureSet(NULL, 0, 0);
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);