#pragma once

// Package: Core

#include <string>
namespace PublicUtils
{
#ifdef _WIN32
std::string CastErrorMessage(unsigned int code);
#endif

class FrameworkException : public std::exception

{
public:
    FrameworkException(const std::string& file, size_t line, const std::string& msg, int code = 0);

    FrameworkException(const std::string& file, size_t line, const std::string& msg, const std::string& arg, int code = 0);

    virtual ~FrameworkException() throw();

    virtual const char* Name() const throw();

    virtual const char* ClassName() const throw();

    virtual const char* what() const throw();

    const std::string& Message() const;

    int Code() const;

    std::string DisplayText() const;

    virtual void Rethrow() const;

    const std::string& File() const;

    size_t Line() const;

protected:
    FrameworkException(const std::string& file, size_t line, int code = 0);

    void Message(const std::string& msg);

    void ExtendedMessage(const std::string& arg);

    void GenerateDisplay();

private:
    std::string _msg;
    int			_code;
    std::string _file;
    size_t      _line;
    std::string _display;
};

#define DECLARE_IMPLEMENT_EXCEPTION(CLS, BASE, NAME, CODE)													\
class CLS: public BASE														\
	{																				\
	public:																			\
		CLS(const std::string& file, size_t line, int code = CODE):BASE(file,line,code){}														\
		CLS(const std::string& file, size_t line, const std::string& msg, int code = CODE):BASE(file,line,msg,code){}								\
		CLS(const std::string& file, size_t line, const std::string& msg, const std::string& arg, int code = CODE):BASE(file,line,msg,arg,code){}		\
		virtual const char* Name() const throw(){return NAME;}											\
};
DECLARE_IMPLEMENT_EXCEPTION(SystemException, FrameworkException, "System exception", 0)

DECLARE_IMPLEMENT_EXCEPTION(InvalidArgumentException, FrameworkException, "Invalid argument exception", 0)
DECLARE_IMPLEMENT_EXCEPTION(NotImplementedException, FrameworkException, "Not implemented ", 0)
DECLARE_IMPLEMENT_EXCEPTION(CreateFileException, FrameworkException, "Create file exception", 0)
DECLARE_IMPLEMENT_EXCEPTION(OpenFileException, FrameworkException, "Can't open file", 0)
DECLARE_IMPLEMENT_EXCEPTION(NotFoundException, FrameworkException, "Not found", 0)
DECLARE_IMPLEMENT_EXCEPTION(SyntaxException, FrameworkException, "Syntax error", 0)
DECLARE_IMPLEMENT_EXCEPTION(CircularReferenceException, FrameworkException, "Circular reference", 0)

#define FRAMEWORK_EXCRPTION(ExceptionType, ...) ExceptionType(__FILE__,__LINE__,##__VA_ARGS__)
}
