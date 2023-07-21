# Install script for directory: E:/learn/opengl/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/Assimp")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/learn/opengl/build/assimp/code/Debug/assimp-vc142-mtd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/learn/opengl/build/assimp/code/Release/assimp-vc142-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/learn/opengl/build/assimp/code/MinSizeRel/assimp-vc142-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/learn/opengl/build/assimp/code/RelWithDebInfo/assimp-vc142-mt.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/learn/opengl/build/assimp/code/Debug/assimp-vc142-mtd.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/learn/opengl/build/assimp/code/Release/assimp-vc142-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/learn/opengl/build/assimp/code/MinSizeRel/assimp-vc142-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/learn/opengl/build/assimp/code/RelWithDebInfo/assimp-vc142-mt.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "E:/learn/opengl/assimp/code/../include/assimp/anim.h"
    "E:/learn/opengl/assimp/code/../include/assimp/aabb.h"
    "E:/learn/opengl/assimp/code/../include/assimp/ai_assert.h"
    "E:/learn/opengl/assimp/code/../include/assimp/camera.h"
    "E:/learn/opengl/assimp/code/../include/assimp/color4.h"
    "E:/learn/opengl/assimp/code/../include/assimp/color4.inl"
    "E:/learn/opengl/build/assimp/code/../include/assimp/config.h"
    "E:/learn/opengl/assimp/code/../include/assimp/defs.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Defines.h"
    "E:/learn/opengl/assimp/code/../include/assimp/cfileio.h"
    "E:/learn/opengl/assimp/code/../include/assimp/light.h"
    "E:/learn/opengl/assimp/code/../include/assimp/material.h"
    "E:/learn/opengl/assimp/code/../include/assimp/material.inl"
    "E:/learn/opengl/assimp/code/../include/assimp/matrix3x3.h"
    "E:/learn/opengl/assimp/code/../include/assimp/matrix3x3.inl"
    "E:/learn/opengl/assimp/code/../include/assimp/matrix4x4.h"
    "E:/learn/opengl/assimp/code/../include/assimp/matrix4x4.inl"
    "E:/learn/opengl/assimp/code/../include/assimp/mesh.h"
    "E:/learn/opengl/assimp/code/../include/assimp/pbrmaterial.h"
    "E:/learn/opengl/assimp/code/../include/assimp/postprocess.h"
    "E:/learn/opengl/assimp/code/../include/assimp/quaternion.h"
    "E:/learn/opengl/assimp/code/../include/assimp/quaternion.inl"
    "E:/learn/opengl/assimp/code/../include/assimp/scene.h"
    "E:/learn/opengl/assimp/code/../include/assimp/metadata.h"
    "E:/learn/opengl/assimp/code/../include/assimp/texture.h"
    "E:/learn/opengl/assimp/code/../include/assimp/types.h"
    "E:/learn/opengl/assimp/code/../include/assimp/vector2.h"
    "E:/learn/opengl/assimp/code/../include/assimp/vector2.inl"
    "E:/learn/opengl/assimp/code/../include/assimp/vector3.h"
    "E:/learn/opengl/assimp/code/../include/assimp/vector3.inl"
    "E:/learn/opengl/assimp/code/../include/assimp/version.h"
    "E:/learn/opengl/assimp/code/../include/assimp/cimport.h"
    "E:/learn/opengl/assimp/code/../include/assimp/importerdesc.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Importer.hpp"
    "E:/learn/opengl/assimp/code/../include/assimp/DefaultLogger.hpp"
    "E:/learn/opengl/assimp/code/../include/assimp/ProgressHandler.hpp"
    "E:/learn/opengl/assimp/code/../include/assimp/IOStream.hpp"
    "E:/learn/opengl/assimp/code/../include/assimp/IOSystem.hpp"
    "E:/learn/opengl/assimp/code/../include/assimp/Logger.hpp"
    "E:/learn/opengl/assimp/code/../include/assimp/LogStream.hpp"
    "E:/learn/opengl/assimp/code/../include/assimp/NullLogger.hpp"
    "E:/learn/opengl/assimp/code/../include/assimp/cexport.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Exporter.hpp"
    "E:/learn/opengl/assimp/code/../include/assimp/DefaultIOStream.h"
    "E:/learn/opengl/assimp/code/../include/assimp/DefaultIOSystem.h"
    "E:/learn/opengl/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "E:/learn/opengl/assimp/code/../include/assimp/SceneCombiner.h"
    "E:/learn/opengl/assimp/code/../include/assimp/fast_atof.h"
    "E:/learn/opengl/assimp/code/../include/assimp/qnan.h"
    "E:/learn/opengl/assimp/code/../include/assimp/BaseImporter.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Hash.h"
    "E:/learn/opengl/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "E:/learn/opengl/assimp/code/../include/assimp/ParsingUtils.h"
    "E:/learn/opengl/assimp/code/../include/assimp/StreamReader.h"
    "E:/learn/opengl/assimp/code/../include/assimp/StreamWriter.h"
    "E:/learn/opengl/assimp/code/../include/assimp/StringComparison.h"
    "E:/learn/opengl/assimp/code/../include/assimp/StringUtils.h"
    "E:/learn/opengl/assimp/code/../include/assimp/SGSpatialSort.h"
    "E:/learn/opengl/assimp/code/../include/assimp/GenericProperty.h"
    "E:/learn/opengl/assimp/code/../include/assimp/SpatialSort.h"
    "E:/learn/opengl/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "E:/learn/opengl/assimp/code/../include/assimp/SmoothingGroups.h"
    "E:/learn/opengl/assimp/code/../include/assimp/SmoothingGroups.inl"
    "E:/learn/opengl/assimp/code/../include/assimp/StandardShapes.h"
    "E:/learn/opengl/assimp/code/../include/assimp/RemoveComments.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Subdivision.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Vertex.h"
    "E:/learn/opengl/assimp/code/../include/assimp/LineSplitter.h"
    "E:/learn/opengl/assimp/code/../include/assimp/TinyFormatter.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Profiler.h"
    "E:/learn/opengl/assimp/code/../include/assimp/LogAux.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Bitmap.h"
    "E:/learn/opengl/assimp/code/../include/assimp/XMLTools.h"
    "E:/learn/opengl/assimp/code/../include/assimp/IOStreamBuffer.h"
    "E:/learn/opengl/assimp/code/../include/assimp/CreateAnimMesh.h"
    "E:/learn/opengl/assimp/code/../include/assimp/irrXMLWrapper.h"
    "E:/learn/opengl/assimp/code/../include/assimp/BlobIOSystem.h"
    "E:/learn/opengl/assimp/code/../include/assimp/MathFunctions.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Macros.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Exceptional.h"
    "E:/learn/opengl/assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "E:/learn/opengl/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Compiler/poppack1.h"
    "E:/learn/opengl/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "E:/learn/opengl/build/assimp/code/Debug/assimp-vc142-mtd.pdb")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "E:/learn/opengl/build/assimp/code/RelWithDebInfo/assimp-vc142-mt.pdb")
  endif()
endif()

