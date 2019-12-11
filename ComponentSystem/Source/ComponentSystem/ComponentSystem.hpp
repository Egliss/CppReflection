#pragma once

#include "../Extensions/CrtNew.hpp"

#include <vector>
#include <string>
#include <functional>
#include <type_traits>

namespace Egliss::ComponentSystem
{
	class GameObject;
	class Component;
	class Transform;
	class RectTransform;
}

#include "../Reflection/Reflection.hpp"

#include "./Component.hpp"
#include "./GameObject.hpp"
#include "./GameObject.inl"
#include "./Transform.hpp"
#include "./RectTransform.hpp"

