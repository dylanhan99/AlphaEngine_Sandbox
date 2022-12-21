		// Drawing object 2 - (first) - No tint
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		// Set position for object 2
		AEGfxSetPosition(100.0f, -60.0f);	
		// No tint
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Set texture
		AEGfxTextureSet(pTex1, 0.0f, 0.0f);	
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);


		// Drawing object 3 - (Second) - Blue tint
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		// Set position for object 3
		AEGfxSetPosition(100.0f, 60.0f);	
		// Add Blue tint
		AEGfxSetTintColor(0.0f, 0.0f, 1.0f, 1.0f);
		// Set texture
		AEGfxTextureSet(pTex1, 0.0f, 0.0f);	
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);