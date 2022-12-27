#include "MovingGuyScript.h"
#include <iostream>
#include "Systems/Systems.h"
#include "Components.h"

struct Guy {
	AEVec2 Position;
	u32 Color;
	AEGfxVertexList* Mesh = 0;
	f32 Size = 50.f;
};

static Guy m_Guy = Guy();

void MovingGuyScript::Init()
{
	using namespace System;
	EntitySystem::Init();

	auto entity = EntitySystem::CreateEntity();
	EntitySystem::AddComponent<Position>(entity->ID, 1, 0);
	EntitySystem::AddComponent<Position>(entity->ID, 0, 0);
	EntitySystem::AddComponent<Script>(entity->ID);
	EntitySystem::AddComponent<Renderable>(entity->ID);
	EntitySystem::AddComponent<Renderable>(entity->ID);
	auto positionComponent = EntitySystem::GetComponent<Position>(entity);
	auto scriptComponent = EntitySystem::GetComponent<Script>(entity);

	auto entity2 = EntitySystem::CreateEntity();
	EntitySystem::AddComponent<Position>(entity2->ID, 69, 96);
	auto position2 = EntitySystem::GetComponent<Position>(entity2);

	m_Guy.Position = { 0, 0 };
	m_Guy.Color = 0xFFFFFFFF;
	
	AEGfxMeshStart();
	AEGfxTriAdd(
		0.f, m_Guy.Size, 0xFFFF0000, 0.0f, 0.0f,
		-m_Guy.Size, -m_Guy.Size, 0xFFFF0000, 0.0f, 0.0f,
		m_Guy.Size, -m_Guy.Size, 0xFFFF0000, 0.0f, 0.0f
	);
	m_Guy.Mesh = AEGfxMeshEnd();
}

void MovingGuyScript::Update()
{
	f32 amt = 10;
	if (AEInputCheckTriggered(AEVK_W)) {
		m_Guy.Position.y += amt;
	}
	if (AEInputCheckTriggered(AEVK_S)) {
		m_Guy.Position.y -= amt;
	}

	//s32 x, y;
	//AEInputGetCursorPosition(&x, &y);
	//m_Guy.Position.x = x;
	//m_Guy.Position.y = y;
}

void MovingGuyScript::Draw()
{
	//std::cout << "Guy pos: " << m_Guy.Position.x << " - " << m_Guy.Position.y << std::endl;
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetPosition(m_Guy.Position.x, m_Guy.Position.y);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(m_Guy.Mesh, AE_GFX_MDM_TRIANGLES);
}

void MovingGuyScript::Terminate()
{
	AEGfxMeshFree(m_Guy.Mesh);

	using namespace System;
	EntitySystem::Terminate();
}