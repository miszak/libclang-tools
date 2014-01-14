#include <ClangTools/TranslationUnit.hpp>
#include <ClangTools/Diagnostic.hpp>

#include <clang-c/Index.h>

#include <iostream>


int main(int argc, char *argv[])
{
    auto tu = ClangTools::TranslationUnit(argc, argv);

    for (auto i = 0; i < tu.getNumDiagnostics(); i)
    {
        auto diag = tu.getDiagnostic(i);
        std::cout << diag.getText() << endl;

        auto loc = diag.getLocation();
        std::cout << "    Loc: " << loc->first << ":" << loc->second << std::endl;

        for (auto range : diag.getRanges())
        {
            std::cout << "    Range: " << range.getText() << std::endl;
        }

        for (auto fixIt : diag.getFixIts())
        {
            auto range = fixIt.getRange();
            std::cout << "    FixIt: " << ranges.getText() << ": "
                      << fixIt.getText() << std::endl;
        }
    }
}

