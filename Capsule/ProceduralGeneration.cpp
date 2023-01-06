#include "ProceduralGeneration.h"
#include "Systems/GraphicsSystem.h"

#include "AEUtil.h"

#include <cmath>

using namespace System;
static u32 rad = 5;
void ProceduralGeneration::Init()
{
	EntityManager::Init();
	GraphicsManager::Init();

	//u32 rad = 20;
	u32 diameter = rad * 2;
	u32 gridSize = 200;
	for (u32 i = 0; i < gridSize; ++i) {
		for (u32 j = 0; j < gridSize; ++j) {
			// init circles
			auto entity = EntityManager::CreateEntity();
			f32 x = (float)(0 - 400) + (float)(i * diameter);
			f32 y = (float)(0 - 300) + (float)(j * diameter);
			EntityManager::AddComponent<Position>(entity, x, y);
			auto renderable = EntityManager::AddComponent<Renderable>(entity);
			//GraphicsManager::SetCircleMesh(renderable, diameter);
			GraphicsManager::SetQuadMesh(renderable, diameter, diameter);
		}
	}
	{
		//auto entity = EntityManager::CreateEntity();
		//EntityManager::AddComponent<Position>(entity, 0, 0);
		//auto renderable = EntityManager::AddComponent<Renderable>(entity);
		//f32 min = -200;
		//f32 max = 200;
		//u32 col = 0xFFFFFFFF;
		//AEGfxMeshStart();
		//for (int i = 0; i < 10; ++i) {
		//	f32 x = min + ((max - min) * AERandFloat());
		//	f32 y = min + ((max - min) * AERandFloat());
		//	AEGfxTriAdd(
		//		-x * 0.5f, -y * 0.5f, col - 100000 * i, 0.0f, 1.0f,
		//		 x * 0.5f, -y * 0.5f, col - 100000 * i, 1.0f, 1.0f,
		//		-x * 0.5f,  y * 0.5f, col - 100000 * i, 0.0f, 0.0f);
		//
		//}
		//renderable->Mesh = AEGfxMeshEnd();
		//
		//AEGfxMeshFree(renderable->Mesh);
	}
}

void ProceduralGeneration::Update()
{
	EntityManager::Update(1.f);
	GraphicsManager::Update(1.f);

	static EntityMap* s_Entities = EntityManager::GetEntities();
	static s32 mouseX = 0;
	static s32 mouseY = 0;
	static u32 mouseRad = 20;
	static u32 totalRad = rad + mouseRad;
	AEInputGetCursorPosition(&mouseX, &mouseY);
	mouseX -= 400;
	mouseY = mouseY * -1 + 300;

	std::cout << mouseX << ", " << mouseY << std::endl;
	static ComponentMap* s_PositionComponents = GetComponents<Position>();
	for (auto it = s_PositionComponents->begin(); it != s_PositionComponents->end(); ++it) {
		auto position = (Position*)it->second;
		// if dist from mouse to pos is < radius, collide, draw.
		// else dont draw
		f32 dist = sqrt(pow((mouseX - position->X), 2) + pow(mouseY - position->Y, 2));
		if (dist <= totalRad) {
			s_Entities->at(position->m_EntityID)->Active = true;
		}
		else
			s_Entities->at(position->m_EntityID)->Active = false;
	}
}

void ProceduralGeneration::Draw()
{
	GraphicsManager::Draw();
}

void ProceduralGeneration::Terminate()
{
	GraphicsManager::Terminate();
	EntityManager::Terminate();
}
