#pragma once

namespace Egliss::Reflection
{
	template<class T>
	class StaticTypeDescription
	{
		// 型固有のId
		// static constexpr int Id = 0;
		// インスタンス化可能か
		// static constexpr bool IsAbstract = true;
		// Rootまで辿る際に使用する型Id一覧
		// static constexpr auto ParentTypeIds = std::array<int, 1> { -1 };
	};

	template<class T>
	using Static = StaticTypeDescription<T>;
}


