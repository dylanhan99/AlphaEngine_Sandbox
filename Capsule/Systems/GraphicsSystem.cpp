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

	AEGfxVertexList* GraphicsSystem::CreateQuadMesh(f32 _width, f32 _height)
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

	Renderable* GraphicsSystem::SetQuadMesh(Renderable* _component, f32 _width, f32 _height)
	{
		if (!_component)
			return nullptr;
		_component->Mesh = CreateQuadMesh(_width, _height);
		return _component;
	}

#define SEGMENTS 36
	AEGfxVertexList* GraphicsSystem::CreateCircleMesh(f32 _diameter)
	{
		return CreatePolygonMesh(SEGMENTS, _diameter);
	}

	Renderable* GraphicsSystem::SetCircleMesh(Renderable* _component, f32 _diameter)
	{
		if (!_component)
			return nullptr;
		_component->Mesh = CreateCircleMesh(_diameter);
		return _component;
	}

#define PI 3.141592654f
	AEGfxVertexList* GraphicsSystem::CreatePolygonMesh(u32 _segments, f32 _diameter)
	{
		f32 rad = _diameter * 0.5f;

		std::vector<AEVec2> points;

		AEGfxVertexList* mesh = nullptr;
		AEGfxMeshStart();

		for (auto i = 0; i < _segments; ++i) {
			f32 angle = 2.0f * PI * i / _segments + PI * 0.5f;
			points.push_back({ rad * AECos(angle) , rad * AESin(angle) });
			//points[i].x = rad * AECos(angle);
			//points[i].y = rad * AESin(angle);
		}

		for (auto i = 0; i < _segments; ++i) {
			u32 next = (i + 1) % _segments;
			AEGfxTriAdd(
				0.f, 0.f, 0xFFFFFFFF, 0.0f, 1.0f,
				points[i].x, points[i].y, 0xFFFFFFFF, 1.0f, 1.0f,
				points[next].x, points[next].y, 0xFFFFFFFF, 0.0f, 0.0f);
		}

		mesh = AEGfxMeshEnd();
		return mesh;
	}

	Renderable* GraphicsSystem::SetPolygonMesh(Renderable* _component, u32 _segments, f32 _diameter)
	{
		if (!_component)
			return nullptr;
		_component->Mesh = CreatePolygonMesh(_segments, _diameter);
		return _component;
	}

	AEGfxTexture* GraphicsSystem::CreateTexture(const char* _path)
	{
		AEGfxTexture* texture = AEGfxTextureLoad(_path);
		if (!texture)
			return nullptr; // could load texture as a "failed texture png" instead?
		return texture;
	}

	Renderable* GraphicsSystem::SetTexture(Renderable* _component, const char* _path, f32 _width, f32 _height)
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