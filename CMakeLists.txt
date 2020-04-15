cmake_minimum_required(VERSION 3.8)
project(silver-umbrella)

add_executable(${PROJECT_NAME} main.c)
if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:demo /SUBSYSTEM:Windows /OPT:REF /OPT:ICF=10 /VERBOSE /NODEFAULTLIB")
    target_compile_options(${PROJECT_NAME} PRIVATE /Gy /O1 /fp:fast /GR- /GS- /MT )
    target_link_libraries(${PROJECT_NAME} User32 Winmm ucrt msvcrt vcruntime Vfw32)
endif()
