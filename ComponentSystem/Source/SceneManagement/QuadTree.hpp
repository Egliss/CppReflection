#pragma once

namespace Egliss::SceneManagement
{
	class QuadTreeAgent;
	template<class ElementT>
	class QuadTree
	{
	public:
		QuadTree(int hierarchy) : Hierarchy(hierarchy)
		{
			if (hierarchy < 0)
				return;
			if (hierarchy >= HierarchyMax)
				return;

			if (hierarchy == 0)
			{
				this->_linearTree.reserve(1);
				this->_linearTree.emplace_back();
				return;
			}
			int totalElementCount = 0;
			for (int L10 = 0; L10 < hierarchy + 1; L10++)
			{
				totalElementCount += (int)std::pow(4, L10);
			}

			this->_linearTree.reserve(totalElementCount);

			for (int L10 = 0; L10 < totalElementCount; L10++)
			{
				this->_linearTree.emplace_back();
			}
		}
		const ElementT& GetByIndex(int index)
		{
			return this->_linearTree[index];
		}
		const ElementT& GetByMortonOrder(int mortonOrder, int hierarchy)
		{
			const auto index = ToLinearIndex(mortonOrder, hierarchy);
			return this->_linearTree[index];
		}
		int ToLinearIndex(int mortonOrder, int hierarchy)
		{
			int n = 4 - 1;
			int linearOffset = (int)(std::pow(4, hierarchy) - 1) / n;
			return mortonOrder + linearOffset;
		}
		const std::vector<ElementT>& MortonLinearTree() const
		{
			return this->_linearTree;
		}
		const int Hierarchy;
		static constexpr inline int HierarchyMax = 12;
	private:
		void _RegisterObject(const QuadTreeAgent& agent);
		std::vector<ElementT> _linearTree;
	};
}