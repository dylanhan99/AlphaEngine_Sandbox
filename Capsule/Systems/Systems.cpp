#include "Systems.h"
#include <algorithm>
#include "../Components.h"

namespace System
{

	static EntitySystem* s_EntityManager = nullptr;
	static ComponentSystem* s_ComponentManager = new ComponentSystem();

	static EntityMap s_EntityMap = {};
	static EntityList s_AvailableEntities = {};
	//static ComponentMap s_AllComponents[Components_MaxNum] = {};

	void EntitySystem::Init()
	{
		s_EntityManager = new EntitySystem();

		for (u32 i = 0; i < MAX_POOL; ++i) {
			s_AvailableEntities.push_back(new Entity());
		}
	}

	void EntitySystem::Terminate()
	{
		//for (auto entity : s_EntityMap)
		for (auto it = s_EntityMap.begin(); it != s_EntityMap.end(); ++it)
			EntitySystem::DestroyEntity(it->second->GetID());
		for (auto entity : s_AvailableEntities)
			delete entity;

		delete s_EntityManager;
	}

	/*!*************************************************************************
	 * \brief
	 * Creates new Entity object
	 * \return
	 * Pointer to the Entity object created.
	***************************************************************************/
	EntityRef EntitySystem::CreateEntity()
	{
		EntityRef entity = nullptr;
		if (s_AvailableEntities.size() > 0) {
			entity = s_AvailableEntities.back();
			s_AvailableEntities.pop_back();
			entity->SetActive(true);
		} else {
			entity = new Entity();
		}
		s_EntityMap.insert(std::make_pair(entity->GetID(), entity));
		return entity;
	}

	void EntitySystem::DestroyEntity(const EntityID& id)
	{
		auto entity = s_EntityMap.at(id);
		entity->Destroy();
		s_AvailableEntities.push_back(entity);
	}
	
	EntityMap EntitySystem::GetEntities()
	{
		return s_EntityMap;
	}

	EntityRef EntitySystem::GetEntity(EntityID& _id)
	{
		if (_id < 0 || _id >= s_EntityMap.size())
			return nullptr;
		return s_EntityMap.at(_id);
	}

	/*!*************************************************************************
	 * \brief
	 * Creates new Entity object
	 * \param name
	 * Name of the game object to find.
	 * \return
	 * Pointer to the game object if found.
	 * Returns nullptr if not found.
	***************************************************************************/
	//void ComponentSystem::AddComponent(Components& _component, EntityID& _id)
	//{
	//	if (_component > Components_MaxNum || _component < 0)
	//		return;
	//	if (ComponentSystem::GetComponents(_component).find(_id) == ComponentSystem::GetComponents(_component).end())
	//		return;
	//
	//
	//}

	void ComponentSystem::Init()
	{
		s_ComponentManager = new ComponentSystem();
	}

	void ComponentSystem::Terminate()
	{
		delete s_ComponentManager;
	}

	//template<typename T>
	//void ComponentSystem::AddComponent(T* _component)
	//{
	//	s_ComponentMapsArray[GetComponentTypeID<T>()].at(_component->GetID()) = _component;
	//}

	//ComponentMap ComponentSystem::GetComponents(Components& _component)
	//{
	//	return s_ComponentMapsArray[_component];
	//}

	//ComponentRef const ComponentSystem::GetComponent(Components& _component, EntityID& _id)
	//{
	//	if (!EntitySystem::GetEntity(_id))
	//		return nullptr;
	//	return GetComponents(_component).at(_id);
	//}

}