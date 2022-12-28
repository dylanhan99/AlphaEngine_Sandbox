#include "GraphicsSystem.h"

namespace System
{

	static ComponentMap* s_PositionComponents = nullptr;
	static ComponentMap* s_RenderableComponents = nullptr;

	void GraphicsSystem::Init()
	{
		s_PositionComponents	= GetComponents<Position>();
		s_RenderableComponents	= GetComponents<Renderable>();
	}

	void GraphicsSystem::Update(f32 _deltatime)
	{
		
	}

	void GraphicsSystem::Draw()
	{
		for (auto it = s_RenderableComponents->begin(); it != s_RenderableComponents->end(); ++it) {
			auto positionIterator = s_PositionComponents->find(it->second->m_EntityID);
			//if (positionIterator == s_RenderableComponents->end())
			//	continue;
			auto renderable = (Renderable*)it->second;
			auto position = (Position*)positionIterator->second;
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
			AEGfxSetPosition(position->X, position->Y);
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxMeshDraw(renderable->Mesh, AE_GFX_MDM_TRIANGLES);
		}
	}

	void GraphicsSystem::Terminate()
	{
		s_PositionComponents = nullptr;
		s_RenderableComponents = nullptr;
	}

	AEGfxVertexList* GraphicsSystem::CreateQuadMesh(float _width, float _height)
	{
		AEGfxVertexList* mesh = nullptr;
		AEGfxMeshStart();
		AEGfxTriAdd(
			0.f,	0.f,	  0xFFFF0000, 0.0f, 0.0f,
			0.f,	-_height, 0xFFFF0000, 0.0f, 0.0f,
			_width, -_height, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			_width, -_height, 0xFFFF0000, 0.0f, 0.0f,
			_width, 0.f,	  0xFFFF0000, 0.0f, 0.0f,
			0.f,	0.f,	  0xFFFF0000, 0.0f, 0.0f
		);
		mesh = AEGfxMeshEnd();
		return mesh;
	}

}