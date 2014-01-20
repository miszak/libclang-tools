#include <ClangTools/TranslationUnit.hpp>

#include <clang-c/Index.h>

#include <iostream>
#include <vector>

CXChildVisitResult visitor(
        CXCursor cursor, CXCursor parent, CXClientData client_data)
{
    ClangTools::TranslationUnit::AstWalker * astWalker =
        reinterpret_cast<ClangTools::TranslationUnit::AstWalker *>(client_data);
    std::vector<std::string> & funcNames =
        *(reinterpret_cast<std::vector<std::string> *>(astWalker->getClientData()));

    auto sourceLocation = clang_getCursorLocation(cursor);
    CXFile file;
    clang_getFileLocation(sourceLocation, &file, 0, 0, 0);
    auto fileName = clang_getFileName(file);
    auto fileNameStr = ClangTools::String(fileName);

    if (fileNameStr != astWalker->getFileName())
    {
        return CXChildVisit_Recurse;
    }

    auto func = std::string{};
    auto def = bool{false};

    if (clang_isCursorDefinition(cursor))
    {
        def = true;
    }

    switch (clang_getCursorKind(cursor))
    {
        case CXCursor_FunctionDecl:
            func = "Function ";
            break;
        case CXCursor_FunctionTemplate:
            func = "FunctionTemplate ";
            break;
        case CXCursor_CXXMethod:
            func = "CXXMethod ";
            break;
        default:
            return CXChildVisit_Recurse;
            break;
    }

    func += clang_isCursorDefinition(cursor) ? "definition: " : "declaration: ";

    auto semanticParent = clang_getCursorSemanticParent(cursor);
    auto semanticParentSpelling = clang_getCursorSpelling(semanticParent);
    func += ClangTools::String(semanticParentSpelling) + "::";

    auto cursorSpelling = clang_getCursorSpelling(cursor);
    func += ClangTools::String(cursorSpelling);

    auto lexicalParent = clang_getCursorLexicalParent(cursor);
    auto lexicalParentSpelling = clang_getCursorSpelling(lexicalParent);
    func += " found in: " + ClangTools::String(lexicalParentSpelling);

    funcNames.push_back(func);

    return CXChildVisit_Recurse;
}

int main(int argc, char *argv[])
{
    auto translationUnit = ClangTools::TranslationUnit(argc, argv);
    std::vector<std::string> funcNames;
    auto astWalker = ClangTools::TranslationUnit::AstWalker(visitor, &funcNames);
    translationUnit.walkAst(&astWalker);

    for (const auto & funcName : funcNames)
    {
        std::cout << funcName << std::endl;
    }

    return 0;
}

