#pragma once
#include "Graphics.h"
#include <memory>
#include <string>


class Drawable;
class TechniqueProbe;


namespace Bind {
	class Bindable
	{
	public:
		virtual void Bind(Graphics& gfx) noexcept = 0;
		virtual ~Bindable() = default;
		virtual void InitializeParentReference(const Drawable&) noexcept
		{}
		virtual std::string GetUID() const noexcept
		{
			assert(false);
			return "";
		}
		virtual void Accept(TechniqueProbe&)
		{}
	protected:
		static ID3D11DeviceContext* GetContext(Graphics & gfx) noexcept;
		static ID3D11Device* GetDevice(Graphics & gfx) noexcept;
		static DxgiInfoManager& GetInfoManager(Graphics & gfx) noexcept(!IS_DEBUG);
	};


	class CloningBindable : public Bindable
	{
	public:
		virtual std::unique_ptr<CloningBindable> Clone() const noexcept = 0;
	};
}
