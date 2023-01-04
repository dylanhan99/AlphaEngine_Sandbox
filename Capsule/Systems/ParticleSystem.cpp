#include "ParticleSystem.h"
#include "GraphicsSystem.h"
#include "../Particle.h"
#include "AEsystem.h"

namespace System
{
	static ParticleSystemList* s_ParticleSystemList = nullptr;
	static ParticleBitSet s_ParticleBitset = {};

	ParticleSystemList* ParticleManager::GetParticleSystemList()
	{
		return s_ParticleSystemList;
	}

	ParticleBitSet ParticleManager::GetParticleBitSet()
	{
		return s_ParticleBitset;
	}

	void ParticleManager::Init()
	{
		s_ParticleSystemList = new ParticleSystemList();
	}

	void ParticleManager::Update(f32 _deltatime)
	{
		for (auto it = s_ParticleSystemList->begin(); it != s_ParticleSystemList->end(); ++it) {
			(*it)->Update(_deltatime);
		}
	}

	void ParticleManager::Draw()
	{
		for (auto it = s_ParticleSystemList->begin(); it != s_ParticleSystemList->end(); ++it) {
			(*it)->Draw();
		}
	}

	void ParticleManager::Terminate()
	{
		for (auto it = s_ParticleSystemList->begin(); it != s_ParticleSystemList->end(); ++it) {
			(*it)->Terminate();
			delete *it;
		}
	}

	void ParticleSystem::Init()
	{
		m_ParticlePool = new ParticlePool();
		for (auto it = m_ParticlePool->begin(); it != m_ParticlePool->end(); ++it) {
			*it = new Particle();
		}
		m_ActiveParticles = new ParticleList();
	}

	void ParticleSystem::Terminate()
	{
		m_ActiveParticles->clear();
		for (auto it = m_ParticlePool->begin(); it != m_ParticlePool->end(); ++it)
			delete* it;
		delete m_ActiveParticles;
		delete m_ParticlePool;
	}

	u32 ParticleSystem::FindUnusedParticle()
	{
		for (auto i = m_LastUsedParticle; i < PARTICLES_MAX; ++i) {
			if (m_ParticlePool->at(i)->Life > 0.f)
				continue;
			m_LastUsedParticle = i;
			return i;
		}

		for (auto i = 0; i < PARTICLES_MAX; ++i) {
			if (m_ParticlePool->at(i)->Life > 0.f)
				continue;
			m_LastUsedParticle = i;
			return i;
		}
		m_LastUsedParticle = 0;
		return 0;
	}

	void Smoke_ParticleSystem::Update(f32 _deltatime)
	{
		if (m_ActiveParticles->empty())
			return;
		for (u32 i = 0; i < m_ActiveParticles->size(); ++i) {
			auto particle = m_ActiveParticles->at(i);
			if (particle->Life <= 0.f) {
				// return to pool
				AEGfxMeshFree(particle->Mesh);
				m_ActiveParticles->erase(m_ActiveParticles->begin() + i);
				continue;
			}
			particle->Life -= _deltatime;
		}
	}

	void Smoke_ParticleSystem::Draw()
	{
		for (auto it = m_ActiveParticles->begin(); it != m_ActiveParticles->end(); ++it ) {
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

	void Smoke_ParticleSystem::SubmitParticles()
	{
		std::cout << "Set Particle\n";
		auto availableParticle = m_ParticlePool->at(FindUnusedParticle());
		availableParticle->Life = 2.f;
		s32 x, y; AEInputGetCursorPosition(&x, &y);
		availableParticle->Position.x = x - 800 * 0.5f;
		availableParticle->Position.y = -y + 600 * 0.5f;
		availableParticle->Mesh = GraphicsManager::CreateQuadMesh(100, 100, 0xffffffff);
		m_ActiveParticles->push_back(availableParticle);
	}

}