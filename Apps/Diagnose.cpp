#include <ClangTools/TranslationUnit.hpp>
#include <ClangTools/Diagnostic.hpp>

#include <clang-c/Index.h>

#include <iostream>


int main(int argc, char *argv[])
{
    auto tu = ClangTools::TranslationUnit(argc, argv);

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

