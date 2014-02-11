#include <ClangTools/TranslationUnit.hpp>

#include <clang-c/Index.h>

#include <iostream>


int main(int argc, char *argv[])
{
    auto translationUnit = ClangTools::TranslationUnit(argc - 2, argv);
    auto completionResults = translationUnit.completeCode(
                        std::stoi(argv[argc - 2]), std::stoi(argv[argc - 1]));

    for (auto i = 0u; i < completionResults->NumResults; ++i)
    {
        auto & complStr = completionResults->Results[i].CompletionString;

        auto complComment = clang_getCompletionBriefComment(complStr);
        auto printableComment = ClangTools::String(complComment);
        if (printableComment.length())
        {
            std::cout << "// " << printableComment << std::endl;
        }

        for (auto j = 0u;
             j < clang_getNumCompletionChunks(complStr);
             ++j)
        {
            auto completionChunk =
                    clang_getCompletionChunkText(complStr, j);
            auto printableCompl = ClangTools::String(completionChunk);
            std::cout << printableCompl << " -> " <<
                clang_getCompletionChunkKind(complStr, j);
            std::cout << std::endl;
        }

        for (auto j = 0u;
             j < clang_getCompletionNumAnnotations(complStr);
             ++j)
        {
            auto completionAnn =
                    clang_getCompletionAnnotation(complStr, j);
            auto printableAnn = ClangTools::String(completionAnn);
            std::cout << ">>> " << printableAnn << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}

