#pragma once
#include <exception>
#include <string>

namespace Wex
{
	class Exception : public std::exception
	{
	public:
		Exception() = default;
		Exception(
			const std::string& file,
			int line,
			const std::string& whenCompiled,
			const std::string& whenModified,
			const std::string& function,
			const std::string& location,
			int errorCode,
			const std::string& description);
		Exception(const Exception& rhs) = default;
		~Exception() noexcept(true) = default;

		Exception& operator=(const Exception& rhs) = default;

		const char* what() const noexcept(true) override;

		const std::string& GetFile() const;
		int GetLine() const;
		const std::string& GetWhenCompiled() const;
		const std::string& GetWhenModified() const;
		const std::string& GetFunction() const;
		const std::string& GetLocation() const;
		int GetErrorCode() const;
		const std::string& GetDescription() const;
		const std::string& GetFullDescription() const;

	private:
		friend class ExceptionTest;
		std::string file;
		int line = 0;
		std::string whenCompiled;
		std::string whenModified;
		std::string function;
		std::string location;
		int errorCode = 0;
		std::string description;
		std::string fullDescription;
	};
}

#define ThrowException(location, errorCode, description) \
	throw Wex::Exception \
	{ \
		__FILE__, \
		__LINE__, \
		__DATE__ " " __TIME__, \
		__TIMESTAMP__, \
		__PRETTY_FUNCTION__, \
		location, \
		errorCode, \
		description \
	}

#define CheckError(isError, errorCode, description) \
	if (isError) \
		ThrowException(#isError, errorCode, description);

