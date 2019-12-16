#include "./SceneManagement.hpp"
#include "../ComponentSystem/ComponentSystem.hpp"

using namespace Egliss::ComponentSystem;
using namespace Egliss::SceneManagement;

namespace Egliss::ComponentSystem
{
	class InternalhierarchyTreeOption : public HiralchyTreeOptions
	{
	public:
		int nowhierarchy = 0;

		InternalhierarchyTreeOption(const HiralchyTreeOptions& options)
		{
			*this = options;
		}
		InternalhierarchyTreeOption& operator=(const HiralchyTreeOptions& options)
		{
			this->root = options.root;
			this->indent = options.indent;
			this->ignoreComponent = options.ignoreComponent;
			this->ignoreComponentId = options.ignoreComponentId;
			this->ignoreGameObjectId = options.ignoreGameObjectId;
			return *this;
		}
	};
}

using DebuggerT = ComponentSystemDebugger;

std::string DebuggerT::CreateHiralchyTreeText(const HiralchyTreeOptions& options)
{
	//copy 
	InternalhierarchyTreeOption option = options;
	std::stringstream stream;
	ComponentSystemDebugger::CreatehierarchyTreeTextWithGameObject(options.root, stream, option);
	// RVOが効くのでmoveしない
	return stream.str();
}

void DebuggerT::CreatehierarchyTreeTextWithGameObject(const GameObject* target, std::stringstream& text, InternalhierarchyTreeOption& options)
{
	// コピー
	auto option = options;
	const int blankCount = static_cast<int>(options.nowhierarchy * options.indent);
	text
		<< std::string(blankCount, ' ')
		<< "[" << target->Name() << "(" << std::to_string(target->Id()) << ")]"
		<< std::endl;
	for (const auto component : target->_InternalComponents()) {
		CreatehierarchyTreeTextWithComponent(component, text, options);
	}
	for (const auto child : target->Transform()->Childs()) {
		option.nowhierarchy++;
		CreatehierarchyTreeTextWithGameObject(child->GameObject(), text, option);
	}
	options.nowhierarchy--;
}
void DebuggerT::CreatehierarchyTreeTextWithComponent(const Component* target, std::stringstream& text, const InternalhierarchyTreeOption& options)
{
	const int blankCount = static_cast<int>(options.nowhierarchy * options.indent);
	text
		<< std::string(blankCount, ' ')
		<< "- "
		<< Reflection::DynamicTypeManager::IndexOf(target->TypeId()).name
		<< "(" << std::to_string(target->Id()) << ")"
		<< std::endl;
}