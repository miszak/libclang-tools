#include <ClangTools/TranslationUnit.hpp>

#include <clang-c/Index.h>

#include <iostream>


int main(int argc, char *argv[])
{
    auto tu = ClangTools::TranslationUnit(argc, argv);


    return 0;
}

