#pragma once

namespace Egliss::ComponentSystem
{
	enum struct ComponentLifeCycleState
	{
		Constructed,
		Awaked,
		Started,
		Updated,
		LateUpdated,
		DestroyRequested,
	};

	class GameObject;
	class Component abstract : public Egliss::Reflection::IRfelectionTarget
	{
		using GameObjectT = GameObject;
	public:
		virtual ~Component() = default;
		Component();

		bool Enable()const { return this->_enable; }
		int Id()const { return this->_id; }
		int TypeId()const { return this->_typeId; }
		const GameObjectT* GameObject() const { return this->_GameObject; }
		GameObjectT* GameObject() { return this->_GameObject; }

		ComponentLifeCycleState State() const { return this->_state; }

		void Enable(bool enable) { this->_enable = enable; }
		void Id(int id) { this->_id = id; }
		void TypeId(int typeId) { this->_typeId = typeId; }

		template<class T>
		inline T* As()
		{
			return static_cast<T*>(this);
		}
		template<class T>
		const T* As()const
		{
			return static_cast<const T*>(this);
		}

		virtual void OnAwake() {}
		virtual void OnStart() {}
		virtual void OnUpdate() {}
		virtual void OnLateUpdate() {}
		virtual void OnDestroy() {}

		void _InternalState(ComponentLifeCycleState state) { this->_state = state; }
		void _InternalAwake(GameObjectT* entiry, int typeId);
		void _InternalDestroyRequested();
	private:
		bool _enable;
		int _id;
		int _typeId;
		GameObjectT* _GameObject;
		ComponentLifeCycleState _state;
	};
}
