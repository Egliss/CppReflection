#include "../Reflection/ReflectionAnchor.hpp"
#include "Component.hpp"

using namespace Egliss::ComponentSystem;

Component::Component() : _id(-1), _typeId(-1), _state(ComponentLifeCycleState::Constructed), _enable(true), _GameObject(nullptr)
{
}

void Component::_InternalAwake(GameObjectT* GameObject, int typeId)
{
	// TODO 
	static int ComponentId = 0;
	this->_id = ComponentId++;

	this->_typeId = typeId;
	this->_GameObject = GameObject;
	this->OnAwake();
}

void Component::_InternalDestroyRequested()
{
	this->_enable = false;
	this->_state = ComponentLifeCycleState::DestroyRequested;
}
