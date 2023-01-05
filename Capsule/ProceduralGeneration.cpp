#include "ProceduralGeneration.h"
#include "Systems/GraphicsSystem.h"

#include "AEUtil.h"

#include <cmath>

using namespace System;

void ProceduralGeneration::Init()
{
	EntityManager::Init();
	GraphicsManager::Init();

	AEVec2 circlePos = { 0, 0 };
	f32 spawnRadius = 300;
	f32 spawnDiameter = spawnRadius * 2;
	u32 numToSpawn = 5;
	f32 sizeSmallest = 50;
	f32 sizeLargest = 100;

	struct circ {
		f32 X, Y;
		f32 size;
	};

	std::vector<circ> circVector;

	srand((unsigned)time(NULL));
	for (u32 i = 0; i < numToSpawn; ) {
		// random x,y values within circle range
		// random size - pick 2 corners of the new quad
			// if overlap with any others, dont ++i, 
			// delete quad and redo
			// if no overlap, ++i

		circ newCirc = {
			0 - spawnRadius + (spawnDiameter * AERandFloat()), // x
			0 - spawnRadius + (spawnDiameter * AERandFloat()), // y
			sizeSmallest + (sizeLargest - sizeSmallest) * AERandFloat() // size
		};

		auto entity = EntityManager::CreateEntity();
		if (!entity)
			continue;
		
		if (!circVector.empty()) {
			bool overlap = false;
			for (u32 j = 0; j < circVector.size(); ++j) {
				auto comparison = circVector[j];
				f32 totalRadius = newCirc.size / 2 + comparison.size / 2;
				f32 distance = sqrt(pow(comparison.X - newCirc.X, 2) + pow(comparison.Y - newCirc.Y, 2));
				if (distance < totalRadius)
					overlap = true;
			}
			if (overlap)
				continue;
		}

		EntityManager::AddComponent<Position>(entity, newCirc.X, newCirc.Y);
		auto renderable = EntityManager::AddComponent<Renderable>(entity);
		//GraphicsManager::SetQuadMesh(renderable, size, size);
		GraphicsManager::SetCircleMesh(renderable, newCirc.size);
		GraphicsManager::SetDrawMode(renderable, AE_GFX_MDM_TRIANGLES);
		++i;
	}

	auto entity = EntityManager::CreateEntity();
	EntityManager::AddComponent<Position>(entity, 0, 0);
	auto renderable = EntityManager::AddComponent<Renderable>(entity);
	f32 min = -200;
	f32 max = 200;
	u32 col = 0xFFFFFFFF;
	AEGfxMeshStart();
	for (int i = 0; i < 10; ++i) {
		f32 x = min + ((max - min) * AERandFloat());
		f32 y = min + ((max - min) * AERandFloat());
		AEGfxTriAdd(
			-x * 0.5f, -y * 0.5f, col - 100000 * i, 0.0f, 1.0f,
			 x * 0.5f, -y * 0.5f, col - 100000 * i, 1.0f, 1.0f,
			-x * 0.5f,  y * 0.5f, col - 100000 * i, 0.0f, 0.0f);

	}
	renderable->Mesh = AEGfxMeshEnd();

	AEGfxMeshFree(renderable->Mesh);

}

void ProceduralGeneration::Update()
{
	EntityManager::Update(1.f);
	GraphicsManager::Update(1.f);
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
