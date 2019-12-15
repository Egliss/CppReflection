#pragma once

namespace Egliss::Reflection
{
	class DynamicTypeDescription
	{
	public:
		DynamicTypeDescription() = default;
		DynamicTypeDescription(std::string&& name, bool isAbstract, std::vector<int>&& parentTypeIds, std::function<void* ()>&& constructor)
		{
			this->name = std::move(name);
			this->isAbstract = isAbstract;
			this->parentTypeIds = std::move(parentTypeIds);
			this->constructor = std::move(constructor);
			this->name.shrink_to_fit();
			this->parentTypeIds.shrink_to_fit();
		}
		bool HasTypeRelation(int typeId) const
		{
			// ~‡ƒ\[ƒg‚³‚ê‚Ä‚¢‚é‚½‚ß“ñ•ª’Tõo—ˆ‚é
			return std::binary_search(this->parentTypeIds.rbegin(), this->parentTypeIds.rend(), typeId);
		}

		int Id()const {return this->parentTypeIds[0]; }
		std::string name;
		bool isAbstract;
		std::vector<int> parentTypeIds;
		std::function<void* ()> constructor;
	};

	class DynamicTypeManager
	{
	public:
		static void Initialize();
		static void Finalize()
		{
			_indexedTypes.clear();
			_typesindices.clear();
		}

		static const auto& Types()
		{
			return _indexedTypes;
		}
		static const DynamicTypeDescription& IndexOf(int index)
		{
			return _indexedTypes[index];
		}
		static const DynamicTypeDescription& TypeNameOf(const std::string& typeName)
		{
			auto index = _typesindices.at(typeName);
			return IndexOf(index);
		}
		static const DynamicTypeDescription* FindByTypeName(const std::string& typeName)
		{
			const auto index = _typesindices.find(typeName);
			if(index == _typesindices.end())
				return nullptr;
			return &_indexedTypes[index->second];
		}
	private:
		static std::vector<DynamicTypeDescription> _indexedTypes;
		static std::unordered_map<std::string, int> _typesindices;
	};
}