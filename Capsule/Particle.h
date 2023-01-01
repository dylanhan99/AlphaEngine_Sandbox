#pragma once
#include "AEvec2.h"
#include "AEGraphics.h"
#include "Constants.h"

struct Particle
{
	AEGfxVertexList* Mesh = nullptr;
	f32 Life = 0;
	AEVec2 Position = { 0, 0 };
	f32 Speed = 0;
	u32 Color = System::DEFAULT_COLOR;
	f32 Size = 0;
};