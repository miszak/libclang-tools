IF(USE_CLANG)
    # C++ compiler flags
    SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Wno-unused-parameter -Wno-parentheses -pedantic -Qunused-arguments -fcolor-diagnostics" )
    SET(CMAKE_CXX_FLAGS_DEBUG "-gdwarf-3 -g -O0 -fsanitize=address -fno-omit-frame-pointer" )
    SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNO_DEBUG -DNDEBUG" )
    # C compiler flags
    SET(CMAKE_C_FLAGS "")
    SET(CMAKE_C_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    SET(CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    # additional flags
    SET(CMAKE_EXE_LINKER_FLAGS "-lstdc++")
ELSE(USE_CLANG)
    # C++ compiler flags
    SET(CMAKE_CXX_FLAGS "-std=c++11 -pipe -fstack-protector-all -Wall -Wextra -Wno-unused-parameter -Wno-unused-but-set-parameter -Wno-parentheses -pedantic -Wno-unused-local-typedefs" )
    SET(CMAKE_CXX_FLAGS_DEBUG "-gdwarf-3 -O0 -fsanitize=address -fno-omit-frame-pointer" )
    SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNO_DEBUG -DNDEBUG -fPIC -rdynamic" )
    # C compiler flags
    SET(CMAKE_C_FLAGS "")
    SET(CMAKE_C_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    SET(CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    # additional flags
    SET(CMAKE_EXE_LINKER_FLAGS "-lstdc++")
ENDIF(USE_CLANG)

SET(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

