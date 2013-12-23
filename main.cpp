#include <iostream>
#include <clang-c/Index.h>

int main(int argc, char *argv[])
{
    auto index = clang_createIndex(0, 0);
    auto tu =
        clang_parseTranslationUnit(index, 0, argv, argc,
                                   0, 0, CXTranslationUnit_DetailedPreprocessingRecord);

    struct List { int a; };
//     int sum(union List *L) { return 0; }

    auto n = clang_getNumDiagnostics(tu);
    for (auto i = 0u; i != n; ++i)
    {
        auto diag = clang_getDiagnostic(tu, i);
        auto diagStr =
            clang_formatDiagnostic(diag, clang_defaultDiagnosticDisplayOptions());
        std::cout << clang_getCString(diagStr) << std::endl;

        auto numFixIts = clang_getDiagnosticNumFixIts(diag);

        for (auto j = 0u; j != numFixIts; ++j)
        {
            CXSourceRange replRange;
            auto fixIt = clang_getDiagnosticFixIt(diag, j, &replRange);
            unsigned line, column, offset;
            clang_getSpellingLocation(clang_getRangeStart(replRange), 0, &line, &column, &offset);
            std::cout << line << " " << column << " " << offset <<
                clang_getCString(fixIt) << std::endl;

            clang_disposeString(fixIt);
        }

        clang_disposeString(diagStr);
    }

    clang_disposeTranslationUnit(tu);
    clang_disposeIndex(index);

    return 0;
}

