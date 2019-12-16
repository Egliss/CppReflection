#pragma once

namespace Egliss::Extensions
{
	class EglContainer
	{
	public:
		template<class T, class U>
		static std::vector<T, U>&& Concat(std::vector<T, U>& dst, const std::vector<T, U>& source)
		{
			dst.insert(source.begin(), source.end());
		}
	};
}