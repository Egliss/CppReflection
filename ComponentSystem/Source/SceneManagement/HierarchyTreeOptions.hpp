#pragma once

namespace Egliss::ComponentSystem
{
	struct HiralchyTreeOptions
	{
		GameObject* root = nullptr;
		int indent = 2;
		bool ignoreComponent = false;
		bool ignoreGameObjectId = false;
		bool ignoreComponentId = false;
	};

	class InternalhierarchyTreeOption;
	class ComponentSystemDebugger
	{
	public:
		static std::string CreateHiralchyTreeText(const HiralchyTreeOptions& options);
	private:
		static void CreatehierarchyTreeTextWithGameObject(const GameObject* target, std::stringstream& text, InternalhierarchyTreeOption& options);
		static void CreatehierarchyTreeTextWithComponent(const Component* target, std::stringstream& text, const InternalhierarchyTreeOption& options);
	};
}
