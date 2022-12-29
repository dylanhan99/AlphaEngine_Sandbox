#include "MovingGuyScript.h"
#include <iostream>
//#include "Systems/Systems.h"
//#include "Components.h"
#include "Systems/GraphicsSystem.h"

struct Guy {
	AEVec2 Position;
	u32 Color;
	AEGfxVertexList* Mesh = 0;
	f32 Size = 50.f;
};

static Guy m_Guy = Guy();

static Position* s_PositionComponent = NULL;

void MovingGuyScript::Init()
{
	using namespace System;
	EntitySystem::Init();
	GraphicsSystem::Init();

	auto entity2 = EntitySystem::CreateEntity();
	EntitySystem::AddComponent<Position>(entity2->ID, 100, 96);
	EntitySystem::AddComponent<Renderable>(entity2);
	EntitySystem::GetComponent<Renderable>(entity2)->Mesh = GraphicsSystem::CreateQuadMesh(100, 200);

	auto entity = EntitySystem::CreateEntity();
	EntitySystem::AddComponent<Position>(entity, 1, 0);
	EntitySystem::AddComponent<Script>(entity);
	auto rend = EntitySystem::AddComponent<Renderable>(entity);
	s_PositionComponent = EntitySystem::GetComponent<Position>(entity);
	GraphicsSystem::SetTexture(rend, "Assets/PlanetTexture.png", 100, 100);
}

void MovingGuyScript::Update()
{

	f32 amt = 10;
	if (AEInputCheckTriggered(AEVK_W)) {
		s_PositionComponent->Y += amt;
	}
	if (AEInputCheckTriggered(AEVK_S)) {
		s_PositionComponent->Y -= amt;
	}

	if (AEInputCheckTriggered(AEVK_A)) {
		s_PositionComponent->X -= amt;
	}
	if (AEInputCheckTriggered(AEVK_D)) {
		s_PositionComponent->X += amt;
	}

	System::GraphicsSystem::Update(1.f);
}

void MovingGuyScript::Draw()
{
	//std::cout << "Guy pos: " << m_Guy.Position.x << " - " << m_Guy.Position.y << std::endl;
	//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	//AEGfxSetPosition(m_Guy.Position.x, m_Guy.Position.y);
	//AEGfxTextureSet(NULL, 0, 0);
	//AEGfxMeshDraw(m_Guy.Mesh, AE_GFX_MDM_TRIANGLES);
	System::GraphicsSystem::Draw();
}

void MovingGuyScript::Terminate()
{
	using namespace System;
	GraphicsSystem::Terminate();
	EntitySystem::Terminate();
}