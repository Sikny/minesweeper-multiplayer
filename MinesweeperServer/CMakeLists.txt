cmake_minimum_required(VERSION 3.19)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows-static")

cmake_policy(SET CMP0091 NEW)

project(MineSweeperServer)

add_executable(MineSweeperServer src/main.cpp src/Game.cpp src/Game.h src/Cell.cpp src/Cell.h src/UdpServer.cpp src/UdpServer.h)

set_property(TARGET MineSweeperServer PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_options(MineSweeperServer PRIVATE /Zc:__cplusplus)
target_compile_features(MineSweeperServer PRIVATE cxx_std_20)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_include_directories(MineSweeperServer PRIVATE
		)

target_link_libraries(MineSweeperServer PRIVATE
		sfml-system sfml-network sfml-graphics sfml-window)