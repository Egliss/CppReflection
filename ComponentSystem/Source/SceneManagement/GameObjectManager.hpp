#pragma once

namespace Egliss::ComponentSystem
{
	class GameObject;
}
namespace Egliss::SceneManagement
{
	template<class T>
	class QuadTree;

	// TODO ComponentSystem‚É’u‚«‚½‚¢
	class GameObjectManager
	{
	// TODO Žl•ª–Ø‚É’u‚«Š·‚¦‚½‚¢
	// using ContainerT = std::unique_ptr<QuadTree<std::vector<GameObject*>>>;
	using ContainerT = std::vector<ComponentSystem::GameObject*>;
	public:
		static void Initialize();
		static void Finalize();
		static void Destroy(ComponentSystem::GameObject* GameObject);
		static void Update();

		static ComponentSystem::GameObject* Create(const std::string& name = "GameObject");
		static ComponentSystem::GameObject* Find(const std::string& GameObjectName);
		static ComponentSystem::GameObject* Find(const std::function<bool(const ComponentSystem::GameObject*)>& functor);

	private:
		static ContainerT _entities;
		static int _primaryId;
	};
}