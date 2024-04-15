cmake_minimum_required(VERSION 3.16)
project(QuackAttack LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(QuackAttack src/main.cpp)

file(COPY src/textures DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

target_link_libraries(QuackAttack PRIVATE sfml-graphics)
target_compile_features(QuackAttack PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET QuackAttack
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:QuackAttack>
        VERBATIM)
endif()

#if(MSVC)
#    set_target_properties(QuackAttack PROPERTIES
#            WIN32_EXECUTABLE YES
#    )
#endif()

install(TARGETS QuackAttack)
