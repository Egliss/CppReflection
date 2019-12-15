#include "UniqueTypeId.h"
#include "../Reflection/Reflection.hpp"
#include "../ComponentSystem/ComponentSystem.hpp"

void Egliss::Reflection::UniqueTypeId::Initialize()
{
	// DynamicTypeManager.cpp �ŏ���������Id���ɏ��������Ă��炤
	// Id = 0
	UniqueTypeId::Get<Egliss::ComponentSystem::Component>();
	// Id = 1
	UniqueTypeId::Get<Egliss::ComponentSystem::Transform>();
	// Id = 1
	UniqueTypeId::Get<Egliss::ComponentSystem::Transform>();
	// ...
}
