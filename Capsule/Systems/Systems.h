#pragma once

#include "../Components.h"

namespace System
{

	constexpr u32 MAX_POOL = 1000;

	class System
	{
		virtual void Init() = 0;
		virtual void Update(f32 _deltatime) = 0;
		virtual void Terminate() = 0;
	};

	class EntitySystem
	{
	private:
		
	public:
		static void Init();
		static void Update(f32 _deltatime) {}
		static void Terminate();

		/*!*************************************************************************
		 * \brief
		 * Get entirety of entitymap
		 * \return
		 * EntityMap
		***************************************************************************/
		static EntityMap GetEntities();
		/*!*************************************************************************
		 * \brief
		 * Get specific entity from entitymap
		 * \param _id
		 * Entity ID to be searched for.
		 * \return
		 * Reference to entity, null if non-existant
		***************************************************************************/
		static EntityRef GetEntity(EntityID& _id);

		/*!*************************************************************************
		 * \brief
		 * "Create" new entity by pulling from pool
		 * \return
		 * Reference to "new" entity
		***************************************************************************/
		static EntityRef CreateEntity();
		/*!*************************************************************************
		 * \brief
		 * "Destroys" entity, moves it into pool
		 * \param _id
		 * Entity ID to be destroyed.
		***************************************************************************/
		static void DestroyEntity(const EntityID& _id);
	};

	class ComponentSystem
	{
	public:
		static void Init();
		static void Update(f32 _deltatime) {}
		static void Terminate();

		//template <typename T>
		//inline ComponentMap GetComponents() noexcept
		//{
		//	return Componenth_GetComponents<T>();
		//}
		//
		//template <typename T>
		//inline ComponentRef const GetComponent(EntityID& _id)
		//{
		//	if (!EntitySystem::GetEntity(_id))
		//		return nullptr;
		//	return GetComponents<T>().at(_id);
		//}
		//static ComponentMap GetComponents(Components& _component);
		//static ComponentRef const GetComponent(Components& _component, EntityID& _id);

		//template<typename T>
		//static void AddComponent(T* _component);
	};

}