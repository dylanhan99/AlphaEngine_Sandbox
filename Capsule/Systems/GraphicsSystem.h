#pragma once
#include "Systems.h"

namespace System
{

	class GraphicsSystem : public System
	{
	private:

	public:
		static void Init();
		static void Update(f32 _deltatime);
		static void Draw();
		static void Terminate();

		static AEGfxVertexList* CreateQuadMesh(float _width, float _height);
	};

}