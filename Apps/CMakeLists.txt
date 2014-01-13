SET(TARGET_diagnose diagnose)
ADD_EXECUTABLE(${TARGET_diagnose} Diagnose.cpp)
TARGET_LINK_LIBRARIES(${TARGET_diagnose} clang)
