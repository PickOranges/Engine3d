#include "TimerWrapper.h"
using namespace std::chrono;

TimerWrapper::TimerWrapper() noexcept
{
	last = steady_clock::now();
}

float TimerWrapper::Mark() noexcept
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float TimerWrapper::Peek() const noexcept
{
	return duration<float>(steady_clock::now() - last).count();
}
