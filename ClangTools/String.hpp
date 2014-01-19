#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <clang-c/CXString.h>

#include <string>

namespace ClangTools
{

class String : public std::string
{
public:
    String(CXString & cxstring) :
        std::string((clang_getCString(cxstring) ? clang_getCString(cxstring) : ""))
    {
        clang_disposeString(cxstring);
    }

    String(std::string const & stdstring) :
        std::string(stdstring)
    {
    }

    String(char const * cstring) :
        std::string(cstring)
    {
    }

    std::string str()
    {
        return *this;
    }
};

} // namespace ClangTools

#endif // __STRING_HPP__

