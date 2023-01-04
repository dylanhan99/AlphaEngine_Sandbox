#pragma once
#include "System.h"
#include "../Particle.h"
#include <bitset>

#define PARTICLES_MAX 10000

namespace System
{
	enum Particles {
		Particle_Smoke = 0,

		Particle_MaxNum
	};

	//#define PARTICLES_MAX 10000;
	class ParticleSystem;
	using ParticleSystemList = std::vector<ParticleSystem*>;
	using ParticlePool = std::array<Particle*, PARTICLES_MAX>; // Arbitrary number
	using ParticleList = std::vector<Particle*>;

	using ParticleBitSet = std::bitset<Particle_MaxNum>;
	using ParticleID = u32;

	//struct ParticleProp {
	//	u32 NumberOfParticles	= 1;
	//	f32 Life				= 2;
	//	f32 LifeRange			= 0;
	//
	//	bool SpawnAtDistance	= false; // If true, SpawnRange will be used as diameter
	//	u32 SpawnX				= 0;
	//	u32 SpawnXRange			= 0;
	//	u32 SpawnY				= 0;
	//	u32 SpawnYRange			= 0;
	//
	//	AEVec2 Direction		= { 0, 0 };
	//
	//};

	inline ParticleID GetParticleID()
	{
		static ParticleID lastID = 0;
		return lastID++;
	}

	template <typename T>
	inline ParticleID GetParticleTypeID() noexcept
	{
		static ParticleID typeID = GetParticleID();
		return typeID;
	}

	class ParticleManager : public Manager
	{
	public:
		static ParticleSystemList* GetParticleSystemList();
		static ParticleBitSet GetParticleBitSet();

		static void Init();
		static void Update(f32 _deltatime);
		static void Draw();
		static void Terminate();

		template<typename T>
		static bool HasParticleSystem()
		{
			return GetParticleBitSet()[GetParticleTypeID<T>()];
		}
		
		template <typename T>
		static inline ParticleSystem* GetParticleSystem()
		{
			return GetParticleSystemList()->at(GetParticleTypeID<T>());
		}

		template<typename T>
		static T* AddParticleSystem()
		{
			if (HasParticleSystem<T>()) {
				std::cout << "Particle system already exists\n";
				return (T*)GetParticleSystem<T>();
			}
			T* particleSystem = new T();
			GetParticleSystemList()->push_back(particleSystem);
			GetParticleBitSet()[GetParticleTypeID<T>()] = true;
			
			return particleSystem;
		}
	};
	
	class ParticleSystem
	{
	protected:
		ParticlePool* m_ParticlePool;// = nullptr;
		ParticleList* m_ActiveParticles;
		u32 m_LastUsedParticle;// = 0;
	public:
		ParticleSystem() { Init(); }
		virtual void Init();
		virtual void Terminate();
		
		virtual void Update(f32 _deltatime) = 0;
		virtual void Draw() = 0;
		virtual void SubmitParticles() = 0; // Submit a fixed set of particles. Unique to each particle type

		u32 FindUnusedParticle();
	};

	class Smoke_ParticleSystem : public ParticleSystem
	{
		//void Init() override;
		void Update(f32 _deltatime) override;
		void Draw() override;
		//void Terminate() override;

		void SubmitParticles() override;
	};

}