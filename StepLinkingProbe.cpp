#include "StepLinkingProbe.h"
#include "RenderGraph.h"
#include "Step.h"

namespace Rgph {
	void StepLinkingProbe::OnSetStep()
	{
		pStep->Link(rg);
	}
}