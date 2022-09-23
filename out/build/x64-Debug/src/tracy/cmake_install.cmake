# Install script for directory: C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/magui/dev/OpenGL_UnknownEngine/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/magui/dev/OpenGL_UnknownEngine/out/build/x64-Debug/src/tracy/TracyClient.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/TracyC.h"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/Tracy.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/TracyD3D11.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/TracyD3D12.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/TracyLua.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/TracyOpenCL.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/TracyOpenGL.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/TracyVulkan.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/client" TYPE FILE FILES
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/tracy_concurrentqueue.h"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/tracy_rpmalloc.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/tracy_SPSCQueue.h"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyArmCpuTable.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyCallstack.h"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyCallstack.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyDebug.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyDxt1.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyFastVector.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyLock.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyProfiler.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyRingBuffer.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyScoped.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyStringHelpers.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracySysTime.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracySysTrace.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/client/TracyThread.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/common" TYPE FILE FILES
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/tracy_lz4.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/tracy_lz4hc.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyAlign.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyAlign.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyAlloc.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyApi.h"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyColor.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyForceInline.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyMutex.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyProtocol.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyQueue.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracySocket.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyStackFrames.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracySystem.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyUwp.hpp"
    "C:/Users/magui/dev/OpenGL_UnknownEngine/src/tracy/common/TracyYield.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/Tracy/TracyConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/Tracy/TracyConfig.cmake"
         "C:/Users/magui/dev/OpenGL_UnknownEngine/out/build/x64-Debug/src/tracy/CMakeFiles/Export/share/Tracy/TracyConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/Tracy/TracyConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/Tracy/TracyConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/Tracy" TYPE FILE FILES "C:/Users/magui/dev/OpenGL_UnknownEngine/out/build/x64-Debug/src/tracy/CMakeFiles/Export/share/Tracy/TracyConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/Tracy" TYPE FILE FILES "C:/Users/magui/dev/OpenGL_UnknownEngine/out/build/x64-Debug/src/tracy/CMakeFiles/Export/share/Tracy/TracyConfig-debug.cmake")
  endif()
endif()

