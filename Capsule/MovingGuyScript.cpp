#include "MovingGuyScript.h"
#include <iostream>
//#include "Systems/Systems.h"
//#include "Components.h"
#include "Systems/GraphicsSystem.h"
//#include "Systems/ParticleSystem.h"

struct Guy {
	AEVec2 Position;
	u32 Color;
	AEGfxVertexList* Mesh = 0;
	f32 Size = 50.f;
};

static Guy m_Guy = Guy();

static EntityRef s_Entity2 = NULL;
static Renderable* s_Entity2Rend = NULL;

static Position* s_PositionComponent = NULL;

static EntityRef s_EntityLIGHT = NULL;
static Position* s_LightPos = NULL;

void MovingGuyScript::Init()
{
	using namespace System;
	EntityManager::Init();
	GraphicsManager::Init();
	//ParticleManager::Init();
	//ParticleSystem::Init();

	s_Entity2 = EntityManager::CreateEntity();
	EntityManager::AddComponent<Position>(s_Entity2->ID, 0, 0);
	EntityManager::AddComponent<Renderable>(s_Entity2);
	//EntitySystem::GetComponent<Renderable>(entity2)->Mesh = GraphicsSystem::CreateCircleMesh(600);
	s_Entity2Rend = EntityManager::GetComponent<Renderable>(s_Entity2);
	s_Entity2Rend->Mesh = GraphicsManager::CreatePolygonMesh(3, 600, 0xFF32AAAA);
	GraphicsManager::SetDrawMode(s_Entity2Rend, AE_GFX_MDM_TRIANGLES);
	//s_Entity2Rend->Mesh = GraphicsSystem::CreateQuadMesh(100, 400, 0xFF32AAAA, 100);

	auto entity = EntityManager::CreateEntity();
	EntityManager::AddComponent<Position>(entity, 1, 0);
	EntityManager::AddComponent<Script>(entity);
	auto rend = EntityManager::AddComponent<Renderable>(entity);
	s_PositionComponent = EntityManager::GetComponent<Position>(entity);
	GraphicsManager::SetTexture(rend, "Assets/PlanetTexture.png", 100, 100);

	//ParticleManager::AddParticleSystem<Smoke_ParticleSystem>();
	//auto stuff = ParticleManager::GetParticleSystemList();
	s_EntityLIGHT = EntityManager::CreateEntity();
	s_LightPos = EntityManager::AddComponent<Position>(s_EntityLIGHT, 0, 0);
	auto lightRend = EntityManager::AddComponent<Renderable>(s_EntityLIGHT);
	GraphicsManager::SetTexture(lightRend, "Assets/LIGHT.png", 75, 75);
}

void MovingGuyScript::Update()
{
	static u32 segments = 3;
	using namespace System;

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

	static f32 rot = 0;
	if (AEInputCheckTriggered(AEVK_UP)) {
		++segments;
		rot += 20;
		AEGfxMeshFree(s_Entity2Rend->Mesh);
		s_Entity2Rend->Mesh = GraphicsManager::CreatePolygonMesh(segments, 600, 0xFF32AAAA, rot);
		//s_Entity2Rend->Mesh = GraphicsSystem::CreateQuadMesh(100, 400, 0xFF32AAAA, rot);
	}
	if (AEInputCheckTriggered(AEVK_DOWN)) {
		--segments;
		rot -= 20;
		AEGfxMeshFree(s_Entity2Rend->Mesh);
		s_Entity2Rend->Mesh = GraphicsManager::CreatePolygonMesh(segments, 600);
	}

	if (AEInputCheckTriggered(AEVK_SPACE)) {
		AEGfxMeshFree(s_Entity2Rend->Mesh);
		GraphicsManager::SetCircleMesh(s_Entity2Rend, 300);
	}

	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		//ParticleSystem::SetParticles(ParticleProp{ 2.f });
	}

	static s32 mousex = 0;
	static s32 mousey = 0;
	AEInputGetCursorPosition(&mousex, &mousey);
	s_LightPos->X = mousex - 400;
	s_LightPos->Y = mousey * -1 + 300;

	GraphicsManager::Update(1.f);
	//ParticleManager::Update(0.1f);
	//ParticleSystem::Update(0.1f);
}

void MovingGuyScript::Draw()
{
	//std::cout << "Guy pos: " << m_Guy.Position.x << " - " << m_Guy.Position.y << std::endl;
	//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	//AEGfxSetPosition(m_Guy.Position.x, m_Guy.Position.y);
	//AEGfxTextureSet(NULL, 0, 0);
	//AEGfxMeshDraw(m_Guy.Mesh, AE_GFX_MDM_TRIANGLES);
	using namespace System;
	GraphicsManager::Draw();
	//ParticleManager::Draw();
	//ParticleSystem::Draw();
}

void MovingGuyScript::Terminate()
{
	using namespace System;
	//ParticleSystem::Terminate();
	//ParticleManager::Terminate();
	GraphicsManager::Terminate();
	EntityManager::Terminate();
}