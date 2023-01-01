#include "GraphicsSystem.h"

namespace System
{

	static ComponentMap* s_PositionComponents = nullptr;
	static ComponentMap* s_RenderableComponents = nullptr;
	static AEGfxTexture* s_DefaultTexture = nullptr; // For failed/missing textures

	void GraphicsSystem::Init()
	{
		s_PositionComponents	= GetComponents<Position>();
		s_RenderableComponents	= GetComponents<Renderable>();

		s_DefaultTexture = AEGfxTextureLoad("Assets/MISSING_TEXTURE.png");
		AE_ASSERT_MESG(s_DefaultTexture, "Failed to load default texture.");
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
				AEGfxMeshDraw(renderable->Mesh, renderable->DrawMode);
			}
		}
	}

	void GraphicsSystem::Terminate()
	{
		s_PositionComponents = nullptr;
		s_RenderableComponents = nullptr;
		AEGfxTextureUnload(s_DefaultTexture);
	}

	AEGfxVertexList* GraphicsSystem::CreateQuadMesh(f32 _width, f32 _height, u32 _color, f32 _rotation)
	{
		AEGfxVertexList* mesh = nullptr;
		AEGfxMeshStart();

		if (!_rotation) {
			AEGfxTriAdd(
				-_width * 0.5f, -_height * 0.5f, _color, 0.0f, 1.0f,
				 _width * 0.5f, -_height * 0.5f, _color, 1.0f, 1.0f,
				-_width * 0.5f,  _height * 0.5f, _color, 0.0f, 0.0f);

			AEGfxTriAdd(
				 _width * 0.5f, -_height * 0.5f, _color, 1.0f, 1.0f,
				 _width * 0.5f,  _height * 0.5f, _color, 1.0f, 0.0f,
				-_width * 0.5f,  _height * 0.5f, _color, 0.0f, 0.0f);
		} else {
			//std::array<AEVec2, 6> arr = {
			AEVec2 arr[6] = {
				AEVec2{-_width * 0.5f, -_height * 0.5f},
				AEVec2{ _width * 0.5f, -_height * 0.5f},
				AEVec2{-_width * 0.5f,  _height * 0.5f},

				AEVec2{ _width * 0.5f, -_height * 0.5f},
				AEVec2{ _width * 0.5f,  _height * 0.5f},
				AEVec2{-_width * 0.5f,  _height * 0.5f}
			};
			AEMtx33 rotmtx;
			AEMtx33RotDeg(&rotmtx, _rotation);
			AEMtx33MultVecArray(arr, &rotmtx, arr, 6);

			AEGfxTriAdd(
				arr[0].x, arr[0].y, _color, 0.0f, 1.0f,
				arr[1].x, arr[1].y, _color, 1.0f, 1.0f,
				arr[2].x, arr[2].y, _color, 0.0f, 0.0f);

			AEGfxTriAdd(
				arr[3].x, arr[3].y, _color, 1.0f, 1.0f,
				arr[4].x, arr[4].y, _color, 1.0f, 0.0f,
				arr[5].x, arr[5].y, _color, 0.0f, 0.0f);
		}
		mesh = AEGfxMeshEnd();
		return mesh;
	}

	Renderable* GraphicsSystem::SetQuadMesh(Renderable* _component, f32 _width, f32 _height, u32 _color, f32 _rotation)
	{
		if (!_component)
			return nullptr;
		_component->Mesh = CreateQuadMesh(_width, _height, _color, _rotation);
		return _component;
	}

	AEGfxVertexList* GraphicsSystem::CreateCircleMesh(f32 _diameter, u32 _color)
	{
		return CreatePolygonMesh(DEFAULT_SEGMENTS, _diameter, _color);
	}

	Renderable* GraphicsSystem::SetCircleMesh(Renderable* _component, f32 _diameter, u32 _color)
	{
		if (!_component)
			return nullptr;
		_component->Mesh = CreateCircleMesh(_diameter, _color);
		return _component;
	}

	AEGfxVertexList* GraphicsSystem::CreatePolygonMesh(u32 _segments, f32 _diameter, u32 _color, f32 _rotation)
	{
		f32 rad = _diameter * 0.5f;

		std::vector<AEVec2> points;

		AEGfxVertexList* mesh = nullptr;
		AEGfxMeshStart();

		for (auto i = 0; i < _segments; ++i) {
			f32 angle = 2.0f * PI * i / _segments + PI * 0.5f + _rotation;
			points.push_back({ rad * AECos(angle) , rad * AESin(angle) });
			//points[i].x = rad * AECos(angle);
			//points[i].y = rad * AESin(angle);
		}

		for (auto i = 0; i < _segments; ++i) {
			u32 next = (i + 1) % _segments;
			AEGfxTriAdd(
				0.f, 0.f, _color, 0.0f, 1.0f,
				points[i].x, points[i].y, _color, 1.0f, 1.0f,
				points[next].x, points[next].y, _color, 0.0f, 0.0f);
		}

		mesh = AEGfxMeshEnd();
		return mesh;
	}

	Renderable* GraphicsSystem::SetPolygonMesh(Renderable* _component, u32 _segments, f32 _diameter, u32 _color, f32 _rotation)
	{
		if (!_component)
			return nullptr;
		_component->Mesh = CreatePolygonMesh(_segments, _diameter, _color, _rotation);
		return _component;
	}

	AEGfxTexture* GraphicsSystem::CreateTexture(const char* _path)
	{
		AEGfxTexture* texture = AEGfxTextureLoad(_path);
		if (!texture)
			texture = s_DefaultTexture; // could load texture as a "failed texture png" instead?
		return texture;
	}

	Renderable* GraphicsSystem::SetTexture(Renderable* _component, const char* _path, f32 _width, f32 _height, f32 _rotation)
	{
		if (!_component)
			return nullptr;
		_component->Texture = CreateTexture(_path);
		_component->Mesh = CreateQuadMesh(_width, _height, DEFAULT_COLOR, _rotation);
		//if (!_component->Texture || !_component->Mesh)
		//	return nullptr;
		return _component;
	}

	Renderable* GraphicsSystem::SetDrawMode(Renderable* _component, AEGfxMeshDrawMode _drawmode)
	{
		if (!_component)
			return nullptr;
		_component->DrawMode = _drawmode;
	}

}