cmake_minimum_required(VERSION 3.0)

project(VidarRender)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${VidarRender_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${VidarRender_SOURCE_DIR}/Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${VidarRender_SOURCE_DIR}/Release")

include(macros)
include(modules/sanitizers_support)
include(modules/clang_tidy_support)
include(modules/add_ide_support)

detect_platform()
print_info()
set_output_paths()

add_subdirectory_ex(3rdpart)


include_directories(src/camera/
                    src/lighting/
                    src/mesh/
                    src/renderer/
                    src/resources/
                    src/spike/
                    api/assimp/include/
                    api/glad/include/
                    api/glfw/include/
                    api/glm/
                    api/stb/
					api/imgui/)

file(GLOB API_SOURCES api/glad/src/glad.c
					  api/imgui/*.cpp)

file(GLOB PROJECT_HEADERS src/camera/*.h
                          src/lighting/*.h
                          src/mesh/*.h
                          src/renderer/*.h
                          src/resources/*.h
                          src/spike/*.h)

file(GLOB PROJECT_SOURCES src/camera/*.cpp
                          src/lighting/*.cpp
                          src/mesh/*.cpp
                          src/renderer/*.cpp
                          src/resources/*.cpp
                          src/spike/*.cpp)

file(GLOB PROJECT_SHADERS resources/shaders/*.glsl
                          resources/shaders/*.frag
                          resources/shaders/*.vert
                          resources/shaders/lighting/*.glsl
                          resources/shaders/lighting/*.frag
                          resources/shaders/lighting/*.vert
                          resources/shaders/lighting/ibl/*.glsl
                          resources/shaders/lighting/ibl/*.frag
                          resources/shaders/lighting/ibl/*.vert
                          resources/shaders/postprocess/*.glsl
                          resources/shaders/postprocess/*.frag
                          resources/shaders/postprocess/*.vert)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("API" FILES ${API_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${API_SOURCES}                        
                               )

#add_executable(VidarStreamFromImages ${PROJECT_SOURCES} ${PROJECT_HEADERS}
#                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
#                               ${API_SOURCES}
#                               tools/test.cpp
#                               )

target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_definitions(
	-DGLFW_INCLUDE_NONE
	-DWINDOWS
    -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
    -DASSET_PATH=\"${PROJECT_SOURCE_DIR}/resources\"
    )
    
link_directories(${VidarRender_SOURCE_DIR})