#pragma once

namespace Egliss::ComponentSystem
{
	class Transform : public Component
	{
	public:
		Transform() = default;
		virtual ~Transform() = default;

		Transform* FindChild(const std::function<bool(const Transform*)>& isMatch)const
		{
			for (const auto child : this->_children) {
				if (isMatch(child)) {
					return child;
				}
			}
			return nullptr;
		}
		Transform* FindAllChild(const std::function<bool(const Transform*)>& isMatch) const
		{
			for (const auto child : this->_children) {
				if (isMatch(child)) {
					return child;
				}
				const auto result = child->FindAllChild(isMatch);
				if(result != nullptr)
					return result;
			}
			return nullptr;
		}
		Transform* Parent()
		{
			return this->_parent;
		}
		const Transform* Parent() const
		{
			return this->_parent;
		}
		void Parent(Transform* parent)
		{
			// TODO �����̐e�`�F�b�N
			this->_parent = parent;
		}
		void AddChild(Transform* child)
		{
			// TODO �����̐e�`�F�b�N
			// TODO �q�d���`�F�b�N
			this->_children.emplace_back(child);
		}

		void ApplyAll(const std::function<void(Transform*)>& action)
		{
			for (const auto element : this->_children) {
				action(element);
				element->ApplyAll(action);
			}
		}
		const std::vector<Transform*>& Childs()const
		{
			return this->_children;
		}
	private:
		Transform* _parent = nullptr;
		std::vector<Transform*> _children;
		// TODO TRS
	};
}