#pragma once

#include "../Components.h"

namespace System
{

	constexpr u32 MAX_POOL = 1000;

	extern ComponentMapArray* GetComponentMapArray();

	template <typename T>
	inline ComponentMap* GetComponents()
	{
		return GetComponentMapArray()->at(GetComponentTypeID<T>());
	}

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
		 * Get list of available entities
		 * \return
		 * Reference to available entity list
		***************************************************************************/
		static EntityList* GetAvailableEntities();

		/*!*************************************************************************
		 * \brief
		 * Get entirety of entitymap
		 * \return
		 * Reference to EntityMap
		***************************************************************************/
		static EntityMap* GetEntities();

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

		/*!*************************************************************************
		 * \brief
		 * Check if entity has component
		 * \param _entity
		 * Entity pointer used to check for component
		 * \return
		 * True/false flag
		***************************************************************************/
		template <typename T>
		static bool HasComponent(EntityRef _entity)
		{
			return _entity->ComponentBitset[GetComponentTypeID<T>()];
		}

		/*!*************************************************************************
		 * \brief
		 * Check if entity has component
		 * \param _id
		 * EntityID used to check for component
		 * \return
		 * True/false flag
		***************************************************************************/
		template <typename T>
		static bool HasComponent(EntityID& _id)
		{
			EntityRef ref = GetEntity(_id);
			if (!ref)
				return false;
			return ref->ComponentBitset[GetComponentTypeID<T>()];
		}

		/*!*************************************************************************
		 * \brief
		 * Get component from entity
		 * \param _entity
		 * Entity pointer used to get component
		 * \return
		 * Pointer to component. Is null if non-existant
		***************************************************************************/
		template <typename T>
		static T* GetComponent(EntityRef _entity)
		{
			return (T*)GetComponents<T>()->at(_entity->ID);
		}

		/*!*************************************************************************
		 * \brief
		 * Add component to entity
		 * \param _id
		 * ID of entity to add component to.
		 * \param _args
		 * Variadic arguments, made up of variables the component's constructor
		 * requires.
		 * \return
		 * Pointer to component. Nullptr if already exists.
		***************************************************************************/
		template <typename T, typename ...Args>
		static T* AddComponent(EntityID& _id, Args&&... _args)
		{
			auto entity = GetEntity(_id);
			if (HasComponent<T>(entity)) {
				std::cout << "Component already exists" << std::endl;
				return nullptr;
			}

			T* component(new T(_id, std::forward<Args>(_args)...));
			entity->ComponentList[GetComponentTypeID<T>()] = component;
			entity->ComponentBitset[GetComponentTypeID<T>()] = true;
			//auto comps = GetComponents<T>();
			//comps->emplace(std::make_pair(component->m_EntityID, component));
			GetComponents<T>()->emplace(std::make_pair(component->m_EntityID, component));

			return component;
		}
	};

}