cmake_minimum_required(VERSION 3.19)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows-static")

cmake_policy(SET CMP0091 NEW)

# --- CLIENT ---


project(MineSweeperClient)

add_executable(MineSweeperClient src/Client/main.cpp src/Common/GameState.cpp src/Common/GameState.h src/Common/Cell.h src/Client/MainWindow.cpp src/Client/MainWindow.h src/Client/CellRenderer.cpp src/Client/CellRenderer.h src/Client/UdpClient.cpp src/Client/UdpClient.h)

set_property(TARGET MineSweeperClient PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_options(MineSweeperClient PRIVATE /Zc:__cplusplus)
target_compile_features(MineSweeperClient PRIVATE cxx_std_20)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(MineSweeperClient PRIVATE
		sfml-system sfml-network sfml-graphics sfml-window
		nlohmann_json nlohmann_json::nlohmann_json)

add_custom_command(TARGET MineSweeperClient PRE_BUILD
		COMMAND robocopy ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR}/resources /E /NS /NC /NFL /NDL /NP /NJH /NJS  || cmd /c "exit /b 0")


# --- SERVER ---


project(MineSweeperServer)

add_executable(MineSweeperServer src/Server/main.cpp src/Common/GameState.cpp src/Common/GameState.h src/Common/Cell.h src/Server/UdpServer.cpp src/Server/UdpServer.h)

set_property(TARGET MineSweeperServer PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_options(MineSweeperServer PRIVATE /Zc:__cplusplus)
target_compile_features(MineSweeperServer PRIVATE cxx_std_20)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(MineSweeperServer PRIVATE
		sfml-system sfml-network sfml-graphics sfml-window
		nlohmann_json nlohmann_json::nlohmann_json)