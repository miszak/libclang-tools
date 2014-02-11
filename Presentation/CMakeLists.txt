CONFIGURE_FILE(
    1000px-LLVM_Logo.png
    ${CMAKE_BINARY_DIR}/Presentation
    COPYONLY)

ADD_LATEX_DOCUMENT(
    libclang.tex
    DEFAULT_PDF
)
