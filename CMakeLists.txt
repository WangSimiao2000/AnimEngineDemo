cmake_minimum_required(VERSION 3.16)

project(AnimEngineDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Dependencies (provided as git submodules under external/) ----

# raylib: used only as a visualization / verification tool for the demo.
# Build just the library, skip its bundled examples/games to keep builds fast.
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
add_subdirectory(external/raylib)

# AnimEngine: the animation library under test.
add_subdirectory(external/AnimEngine)

# ---- Demo executable ----
add_executable(demo src/main.cpp)
target_link_libraries(demo
    PRIVATE
        AnimEngine::animengine
        raylib
)
