#include "ParticleSystem.h"
#include "GraphicsSystem.h"
#include "../Particle.h"

namespace System
{
	constexpr u32 PARTICLES_MAX = 10000;
	
	static std::array<Particle*, PARTICLES_MAX>* s_ParticlePool = nullptr;
	static std::vector<Particle*>* s_ActiveParticles = nullptr;
	static u32 s_LastUsedParticle = 0;

	void ParticleSystem::Init()
	{
		s_ParticlePool = new std::array<Particle*, PARTICLES_MAX>();
		s_ActiveParticles = new std::vector<Particle*>();
		for (auto it = s_ParticlePool->begin(); it != s_ParticlePool->end(); ++it) {
			*it = new Particle();
		}
	}

	void ParticleSystem::Update(f32 _deltatime)
	{
		if (s_ActiveParticles->empty())
			return;
		for (u32 i = 0; i < s_ActiveParticles->size(); ++i) {
			auto particle = s_ActiveParticles->at(i);
			if (particle->Life <= 0.f) {
				// return to pool
				AEGfxMeshFree(particle->Mesh);
				s_ActiveParticles->erase(s_ActiveParticles->begin() + i);
				continue;
			}
			particle->Life -= _deltatime;
		}
	}

	void ParticleSystem::Draw()
	{
		for (auto it = s_ActiveParticles->begin(); it != s_ActiveParticles->end(); ++it ) {
			auto particle = *it;
			if (!particle->Mesh)
				continue;
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			//if (renderable->Texture)
			//	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
			AEGfxSetPosition(particle->Position.x, particle->Position.y);
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxSetTransparency(1.0f);
			AEGfxMeshDraw(particle->Mesh, AE_GFX_MDM_TRIANGLES);
		}
	}

	void ParticleSystem::Terminate()
	{
		s_ActiveParticles->clear();
		for (auto it = s_ParticlePool->begin(); it != s_ParticlePool->end(); ++it)
			delete *it;
		delete s_ActiveParticles;
		delete s_ParticlePool;
	}

	u32 ParticleSystem::FindUnusedParticle()
	{
		for (auto i = s_LastUsedParticle; i < PARTICLES_MAX; ++i) {
			if (s_ParticlePool->at(i)->Life > 0.f) 
				continue;
			s_LastUsedParticle = i;
			return i;
		}

		for (auto i = 0; i < PARTICLES_MAX; ++i) {
			if (s_ParticlePool->at(i)->Life > 0.f)
				continue;
			s_LastUsedParticle = i;
			return i;
		}
		s_LastUsedParticle = 0;
		return 0;
	}

	void ParticleSystem::SetParticles(ParticleProp _prop)
	{
		std::cout << "Set Particle\n";
		auto availableParticle = s_ParticlePool->at(FindUnusedParticle());
		availableParticle->Life = _prop.Life;
		s32 x, y; AEInputGetCursorPosition(&x, &y);
		availableParticle->Position.x = 0;
		availableParticle->Position.y = 0;
		availableParticle->Mesh = GraphicsSystem::CreateQuadMesh(100, 100, 0xffffffff);
		s_ActiveParticles->push_back(availableParticle);
	}

}