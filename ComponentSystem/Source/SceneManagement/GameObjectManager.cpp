#include "../ComponentSystem/ComponentSystem.hpp"
#include "./GameObjectManager.hpp"
// #include "./QuadTree.hpp"

using namespace Egliss::SceneManagement;
using namespace Egliss::ComponentSystem;

std::vector<GameObject*> GameObjectManager::_entities;
int GameObjectManager::_primaryId;

void GameObjectManager::Initialize()
{
	GameObjectManager::_primaryId = 0;
	// GameObjectManager::_entities = std::make_unique<QuadTree<std::vector<GameObject*>>>(4);
}

void GameObjectManager::Finalize()
{
	GameObjectManager::_primaryId = 0;
	for (const auto GameObject : GameObjectManager::_entities) {
		delete GameObject;
	}
	GameObjectManager::_entities.clear();
	// GameObjectManager::_entities =nullptr;
}

GameObject* GameObjectManager::Create(const std::string& name)
{
	auto gameObject = new GameObject();
	gameObject->_InternalState(GameObjectLifeCycleState::Birthed);
	gameObject->_InternalId(GameObjectManager::_primaryId++);
	gameObject->Name(name);
	gameObject->AddComponent<Transform>();
	GameObjectManager::_entities.push_back(gameObject);
	return gameObject;
}

void GameObjectManager::Destroy(GameObject* GameObject)
{
	GameObject->Destroy();
}

void GameObjectManager::Update()
{
	for (const auto GameObject: GameObjectManager::_entities) {
		if (GameObject->Enable())
			GameObject->_InternalUpdate();
	}
}

GameObject* GameObjectManager::Find(const std::string& name)
{
	return GameObjectManager::Find([name](const GameObject* GameObject)
	{
		return GameObject->Name() == name;
	});
}

GameObject* GameObjectManager::Find(const std::function<bool(const GameObject*)>& functor)
{
	for (const auto GameObject : GameObjectManager::_entities) {
		if (functor(GameObject))
			return GameObject;
	}
	return nullptr;
}
