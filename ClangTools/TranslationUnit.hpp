#ifndef __TRANSLATION_UNIT_HPP__
#define __TRANSLATION_UNIT_HPP__

#include <ClangTools/Diagnostic.hpp>

#include <clang-c/Index.h>


namespace ClangTools
{

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

} // namespace ClangTools

#endif // __TRANSLATION_UNIT_HPP__

