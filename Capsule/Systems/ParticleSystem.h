#pragma once
#include "Systems.h"

namespace System
{

	struct ParticleProp {
		f32 Life = 2;

	};
	
	class ParticleSystem : public System
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