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
			if (positionIterator == s_PositionComponents->end())
				continue;
			auto renderable = (Renderable*)it->second;
			auto position = (Position*)positionIterator->second;
			if (renderable->Mesh) {
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetRenderMode(AE_GFX_RM_COLOR);
				if (renderable->Texture)
					AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
				AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
				AEGfxSetPosition(position->X, position->Y);
				AEGfxTextureSet(renderable->Texture, 0, 0);
				AEGfxSetTransparency(1.0f);
				AEGfxMeshDraw(renderable->Mesh, AE_GFX_MDM_TRIANGLES);
			}
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
			-_width * 0.5f, -_height * 0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
			 _width * 0.5f, -_height * 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			-_width * 0.5f,  _height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

		AEGfxTriAdd(
			 _width * 0.5f, -_height * 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			 _width * 0.5f,  _height * 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			-_width * 0.5f,  _height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

		mesh = AEGfxMeshEnd();
		return mesh;
	}

	Renderable* GraphicsSystem::SetQuadMesh(Renderable* _component, float _width, float _height)
	{
		if (!_component)
			return nullptr;
		_component->Mesh = CreateQuadMesh(_width, _height);
		return _component;
	}

	AEGfxTexture* GraphicsSystem::CreateTexture(const char* _path)
	{
		AEGfxTexture* texture = AEGfxTextureLoad(_path);
		if (!texture)
			return nullptr; // could load texture as a "failed texture png" instead?
		return texture;
	}

	Renderable* GraphicsSystem::SetTexture(Renderable* _component, const char* _path, float _width, float _height)
	{
		if (!_component)
			return nullptr;
		_component->Texture = CreateTexture(_path);
		_component->Mesh = CreateQuadMesh(_width, _height);
		//if (!_component->Texture || !_component->Mesh)
		//	return nullptr;
		return _component;
	}

}