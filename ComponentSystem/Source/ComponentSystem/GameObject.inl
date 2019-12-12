#pragma once

namespace Egliss::ComponentSystem
{
	inline void GameObject::_InternalAddComponent(Component* component, int typeId)
	{
		this->_appendReserved.emplace_back(component);
		this->_appendReserved.back()->_InternalAwake(this, typeId);
	}

	template<class T>
	inline T* GameObject::AddComponent()
	{
		const auto typeId = Reflection::StaticTypeDescription<T>::Id;
		const auto component = new T();
		// GameObject�ւ̊֘A�t��
		this->_InternalAddComponent(component, typeId);
		return component->As<T>();
	}

	inline Component* GameObject::AddComponentByName(const std::string& typeName)
	{
		const auto description = Reflection::DynamicTypeManager::FindByTypeName(typeName);
		if(description == nullptr)
			return nullptr;
		if (description->isAbstract) {
			return nullptr;
		}
		const auto component = static_cast<Component*>(description->constructor());
		this->_InternalAddComponent(component, description->id);
		return component;
	}

	template<class T>
	inline T* GameObject::AddComponentByNameAs(const std::string& typeName)
	{
		return static_cast<T*>(this->AddComponentByName(typeName));
	}
	template<class T, class U>
	static inline T* _InternalGetComponentFrom(const U& container)
	{
		// ��������^��ID���E��
		const int inputTypeId = Reflection::StaticTypeDescription<T>::Id;
		// �R���e�i�ɑ��݂���R���|�[�l���g���
		for (const auto component : container)
		{
			const auto typeID = component->TypeId();
			// �^�����擾
			const auto& description = Reflection::DynamicTypeManager::IndexOf(typeID);
			// ���N���X�܂ł̌^ID�ꗗ��H���đΏۂ�ID�����݂��邩
			if (description.HasTypeRelation(inputTypeId))
			{
				return component->As<T>();
			}
		}
		return nullptr;
	}

	template<class T>
	inline T* GameObject::GetComponent() const
	{
		auto component = _InternalGetComponentFrom<T>(this->_appendReserved);

		if (component)
			return component;

		component = _InternalGetComponentFrom<T>(this->_components);

		if (component)
			return component;
		return nullptr;
	}
}