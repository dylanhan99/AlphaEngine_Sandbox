#include "System.h"
#include <algorithm>
#include "../Components.h"

namespace System
{

	static EntityMap* s_EntityMap = nullptr;
	static EntityList* s_AvailableEntities = nullptr;
	static ComponentMapArray* s_ComponentMapsArray = nullptr;

	ComponentMapArray* GetComponentMapArray()
	{
		return s_ComponentMapsArray;
	}

	void EntityManager::Init()
	{
		s_EntityMap = new EntityMap();
		s_AvailableEntities = new EntityList({ nullptr });
		s_ComponentMapsArray = new ComponentMapArray({ nullptr });

		for (u32 i = 0; i < MAX_POOL; ++i)
			s_AvailableEntities->push_back(new Entity());
		for (auto it = s_ComponentMapsArray->begin(); it != s_ComponentMapsArray->end(); ++it)
			*it = new ComponentMap();
	}

	void EntityManager::Terminate()
	{
		// When there is a component pool, dont forget to delete pool and component map from here.
		// Then DestroyEntity() will jkust disable the component rather than delete it.

		for (auto it = s_ComponentMapsArray->begin(); it != s_ComponentMapsArray->end(); ++it) {
			for (auto it2 = (*it)->begin(); it2 != (*it)->end(); ++it2) {
				delete it2->second;
		}}
		for (auto it = s_AvailableEntities->begin(); it != s_AvailableEntities->end(); ++it)
			delete *it;
	}

	EntityRef EntityManager::CreateEntity()
	{
		EntityRef entity = nullptr;
		if (s_AvailableEntities->size() > 0) {
			entity = s_AvailableEntities->back();
			s_AvailableEntities->pop_back();
			entity->Active = true;
		} else {
			entity = new Entity();
		}
		s_EntityMap->insert(std::make_pair(entity->ID, entity));
		return entity;
	}

	void EntityManager::DestroyEntity(const EntityID& _id)
	{
		auto entity = s_EntityMap->at(_id);
		for (auto component : entity->ComponentList)
			if (component) delete component;
		entity->Active = false;
		GetEntities()->erase(entity->ID);
		GetAvailableEntities()->push_back(entity);
	}
	
	EntityList* EntityManager::GetAvailableEntities()
	{
		return s_AvailableEntities;
	}

	EntityMap* EntityManager::GetEntities()
	{
		return s_EntityMap;
	}

	EntityRef EntityManager::GetEntity(EntityID& _id)
	{
		//if (_id < 0 || _id >= s_EntityMap.size())
		//	return nullptr;
		return s_EntityMap->at(_id);
	}

}