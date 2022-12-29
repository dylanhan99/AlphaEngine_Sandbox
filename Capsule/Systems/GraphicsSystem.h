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
		static AEGfxVertexList* CreateQuadMesh(float _width, float _height);
		
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
		static Renderable* SetQuadMesh(Renderable* _component, float _width, float _height);

		static AEGfxVertexList* CreateCircleMesh(float _diameter);

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
		static Renderable* SetTexture(Renderable* _component, const char* _path, float _width, float _height);
	};

}