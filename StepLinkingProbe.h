#pragma once
#include "TechniqueProbe.h"

namespace Rgph {
	class RenderGraph;
}

namespace Rgph {
	class StepLinkingProbe : public TechniqueProbe
	{
	protected:
		void OnSetStep() override;
	private:
		Rgph::RenderGraph& rg;
	};
}