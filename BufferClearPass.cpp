#include "BufferClearPass.h"
#include "RenderTarget.h"
#include "DepthStencil.h"
#include "Source.h"
#include "Sink.h"


namespace Rgph {
	BufferClearPass::BufferClearPass(std::string name)
		:
		Pass(std::move(name))
	{
		RegisterSink(DirectBufferSink<Bind::BufferResource>::Make("buffer", buffer));
		RegisterSource(DirectBufferSource<Bind::BufferResource>::Make("buffer", buffer));
	}

	void BufferClearPass::Execute(Graphics& gfx) const noexcept(!IS_DEBUG)
	{
		buffer->Clear(gfx);
	}
}