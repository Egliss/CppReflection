// This file generated by CppReflection.ClassExpoter.
#include "../ComponentSystem/ComponentSystem.hpp"
#include "../Game/Game.hpp"

using namespace Egliss::Reflection;
using namespace std::string_literals;

std::vector<DynamicTypeDescription> DynamicTypeManager::_indexedTypes;
std::unordered_map<std::string, int> DynamicTypeManager::_typesindices;


void Egliss::Reflection::DynamicTypeManager::Initialize()
{
	_indexedTypes.emplace_back("Egliss::ComponentSystem::Component", false,std::vector<int>({0}),[](){return new Egliss::ComponentSystem::Component();});
	_typesindices.insert(std::make_pair("Egliss::ComponentSystem::Component"s,0));
	_indexedTypes.emplace_back("Egliss::ComponentSystem::Transform", false,std::vector<int>({1 ,0}),[](){return new Egliss::ComponentSystem::Transform();});
	_typesindices.insert(std::make_pair("Egliss::ComponentSystem::Transform"s,1));
	_indexedTypes.emplace_back("Egliss::ComponentSystem::RectTransform", false,std::vector<int>({2 ,1 ,0}),[](){return new Egliss::ComponentSystem::RectTransform();});
	_typesindices.insert(std::make_pair("Egliss::ComponentSystem::RectTransform"s,2));
	_indexedTypes.emplace_back("Egliss::Game::Dummy", false,std::vector<int>({3 ,0}),[](){return new Egliss::Game::Dummy();});
	_typesindices.insert(std::make_pair("Egliss::Game::Dummy"s,3));
}
