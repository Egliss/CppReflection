#pragma once

namespace Egliss::ComponentSystem
{
	class GameObject;
}
namespace Egliss::SceneManagement
{
	template<class T>
	class QuadTree;

	// TODO ComponentSystemに置きたい
	class GameObjectManager
	{
	using ContainerT = std::vector<ComponentSystem::GameObject*>;
	public:
		static void Initialize();
		static void Finalize();
		static void Destroy(ComponentSystem::GameObject* GameObject);
		static void Update();

		static ComponentSystem::GameObject* Create(const std::string& name = "GameObject");
		static ComponentSystem::GameObject* Find(const std::string& gameObjectName);
		static ComponentSystem::GameObject* Find(const std::function<bool(const ComponentSystem::GameObject*)>& isSame);

	private:
		static ContainerT _entities;
		static int _primaryId;
	};
}