#pragma once
#include "DynamicConstant.h"
#include <string>
#include <memory>
#include <unordered_map>


namespace Dcb
{
	class RawLayout;
	class LayoutElement;
	class CookedLayout;

	class LayoutCodex
	{
	public:
		static CookedLayout Resolve(RawLayout&& layout) noexcept(!IS_DEBUG);
	private:
		static LayoutCodex& Get_() noexcept;
		std::unordered_map<std::string, std::shared_ptr<LayoutElement>> map;
	};
}