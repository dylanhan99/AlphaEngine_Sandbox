	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00FF00FF, 0.0f, 0.0f, 
		30.0f,  -30.0f, 0x00FFFF00, 0.0f, 0.0f,
		-30.0f,  30.0f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		30.0f, -30.0f, 0x00FFFFFF, 0.0f, 0.0f, 
		30.0f,  30.0f, 0x00FFFFFF, 0.0f, 0.0f,
		-30.0f,  30.0f, 0x00FFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh2

	pMesh2 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh2, "Failed to create mesh 2!!");