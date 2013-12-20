#include <iostream>
#include <clang-c/Index.h>

int main(int argc, char *argv[])
{
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit tu =
        clang_parseTranslationUnit(index, 0, argv, argc,
                                   0, 0, CXTranslationUnit_DetailedPreprocessingRecord);

    // int a; std::cout << a << std::endl;

    auto n = clang_getNumDiagnostics(tu);
    for (auto i = 0u; i != n; ++i)
    {
        CXDiagnostic diag = clang_getDiagnostic(tu, i);
        CXString diagStr =
            clang_formatDiagnostic(diag, clang_defaultDiagnosticDisplayOptions());
        std::cout << clang_getCString(diagStr) << std::endl;
        clang_disposeString(diagStr);
    }

    clang_disposeTranslationUnit(tu);
    clang_disposeIndex(index);

    return 0;
}

