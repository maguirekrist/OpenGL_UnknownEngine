cmake_minimum_required(VERSION 3.22)
project(AlphaEngineCMake)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#option(TRACY_ENABLE "" ON)
#option(TRACY_ON_DEMAND "" ON)

#add_subdirectory(src/tracy)
#
#include_directories(
#        ${PROJECT_SOURCE_DIR}/src
##        ${PROJECT_SOURCE_DIR}/src/tracy
#    )

#
#file(GLOB SOURCES
#        src/*.cpp
#        src/*.hpp
#        src/renderers/*.cpp
#        src/renderers/*.hpp
#        src/utils/*.cpp
#        src/utils/*.hpp
#        src/generation/*.cpp
#        src/generation/*.hpp
#        src/infrastructure/*.cpp
#        src/infrastructure/*.hpp
#        src/renderers/*.cpp
#        src/renderers/*.hpp
#        src/scene/*.cpp
#        src/scene/*.hpp
##        src/tracy/TracyClient.cpp
#        )

set(source_files
        src/main.cpp
        src/renderers/FontRenderer.cpp
        src/renderers/EntityRenderer.cpp
        src/renderers/WorldRenderer.cpp
        src/generation/INoiseGenerator.cpp
        src/generation/NoiseGenerator.cpp
        src/graphics/ArrayTexture.cpp
        src/graphics/Shader.cpp
        src/graphics/Texture.cpp
        src/infrastructure/ResourceManager.cpp
        src/scene/Window.cpp
        src/scene/World.cpp
        src/scene/Camera.cpp
        src/scene/Light.cpp
        src/scene/Tile.cpp
        src/utils/Random.cpp
        )

set(header_files
        src/renderers/FontRenderer.h
        src/renderers/EntityRenderer.h
        src/renderers/WorldRenderer.h
        src/generation/INoiseGenerator.h
        src/generation/NoiseGenerator.h
        src/scene/Window.h
        src/scene/Camera.h
        src/scene/Light.h
        src/scene/World.h
        src/scene/Tile.h
        src/graphics/Shader.h
        src/graphics/ArrayTexture.h
        src/graphics/Texture.h
        src/infrastructure/ResourceManager.h
        src/utils/SpatialMap.hpp
        src/utils/Types.hpp
        src/utils/Random.h
        src/utils/TileType.h
        src/utils/Timer.h)

add_executable(${PROJECT_NAME} ${source_files} ${header_files})

#target_link_libraries(AlphaEngineCMake PRIVATE OpenGL::GL)
target_link_libraries(AlphaEngineCMake ${CONAN_LIBS})