#pragma once
#include "Bindable.h"

namespace Bind
{
	class Sampler : public Bindable
	{
	public:
		Sampler(Graphics& gfx, bool anisoEnable, bool reflect);
		void Bind(Graphics& gfx) noexcept(!IS_DEBUG) override;
		std::string GetUID() const noexcept override;
		static std::shared_ptr<Sampler> Resolve(Graphics& gfx, bool anisoEnable = true, bool reflect = false);
		static std::string GenerateUID(bool anisoEnable, bool reflect);
	protected:
		Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
		bool anisoEnable;
		bool reflect;
	};
}