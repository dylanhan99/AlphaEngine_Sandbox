#include "Components.h"

EntityID Entity::LatestID = 0;

Entity::Entity() 
	: ID(LatestID++), Active(false), ComponentList({ nullptr }), ComponentBitset({ false })
{

}
