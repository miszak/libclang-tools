#include <iostream>
#include <clang-c/Index.h>

#include <string>
#include <vector>
#include <utility>
#include <sstream>

/* ideas:
 * 1) Function name checker (with functor which decides what to check) - separate
 *    for functions, functions in namespaces and member functions
 * 2)
 */

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

    std::string getText() const
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

class Diagnostic
{
public:
    class FixIt
    {
    public:
        FixIt(char const * fixIt, CXSourceRange range) :
            m_range(range),
            m_fixIt(fixIt)
        {
        }

        std::string getText() const
        {
            return m_fixIt;
        }

        SourceRange getRange() const
        {
            return m_range;
        }

    private:
        SourceRange m_range;
        std::string m_fixIt;
    };

    Diagnostic(CXDiagnostic diag) :
        m_diag(diag)
    {
    }

    ~Diagnostic()
    {
        clang_disposeDiagnostic(m_diag);
    }

    std::string getText() const
    {
        auto diagStr = clang_formatDiagnostic(
                                 m_diag, clang_defaultDiagnosticDisplayOptions());
        auto str = std::string(clang_getCString(diagStr));
        clang_disposeString(diagStr);
        return str;
    }

    SourceLocation getLocation() const
    {
        auto loc = clang_getDiagnosticLocation(m_diag);
        unsigned line, column;
        clang_getSpellingLocation(loc, 0, &line, &column, 0);
        return std::make_pair(line, column);
    }

    std::vector<SourceRange> getRanges() const
    {
        std::vector<SourceRange> ranges;
        for (auto i = 0u; i < clang_getDiagnosticNumRanges(m_diag); ++i)
        {
            ranges.push_back(SourceRange(clang_getDiagnosticRange(m_diag, i)));
        }
        return ranges;
    }

    std::vector<FixIt> getFixIts() const
    {
        std::vector<FixIt> fixIts;

        for (auto i = 0u; i < clang_getDiagnosticNumFixIts(m_diag); ++i)
        {
            CXSourceRange range;
            auto fixItStr = clang_getDiagnosticFixIt(m_diag, i, &range);
            fixIts.push_back(FixIt(clang_getCString(fixItStr), range));
            clang_disposeString(fixItStr);
        }

        return fixIts;
    }

private:
    CXDiagnostic m_diag;
};

class TranslationUnit
{
public:
    TranslationUnit(int argc, char *argv[])
    {
        m_index = clang_createIndex(0, 0);
        m_tu = clang_parseTranslationUnit(m_index, 0, argv, argc, 0, 0,
                                 CXTranslationUnit_DetailedPreprocessingRecord);
    }

    unsigned getNumDiagnostics() const
    {
        return clang_getNumDiagnostics(m_tu);
    }

    Diagnostic getDiagnostic(unsigned i)
    {
        return Diagnostic(clang_getDiagnostic(m_tu, i));
    }

    ~TranslationUnit()
    {
        clang_disposeTranslationUnit(m_tu);
        clang_disposeIndex(m_index);
    }

private:
    CXIndex m_index;
    CXTranslationUnit m_tu;
};

int main(int argc, char *argv[])
{
    auto tu = TranslationUnit(argc, argv);
    for (auto i = 0u; i < tu.getNumDiagnostics(); ++i)
    {
        auto diag = tu.getDiagnostic(i);
        std::cout << diag.getText() << std::endl;

        auto loc = diag.getLocation();
        std::cout << "    Loc: " << loc.first << ":" << loc.second << std::endl;

        for (auto range : diag.getRanges())
        {
            std::cout << "    Range: " << range.getText() << std::endl;
        }

        for (auto fixIt : diag.getFixIts())
        {
            auto range = fixIt.getRange();
            std::cout << "    FixIt: " << range.getText() << ": "
                      << fixIt.getText() << std::endl;
        }
    }

    return 0;
}

