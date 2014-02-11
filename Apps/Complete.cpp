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
        for (auto j = 0u;
             j < clang_getNumCompletionChunks(complStr);
             ++j)
        {
            auto completionStr =
                    clang_getCompletionChunkText(complStr, j);
            auto printableCompl = ClangTools::String(completionStr);
//            std::cout << (j ? "_" : "") << printableCompl;
            std::cout << printableCompl << "_" /*<< " -> " <<
                clang_getCompletionChunkKind(completionResults->Results[i].CompletionString, j)*/;
        }

        std::cout << std::endl;
    }

    return 0;
}

