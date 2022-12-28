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
using ComponentMapArray = std::array<ComponentMap*, Components_MaxNum>;

/*!*************************************************************************
 * \brief
 * Registers ID for new component
 * \return
 * unsigned int, ID of new component
***************************************************************************/
inline ComponentID GetComponentID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

/*!*************************************************************************
 * \brief
 * Registers ID for new component
 * Static typeID initializer is called ONCE (reminder), 
 * and is fixed per typename
 * \return
 * unsigned int, ID of component
***************************************************************************/
template <typename T>
inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentID();
	return typeID;
}

struct Component
{
	EntityID m_EntityID;
	Component(EntityID _id) : m_EntityID(_id) {}
};

struct Entity
{
	static EntityID LatestID;
	EntityID ID;
	bool Active;
	std::array<ComponentRef, Components_MaxNum> ComponentList;
	std::bitset<Components_MaxNum> ComponentBitset;
	
	Entity();// : m_ID(LatestID++), m_Active(false) {}
};

struct Position : public Component
{
	f32 X;
	f32 Y;

	Position(EntityID _id, f32 _x, f32 _y) : Component(_id), X(_x), Y(_y) {}
};

// Renderable could be a Mesh or Sprite.
// CreateMesh(width, height) to create a quad
// CreateSprite("path2file", width, height)
// SetMesh(AEGfxVertexList*) for user's custom mesh
struct Renderable : public Component
{
	Renderable(EntityID _id) : Component(_id) {}
	~Renderable();
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
	Script(EntityID _id) : Component(_id) {}
	// Ref to entity
	// Can do stuff like entity.getcomponent<>
};
