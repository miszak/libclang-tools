#ifndef __TRANSLATION_UNIT_HPP__
#define __TRANSLATION_UNIT_HPP__

#include <ClangTools/Diagnostic.hpp>

#include <clang-c/Index.h>


namespace ClangTools
{

class TranslationUnit
{
public:
    class AstWalker
    {
    public:
        AstWalker(CXCursorVisitor visitor, CXClientData data) :
            m_visitor(visitor),
            m_data(data)
        {}

        CXClientData getClientData() const
        {
            return m_data;
        }

        CXCursorVisitor getVisitor() const
        {
            return m_visitor;
        }

        void setFileName(String fileName)
        {
            m_fileName = fileName;
        }

        String const & getFileName() const
        {
            return m_fileName;
        }

    private:
        CXCursorVisitor m_visitor;
        CXClientData m_data;
        String m_fileName;
    };

public:
    TranslationUnit(int argc, char *argv[]) :
        m_filename(argv[1])
    {
        m_index = clang_createIndex(0, 0);
        m_tu = clang_parseTranslationUnit(m_index, 0, argv, argc, 0, 0,
                                 CXTranslationUnit_DetailedPreprocessingRecord);
    }

    String getFilename() const
    {
        return m_filename;
    }

    unsigned getNumDiagnostics() const
    {
        return clang_getNumDiagnostics(m_tu);
    }

    Diagnostic getDiagnostic(unsigned i)
    {
        return Diagnostic(clang_getDiagnostic(m_tu, i));
    }

    CXCursor getCursor() const
    {
        return clang_getTranslationUnitCursor(m_tu);
    }

    void walkAst(AstWalker * astWalker)
    {
        auto cursor = getCursor();
        auto fileName = clang_getTranslationUnitSpelling(m_tu);
        astWalker->setFileName(String(fileName));
        clang_visitChildren(cursor, astWalker->getVisitor(), astWalker);
    }

    CXCodeCompleteResults * completeCode(unsigned line, unsigned column)
    {
        return
            clang_codeCompleteAt(
                    m_tu,
                    m_filename.c_str(),
                    line,
                    column,
                    0,
                    0,
                    clang_defaultCodeCompleteOptions());
    }

    ~TranslationUnit()
    {
        clang_disposeTranslationUnit(m_tu);
        clang_disposeIndex(m_index);
    }

private:
    CXIndex m_index;
    CXTranslationUnit m_tu;
    String m_filename;
};

} // namespace ClangTools

#endif // __TRANSLATION_UNIT_HPP__

