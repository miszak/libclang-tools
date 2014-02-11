SET(TARGET_diagnose diagnose)
ADD_EXECUTABLE(${TARGET_diagnose} Diagnose.cpp)
TARGET_LINK_LIBRARIES(${TARGET_diagnose} clang)

SET(TARGET_fnc function_name_check)
ADD_EXECUTABLE(${TARGET_fnc} FunctionNameCheck.cpp)
TARGET_LINK_LIBRARIES(${TARGET_fnc} clang)

SET(TARGET_compl complete_code)
ADD_EXECUTABLE(${TARGET_compl} Complete.cpp)
TARGET_LINK_LIBRARIES(${TARGET_compl} clang)
