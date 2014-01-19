#include <ClangTools/TranslationUnit.hpp>

#include <clang-c/Index.h>

#include <iostream>

CXChildVisitResult visitor(
        CXCursor cursor, CXCursor parent, CXClientData client_data)
{
    auto sourceLocation = clang_getCursorLocation(cursor);
    CXFile file;
    clang_getFileLocation(sourceLocation, &file, 0, 0, 0);
    auto fileName = clang_getFileName(file);
    auto fileNameStr = ClangTools::String(fileName);

    if (fileNameStr != "/home/miszak/libclang-tools/Examples/eFunctions.cpp")
    {
        return CXChildVisit_Recurse;
    }

    if (clang_getCursorKind(cursor) == CXCursor_FunctionDecl)
    {
        auto cursorSpelling = clang_getCursorSpelling(cursor);
        std::cout << ClangTools::String(cursorSpelling) << std::endl;
    }
    return CXChildVisit_Recurse;
}

int main(int argc, char *argv[])
{
    auto translationUnit = ClangTools::TranslationUnit(argc, argv);
    auto cursor = translationUnit.getCursor();
    clang_visitChildren(cursor, visitor, 0);
    return 0;
}

