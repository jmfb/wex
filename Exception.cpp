#include "Exception.h"
#include <sstream>

namespace Wex
{
	Exception::Exception(
		const std::string& file,
		int line,
		const std::string& whenCompiled,
		const std::string& whenModified,
		const std::string& function,
		const std::string& location,
		int errorCode,
		const std::string& description)
		: file(file),
		line(line),
		whenCompiled(whenCompiled),
		whenModified(whenModified),
		function(function),
		location(location),
		errorCode(errorCode),
		description(description)
	{
		std::ostringstream out;
		out << "File:          " << file << std::endl
			<< "Line:          " << line << std::endl
			<< "When Compiled: " << whenCompiled << std::endl
			<< "When Modified: " << whenModified << std::endl
			<< "Function:      " << function << std::endl
			<< "Location:      " << location << std::endl
			<< "Error Code:    " << errorCode << std::endl
			<< "Description:   " << description << std::endl;
		fullDescription = out.str();
	}
	
	const char* Exception::what() const noexcept(true)
	{
		return fullDescription.c_str();
	}
	
	const std::string& Exception::GetFile() const
	{
		return file;
	}
	
	int Exception::GetLine() const
	{
		return line;
	}
	
	const std::string& Exception::GetWhenCompiled() const
	{
		return whenCompiled;
	}
	
	const std::string& Exception::GetWhenModified() const
	{
		return whenModified;
	}
	
	const std::string& Exception::GetFunction() const
	{
		return function;
	}
	
	const std::string& Exception::GetLocation() const
	{
		return location;
	}
	
	int Exception::GetErrorCode() const
	{
		return errorCode;
	}
	
	const std::string& Exception::GetDescription() const
	{
		return description;
	}
	
	const std::string& Exception::GetFullDescription() const
	{
		return fullDescription;
	}
}

