#pragma once
#include <string>
#include <memory>
#include <typeinfo>
#include "Source.h"
#include "RenderGraphCompileException.h"
#include "Utils.h"
#include "Bindable.h"
#include "BufferResource.h"
#include "RenderTarget.h"
#include "DepthStencil.h"
#include <sstream>
#include <cctype>
#include <type_traits>



namespace Bind
{
	class Bindable;
}


namespace Rgph
{
	class Pass;

	class Sink
	{
	public:
		const std::string& GetRegisteredName() const noexcept;
		const std::string& GetPassName() const noexcept;
		const std::string& GetOutputName() const noexcept;
		void SetTarget(std::string passName, std::string outputName);
		virtual void Bind(Source& source) = 0;
		virtual void PostLinkValidate() const = 0;
		virtual ~Sink() = default;
	protected:
		Sink(std::string registeredName);
	private:
		std::string registeredName;
		std::string passName;
		std::string outputName;
	};
}
