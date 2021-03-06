#ifndef __DIAGNOSTIC_HPP__
#define __DIAGNOSTIC_HPP__

#include <ClangTools/SourceLocations.hpp>
#include <ClangTools/String.hpp>

#include <clang-c/Index.h>

#include <vector>


namespace ClangTools
{

class Diagnostic
{
public:
    class FixIt
    {
    public:
        FixIt(String fixIt, CXSourceRange range) :
            m_range(range),
            m_fixIt(fixIt)
        {
        }

        String getText() const
        {
            return m_fixIt;
        }

        SourceRange getRange() const
        {
            return m_range;
        }

    private:
        SourceRange m_range;
        String m_fixIt;
    };

    Diagnostic(CXDiagnostic diag) :
        m_diag(diag)
    {
    }

    ~Diagnostic()
    {
        clang_disposeDiagnostic(m_diag);
    }

    CXDiagnosticSeverity getSeverity() const
    {
        return clang_getDiagnosticSeverity(m_diag);
    }

    String getSeverityText() const
    {
        switch (getSeverity())
        {
            case CXDiagnostic_Ignored:
                return "ignored";
                break;
            case CXDiagnostic_Note:
                return "note";
                break;
            case CXDiagnostic_Warning:
                return "warning";
                break;
            case CXDiagnostic_Error:
                return "error";
                break;
            case CXDiagnostic_Fatal:
                return "fatal";
                break;
            default:
                return "";
                break;
        }
    }

    String getText() const
    {
        auto diagStr = clang_formatDiagnostic(
                                 m_diag, clang_defaultDiagnosticDisplayOptions());
        auto str = String(diagStr);
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
            fixIts.push_back(FixIt(String(fixItStr), range));
        }

        return fixIts;
    }

private:
    CXDiagnostic m_diag;
};

} // namespace ClangTools

#endif // __DIAGNOSTIC_HPP__

