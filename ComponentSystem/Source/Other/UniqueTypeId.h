#pragma once
namespace Egliss::Reflection
{
	class UniqueTypeId
	{
		static void Initialize();
		template<class T>
		static int Get()
		{
			static int internalId = typeId++;
			return internalId;
		}
		static inline int typeId = 0;
	};
}