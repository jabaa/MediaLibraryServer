cmake_minimum_required (VERSION 3.7.2)
project (MediaLibraryServer VERSION 0.0.1 LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

IF ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CFLAGS -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Weffc++ -Werror)
    IF ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        SET(CFLAGS ${CFLAGS} -Weverything)
    ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # using GCC
    ENDIF ()
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++
ENDIF ()

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(SRC_FILES src/main.cpp src/MediaLibraryServer.cpp src/MediaLibraryServer.hpp src/HttpRequestHandlerFactory.hpp src/ApiRequestHandler.cpp src/ApiRequestHandler.hpp src/WebRequestHandler.cpp src/WebRequestHandler.hpp)
add_executable (MediaLibraryServer ${SRC_FILES})
target_link_libraries(MediaLibraryServer CONAN_PKG::Poco CONAN_PKG::boost CONAN_PKG::fmt)
target_compile_options(MediaLibraryServer PRIVATE ${CFLAGS})
