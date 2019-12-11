#pragma once

namespace Egliss::ComponentSystem
{

	enum struct GameObjectLifeCycleState
	{
		Birthed,
		Activated,
		DestroyRequested,
		Destroy
	};

	class Component;
	class Transform;
	class GameObject
	{
		using TransformT = Transform;
	public:
		GameObject();
		~GameObject()
		{
			this->Destroy();
			this->_InternalDestroy();
		}
		bool Enable()const { return this->_enable; }
		int Id()const { return this->_id; }
		const std::string& Name()const { return this->_name; }
		GameObjectLifeCycleState State()const { return this->_state; }
		TransformT* Transform()const { return this->GetComponent<TransformT>(); }

		void Enable(bool enable) { this->_enable = enable; }
		void Name(const std::string& name) { this->_name = name; }

		template<class T>
		T* AddComponent();
		Component* AddComponentByName(const std::string& typeName);
		template<class T>
		T* AddComponentByNameAs(const std::string& typeName);
		template<class T>
		T* GetComponent() const;

		void Destroy()
		{
			this->_state = GameObjectLifeCycleState::DestroyRequested;
			this->_enable = false;
		}

		// TODO ‚Ç‚¤‚É‚©‚µ‚½‚¢
		void _InternalAddComponent(Component* component, int typeId);
		void _InternalId(int id) { this->_id = id; }
		void _InternalState(GameObjectLifeCycleState state) { this->_state = state; }
		void _InternalUpdate();
		void _InternalLateUpdate();
		void _InternalDestroy();
		std::vector<Component*> _InternalComponents() const;

	private:
		bool _enable = true;
		int _id = -1;
		std::string _name;
		GameObjectLifeCycleState _state;
		std::vector<Component*> _appendReserved;
		std::vector<Component*> _components;
		std::vector<Component*> _removeReserved;
	};
}