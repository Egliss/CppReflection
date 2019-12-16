#include "Extensions/CrtNew.hpp"

#include <iostream>

#include "./Extensions/Extensions.hpp"
#include "./Reflection/Reflection.hpp"
#include "./ComponentSystem/ComponentSystem.hpp"
#include "./SceneManagement/SceneManagement.hpp"
#include "./Game/Game.hpp"

using namespace Egliss::ComponentSystem;
using namespace Egliss::SceneManagement;
using namespace Egliss::Reflection;
using namespace Egliss::Game;

void Func()
{
	auto root = GameObjectManager::Create();
	root->AddComponent<Dummy>();
	auto child0 = GameObjectManager::Create();
	child0->AddComponent<Dummy>();
	child0->AddComponent<Dummy>();
	auto child1 = GameObjectManager::Create();
	child0->AddComponent<Dummy>();
	auto child2 = GameObjectManager::Create();
	auto child3 = GameObjectManager::Create();
	child3->AddComponent<Dummy>();

	root->Transform()->AddChild(child0->Transform());
	child0->Transform()->AddChild(child1->Transform());
	child0->Transform()->AddChild(child2->Transform());
	root->Transform()->AddChild(child3->Transform());

	auto options = HiralchyTreeOptions();
	options.indent = 4;
	options.root = root;
	const auto text = ComponentSystemDebugger::CreateHiralchyTreeText(options);
	std::cout << text << std::endl;
}

// TODO mainはテストと名前が衝突する
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	GameObjectManager::Initialize();
	DynamicTypeManager::Initialize();

	Func();
	GameObjectManager::Finalize();
	DynamicTypeManager::Finalize();

	return 1;
}