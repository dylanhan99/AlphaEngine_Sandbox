		// Object 1 Control
		if (AEInputCheckCurr(AEVK_UP))
			obj1Y += 3.0f;
		else if (AEInputCheckCurr(AEVK_DOWN))
			obj1Y -= 3.0f;

		if (AEInputCheckCurr(AEVK_LEFT))
			obj1X -= 3.0f;
		else if (AEInputCheckCurr(AEVK_RIGHT))
			obj1X += 3.0f;