cmake_minimum_required (VERSION 2.8)
project(GameMap)

set(CMAKE_CXX_STANDARD 20)

## [discover_ogre]
# specify which version and components you need
find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)

# copy resource.cfg next to our binaries where OGRE looks for it
file(COPY ${OGRE_CONFIG_DIR}/resources.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Map Map.cpp)

target_link_libraries(Map ${OGRE_LIBRARIES})
