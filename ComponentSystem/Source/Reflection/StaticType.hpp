#pragma once

namespace Egliss::Reflection
{
	template<class T>
	class StaticTypeDescription
	{
		// �^�ŗL��Id
		// static constexpr int Id = 0;
		// �C���X�^���X���\��
		// static constexpr bool IsAbstract = true;
		// Root�܂ŒH��ۂɎg�p����^Id�ꗗ
		// static constexpr auto ParentTypeIds = std::array<int, 1> { -1 };
	};

	template<class T>
	using Static = StaticTypeDescription<T>;
}


