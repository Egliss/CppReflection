#pragma once

namespace Egliss::Reflection
{
	template<class T>
	class StaticTypeDescription
	{
		// �^�ŗL��Id
		// static constexpr int Id = 0;
		// �N���X�̖���
		// static constexpr std::string_view Name = "NameSpace::ClassName";
	};

	template<class T>
	using Static = StaticTypeDescription<T>;
}


