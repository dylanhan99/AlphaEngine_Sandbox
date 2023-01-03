#pragma once
#include "System.h"

namespace System
{

	struct ParticleProp {
		u32 NumberOfParticles	= 1;
		f32 Life				= 2;
		f32 LifeRange			= 0;

		bool SpawnAtDistance	= false; // If true, SpawnRange will be used as diameter
		u32 SpawnX				= 0;
		u32 SpawnXRange			= 0;
		u32 SpawnY				= 0;
		u32 SpawnYRange			= 0;

		AEVec2 Direction		= { 0, 0 };

	};

	class ParticleManager : public Manager
	{

	};
	
	class ParticleSystem// : public System
	{
	private:
	public:
		static void Init();
		static void Update(f32 _deltatime);
		static void Draw();
		static void Terminate();

		static u32 FindUnusedParticle();
		static void SetParticles(ParticleProp _prop);
	};

}