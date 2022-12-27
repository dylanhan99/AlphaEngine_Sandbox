#pragma once
#include "AEengine.h"
#include <array>
#include <bitset>
#include <unordered_map>
#include <iostream>

// Change to u64 if more than 8 components
//constexpr u32 BITSET_POSITION	= 0x00000001;
//constexpr u32 BITSET_RENDERABLE = 0x00000010;
//constexpr u32 BITSET_SCRIPT		= 0x00000100;

enum Components {
	Components_Position = 0,
	Components_Renderable,
	Components_Script,

	Components_MaxNum
};

class Entity;
struct Component;

using EntityID = u32;
using ComponentID = u32;
using EntityRef = Entity*;
using ComponentRef = Component*;
using EntityList = std::vector<EntityRef>;
using EntityMap = std::unordered_map<EntityID, EntityRef>;
using ComponentMap = std::unordered_map<EntityID, ComponentRef>;
using ComponentMapArray = std::array<ComponentMap, Components_MaxNum>;

inline ComponentID GetComponentID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T>
inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentID();
	return typeID;
}

extern ComponentMapArray GetComponentMapArray();

template <typename T>
inline ComponentMap Componenth_GetComponents() noexcept
{
	return GetComponentMapArray().at(GetComponentTypeID<T>());
}

struct Component
{
	EntityID m_EntityID;
	Component(EntityID _id) : m_EntityID(_id) {}

	inline const EntityID GetID() const { return m_EntityID; }
};

class Entity
{
private:
	static EntityID LatestID;
	EntityID m_ID;
	bool m_Active;
	std::array<Component*, Components_MaxNum> m_ComponentArray;
	std::bitset<Components_MaxNum> m_ComponentBitset;

public:
	Entity();// : m_ID(LatestID++), m_Active(false) {}

	void Destroy();

	//template<class T, class ...Args>
	//T* AddComponent(Args&&... _args);
	template <typename T, typename ...Args>
	T* AddComponent(Args&&... _args)
	{
		if (HasComponent<T>()) {
			std::cout << "Component already exists" << std::endl;
			return nullptr;
		}
		T* component(new T(std::forward<Args>(_args)...));
		m_ComponentArray[GetComponentTypeID<T>()] = component;
		m_ComponentBitset[GetComponentTypeID<T>()] = true;

		GetComponentMapArray()[GetComponentTypeID<T>()].
			insert(std::make_pair(component->GetID(), component));

		return component;
	}

	template <typename T>
	bool HasComponent() const
	{
		return m_ComponentBitset[GetComponentTypeID<T>()];
	}

	template <typename T>
	T* GetComponent() const
	{
		return m_ComponentArray[GetComponentTypeID<T>()];
	}

	inline EntityID const GetID() const { return m_ID; }
	inline void SetActive(bool _active) { m_Active = _active; }
};

struct Position : public Component
{
	f32 X;
	f32 Y;

	Position(EntityID _id, f32 _x, f32 _y) : Component(_id), X(_x), Y(_y) {}
};

struct Renderable : public Component
	// Renderable could be a Mesh or Sprite.
	// CreateMesh(width, height) to create a quad
	// CreateSprite("path2file", width, height)
	// SetMesh(AEGfxVertexList*) for user's custom mesh
{
	// In render system, if (texture): rendermode, tint, textureset(NULL), transparency
	// After component added, can do renderable.Mesh = AEgfxMeshEnd or whatever
	// Could have a functions in graphics system to handle this creation stuff
	// eg. 
	AEGfxVertexList* Mesh = nullptr; 
	AEGfxTexture* Texture = nullptr;
	u32 Color;
};
	
struct Script : public Component
{
	// Ref to entity
	// Can do stuff like entity.getcomponent<>
};
