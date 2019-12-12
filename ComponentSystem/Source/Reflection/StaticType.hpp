#pragma once

namespace Egliss::Reflection
{
	template<class T>
	class StaticTypeDescription
	{
		// å^å≈óLÇÃId
		// static constexpr int Id = 0;
		// ÉNÉâÉXÇÃñºèÃ
		// static constexpr std::string_view Name = "NameSpace::ClassName";
	};

	template<class T>
	using Static = StaticTypeDescription<T>;
}


