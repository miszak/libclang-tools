#include <ClangTools/TranslationUnit.hpp>
#include <ClangTools/Diagnostic.hpp>

#include <clang-c/Index.h>

#include <iostream>


int main(int argc, char *argv[])
{
    std::cout << std::endl;

    auto translationUnit = ClangTools::TranslationUnit(argc, argv);

    for (auto i = 0u; i < translationUnit.getNumDiagnostics(); ++i)
    {
        auto diagnostic = translationUnit.getDiagnostic(i);
        std::cout << diagnostic.getText() << std::endl;
        std::cout << "    Severity: " << diagnostic.getSeverityText() << std::endl;

        auto diagnosticLocation = diagnostic.getLocation();
        std::cout << "    Loc: " << diagnosticLocation.first << ":" 
                                 << diagnosticLocation.second << std::endl;

        for (auto diagnosticRange : diagnostic.getRanges())
        {
            std::cout << "    Range: " << diagnosticRange.getText() << std::endl;
        }

        for (auto diagnosticFixIt : diagnostic.getFixIts())
        {
            auto fixItRange = diagnosticFixIt.getRange();
            std::cout << "    FixIt: " << fixItRange.getText() << ": "
                      << diagnosticFixIt.getText() << std::endl;
        }
    }

    return 0;
}

