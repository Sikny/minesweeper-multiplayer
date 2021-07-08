cmake_minimum_required(VERSION 3.19)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows-static")

cmake_policy(SET CMP0091 NEW)

project(MineSweeperClient)

add_executable(MineSweeperClient src/main.cpp include/game.h src/game.cpp include/case.h src/case.cpp)

set_property(TARGET MineSweeperClient PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_options(MineSweeperClient PRIVATE /Zc:__cplusplus)
target_compile_features(MineSweeperClient PRIVATE cxx_std_20)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_include_directories(MineSweeperClient PRIVATE include
		)

target_link_libraries(MineSweeperClient PRIVATE
		sfml-system sfml-network sfml-graphics sfml-window)