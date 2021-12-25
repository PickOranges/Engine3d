#pragma once
#include "Win.h"
#include <exception>
#include <string>

class ExceptionBase : public std::exception
{
public:
	ExceptionBase(int line, const char* file) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;
private:
	int line;
	std::string file;
protected:
	mutable std::string whatBuffer;
};


class Exception : public ExceptionBase
{
	using ExceptionBase::ExceptionBase;
public:
	static std::string TranslateErrorCode(HRESULT hr) noexcept;
};
class HrException : public Exception
{
public:
	HrException(int line, const char* file, HRESULT hr) noexcept;
	const char* what() const noexcept override;
	const char* GetType() const noexcept override;
	HRESULT GetErrorCode() const noexcept;
	std::string GetErrorDescription() const noexcept;
protected:
	HRESULT hr;
};
