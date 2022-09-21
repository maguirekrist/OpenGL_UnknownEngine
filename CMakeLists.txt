cmake_minimum_required(VERSION 3.21)
project(AlphaEngineCMake)


set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
include_directories(
        ${PROJECT_SOURCE_DIR}/src
    )
file(GLOB SOURCES
        src/*.cpp
        src/*.hpp
        )


add_executable(AlphaEngineCMake ${SOURCES} src/Renderers/SpriteRenderer.cpp src/Renderers/SpriteRenderer.h src/Tile.cpp src/Tile.h src/World.cpp src/World.h src/Renderers/WorldRenderer.cpp src/Renderers/WorldRenderer.h src/Renderers/QuadRenderer.cpp src/Renderers/QuadRenderer.h src/SpatialMap.hpp)
target_include_directories(AlphaEngineCMake PRIVATE ${STB_INCLUDE_DIRS})
target_link_libraries(AlphaEngineCMake PRIVATE OpenGL::GL)
target_link_libraries(AlphaEngineCMake PRIVATE glm::glm)
target_link_libraries(AlphaEngineCMake PRIVATE GLEW::GLEW)
target_link_libraries(AlphaEngineCMake PRIVATE glfw)