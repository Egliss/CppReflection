#include <string>
#include <vector>

#include "../Reflection/ReflectionAnchor.hpp"
#include "GameObject.hpp"
#include "Component.hpp"

using namespace Egliss::ComponentSystem;

// TODO 削除回りが甘い
GameObject::GameObject() : _id(-1), _enable(true), _name(""), _state(GameObjectLifeCycleState::Birthed)
{
}

void GameObject::_InternalUpdate()
{
	for (auto component : this->_appendReserved)
	{
		this->_components.emplace_back(component);
	}
	this->_appendReserved.clear();
	for (auto iterator = this->_components.begin(); iterator != this->_components.end(); iterator++)
	{
		auto component = *iterator;
		if (component->State() == ComponentLifeCycleState::DestroyRequested)
		{
			this->_removeReserved.emplace_back(component);
			this->_components.erase(iterator);
			continue;
		}
		if (component->Enable())
		{
			if (component->State() == ComponentLifeCycleState::Awaked)
			{
				component->OnStart();
				component->_InternalState(ComponentLifeCycleState::Started);
			}
		}
		if (component->Enable())
		{
			component->OnUpdate();
		}
		if (component->State() == ComponentLifeCycleState::DestroyRequested)
		{
			this->_removeReserved.emplace_back(component);
			this->_components.erase(iterator);
			continue;
		}
	}
	for (auto component : this->_removeReserved)
	{
		delete component;
	}
	this->_removeReserved.clear();
}
void GameObject::_InternalLateUpdate()
{
	for (auto component : this->_components)
	{
		if (component->Enable())
		{
			component->OnLateUpdate();
		}
	}
}
void GameObject::_InternalDestroy()
{
	for (auto component : this->_appendReserved)
	{
		delete component;
	}
	this->_appendReserved.clear();
	for (auto component : this->_components)
	{
		component->OnDestroy();
		delete component;
	}
	this->_components.clear();
	for (auto component : this->_removeReserved)
	{
		component->OnDestroy();
		delete component;
	}
	this->_removeReserved.clear();
}

std::vector<Component*> Egliss::ComponentSystem::GameObject::_InternalComponents() const
{
	const auto componentCount = _appendReserved.size() + _components.size() + _removeReserved.size();
	std::vector<Component*> output;
	output.reserve(componentCount);
	output.insert(output.end(), this->_appendReserved.begin(), this->_appendReserved.end());
	output.insert(output.end(), this->_components.begin(), this->_components.end());
	output.insert(output.end(), this->_removeReserved.begin(), this->_removeReserved.end());

	// RVO
	return output;
}

