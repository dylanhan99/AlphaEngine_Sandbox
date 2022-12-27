#include "Components.h"
#include <utility>

EntityID Entity::LatestID = 0;
static std::array<ComponentMap, Components_MaxNum> s_ComponentMapsArray = {};

ComponentMapArray GetComponentMapArray()
{
	return s_ComponentMapsArray;
}

Entity::Entity() 
	: m_ID(LatestID++), m_Active(false), m_ComponentArray({ nullptr })
{

}

void Entity::Destroy()
{
	for (auto component : m_ComponentArray)
		if (component) delete component;
	m_Active = false;
}

//template <typename T, typename ...Args>
//T* Entity::AddComponent(Args&&... _args)
//{
//	T* component(new T(std::forward<Args>(_args)...));
//
//	this.m_ComponentArray[GetComponentTypeID<T>()] = component;
//	this.m_ComponentBitSet[GetComponentTypeID<T>()] = true;
//
//	// Add too relevant system map here
//	//System::ComponentSystem::AddComponent<T>(component);
//	s_ComponentMapsArray[GetComponentTypeID<T>()].at(component->GetID()) = component;
//	
//	return component;
//}