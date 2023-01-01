#pragma once
#include "Systems.h"
#include "../Constants.h"

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

		/*!*************************************************************************
		 * \brief
		 * Creates a quad mesh. 
		 * Mesh is drawn from top left corner.
		 * \param _width
		 * Width of mesh in pixels.
		 * \param _height
		 * Height of mesh in pixels.
		 * \return
		 * Pointer to new AEGfxVertexList. 
		 * Typically assigned to RenderableComponent->Mesh.
		***************************************************************************/
		static AEGfxVertexList* CreateQuadMesh(f32 _width, f32 _height, u32 _color = DEFAULT_COLOR, f32 _rotation = 0.f);
		
		/*!*************************************************************************
		 * \brief
		 * Creates and assigns a quad mesh to component. 
		 * Mesh is drawn from top left corner.
		 * \param _component
		 * Pointer to Renderable component
		 * \param _width
		 * Width of mesh in pixels.
		 * \param _height
		 * Height of mesh in pixels.
		 * \return
		 * Pointer to component provided.
		 * Nullptr if invalid component.
		***************************************************************************/
		static Renderable* SetQuadMesh(Renderable* _component, f32 _width, f32 _height, u32 _color = DEFAULT_COLOR, f32 _rotation = 0.f);
		
		/*!*************************************************************************
		 * \brief
		 * Creates a circle mesh.
		 * \param _diameter
		 * Diameter of mesh in pixels.
		 * \return
		 * Pointer to new AEGfxVertexList.
		 * Typically assigned to RenderableComponent->Mesh.
		***************************************************************************/
		static AEGfxVertexList* CreateCircleMesh(f32 _diameter, u32 _color = DEFAULT_COLOR);

		/*!*************************************************************************
		 * \brief
		 * Creates and assigns a circle mesh.
		 * \param _component
		 * Pointer to Renderable component
		 * \param _diameter
		 * Diameter of mesh in pixels.
		 * \return
		 * Pointer to component provided.
		 * Nullptr if invalid component.
		***************************************************************************/
		static Renderable* SetCircleMesh(Renderable* _component, f32 _diameter, u32 _color = DEFAULT_COLOR);

		static AEGfxVertexList* CreatePolygonMesh(u32 _segments, f32 _diameter, u32 _color = DEFAULT_COLOR, f32 _rotation = 0.f);
		static Renderable* SetPolygonMesh(Renderable* _component, u32 _segments, f32 _diameter, u32 _color = DEFAULT_COLOR, f32 _rotation = 0.f);

		/*!*************************************************************************
		 * \brief
		 * Creates a texture.
		 * \param _path
		 * Path to texture
		 * \return
		 * Pointer to new AEGfxTexture.
		 * Nullptr if failed texture.
		***************************************************************************/
		static AEGfxTexture* CreateTexture(const char* _path);
		
		/*!*************************************************************************
		 * \brief
		 * Creates and assigns a texture to component.
		 * \param _component
		 * Pointer to Renderable component
		 * \param _path
		 * Path to texture
		 * \param _width
		 * Width of mesh in pixels.
		 * \param _height
		 * Height of mesh in pixels.
		 * \return
		 * Pointer to component provided.
		 * Nullptr if invalid component or failed texture.
		***************************************************************************/
		static Renderable* SetTexture(Renderable* _component, const char* _path, f32 _width, f32 _height, f32 _rotation = 0.f);
	
		static Renderable* SetDrawMode(Renderable* _component, AEGfxMeshDrawMode _drawmode);
	};

}