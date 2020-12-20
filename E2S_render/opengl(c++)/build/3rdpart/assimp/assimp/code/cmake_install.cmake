# Install script for directory: G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/VidarRender")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "G:/Vidar/VidarStreamSim/VidarSimOpenGL/build/lib/Debug/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "G:/Vidar/VidarStreamSim/VidarSimOpenGL/build/lib/Release/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "G:/Vidar/VidarStreamSim/VidarSimOpenGL/build/lib/MinSizeRel/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "G:/Vidar/VidarStreamSim/VidarSimOpenGL/build/lib/RelWithDebInfo/assimp-vc140-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "G:/Vidar/VidarStreamSim/VidarSimOpenGL/Debug/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "G:/Vidar/VidarStreamSim/VidarSimOpenGL/Release/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "G:/Vidar/VidarStreamSim/VidarSimOpenGL/build/bin/MinSizeRel/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "G:/Vidar/VidarStreamSim/VidarSimOpenGL/build/bin/RelWithDebInfo/assimp-vc140-mt.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/anim.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/ai_assert.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/camera.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/color4.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/color4.inl"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/build/3rdpart/assimp/assimp/code/../include/assimp/config.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/defs.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Defines.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/cfileio.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/light.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/material.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/material.inl"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/matrix3x3.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/matrix3x3.inl"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/matrix4x4.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/matrix4x4.inl"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/mesh.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/pbrmaterial.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/postprocess.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/quaternion.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/quaternion.inl"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/scene.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/metadata.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/texture.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/types.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/vector2.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/vector2.inl"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/vector3.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/vector3.inl"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/version.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/cimport.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/importerdesc.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Importer.hpp"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/DefaultLogger.hpp"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/ProgressHandler.hpp"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/IOStream.hpp"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/IOSystem.hpp"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Logger.hpp"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/LogStream.hpp"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/NullLogger.hpp"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/cexport.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Exporter.hpp"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/DefaultIOStream.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/DefaultIOSystem.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/SceneCombiner.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/fast_atof.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/qnan.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/BaseImporter.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Hash.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/ParsingUtils.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/StreamReader.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/StreamWriter.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/StringComparison.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/StringUtils.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/SGSpatialSort.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/GenericProperty.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/SpatialSort.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/SmoothingGroups.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/SmoothingGroups.inl"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/StandardShapes.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/RemoveComments.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Subdivision.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Vertex.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/LineSplitter.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/TinyFormatter.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Profiler.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/LogAux.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Bitmap.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/XMLTools.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/IOStreamBuffer.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/CreateAnimMesh.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/irrXMLWrapper.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/BlobIOSystem.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/MathFunctions.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Macros.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Exceptional.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Compiler/poppack1.h"
    "G:/Vidar/VidarStreamSim/VidarSimOpenGL/3rdpart/assimp/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "G:/Vidar/VidarStreamSim/VidarSimOpenGL/build/3rdpart/assimp/assimp/code/Debug/assimp-vc140-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "G:/Vidar/VidarStreamSim/VidarSimOpenGL/build/3rdpart/assimp/assimp/code/RelWithDebInfo/assimp-vc140-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

