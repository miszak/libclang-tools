#ifndef __SOURCE_LOCATIONS_HPP__
#define __SOURCE_LOCATIONS_HPP__

#include <ClangTools/String.hpp>

#include <clang-c/Index.h>

#include <utility>
#include <sstream>


namespace ClangTools
{

typedef std::pair<unsigned, unsigned> SourceLocation;

class SourceRange
{
public:
    SourceRange(CXSourceRange range) :
        m_range(range)
    {
    }

    SourceLocation getStart() const
    {
        return getSourceLocation(clang_getRangeStart(m_range));
    }

    SourceLocation getEnd() const
    {
        return getSourceLocation(clang_getRangeEnd(m_range));
    }

    String getText() const
    {
        std::ostringstream oss;
        oss << getStart().first << ":" << getStart().second << " - "
            << getEnd().first << ":" << getEnd().second;
        return oss.str();
    }

private:
    CXSourceRange m_range;

    SourceLocation getSourceLocation(CXSourceLocation location) const
    {
        unsigned line, column;
        clang_getSpellingLocation(location, 0, &line, &column, 0);
        return std::make_pair(line, column);
    }
};

} // namespace ClangTools

#endif // __SOURCE_LOCATIONS_HPP__


