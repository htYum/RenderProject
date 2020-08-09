cmake_minimum_required(VERSION 3.5)

project(RenderProject LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(RenderProject SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Math/detail/Matrix4x4.h
    Math/detail/Matrix4x4.cpp
    Math/detail/vec2.h
    Math/detail/vec2.cpp
    Math/detail/vec3.h
    Math/detail/vec3.cpp
    Math/detail/vec4.h
    Math/detail/vec4.cpp
    Math/MyMath.h
    RenderLoop/framebuffer.h
    RenderLoop/framebuffer.cpp
    RenderLoop/vertex.h
    RenderLoop/vertex.cpp
    RenderLoop/v2f.h
    RenderLoop/v2f.cpp
    RenderLoop/mesh.h
    RenderLoop/mesh.cpp
    Shader/baseshader.h
    Shader/baseshader.cpp
    Shader/myshader.h
    Shader/myshader.cpp
    RenderLoop/renderloop.h
    RenderLoop/renderloop.cpp
    RenderLoop/pipeline.h
    RenderLoop/pipeline.cpp
    RenderLoop/Texture2D.h
    RenderLoop/Texture2D.cpp
    Control/Camera.h
    Control/Camera.cpp
    Math/Quaternion.h
    Math/Quaternion.cpp
    Math/detail/Functions.h
    Math/detail/Functions.cpp
  )
else()
  add_executable(RenderProject
      main.cpp
      mainwindow.cpp
      mainwindow.h
      mainwindow.ui
      Math/detail/Matrix4x4.h
      Math/detail/Matrix4x4.cpp
      Math/detail/vec2.h
      Math/detail/vec2.cpp
      Math/detail/vec3.h
      Math/detail/vec3.cpp
      Math/detail/vec4.h
      Math/detail/vec4.cpp
      Math/MyMath.h
      RenderLoop/framebuffer.h
      RenderLoop/framebuffer.cpp
      RenderLoop/vertex.h
      RenderLoop/vertex.cpp
      RenderLoop/v2f.h
      RenderLoop/v2f.cpp
      RenderLoop/mesh.h
      RenderLoop/mesh.cpp
      Shader/baseshader.h
      Shader/baseshader.cpp
      Shader/myshader.h
      Shader/myshader.cpp
      RenderLoop/renderloop.h
      RenderLoop/renderloop.cpp
      RenderLoop/pipeline.h
      RenderLoop/pipeline.cpp
      RenderLoop/Texture2D.h
      RenderLoop/Texture2D.cpp
      Control/Camera.h
      Control/Camera.cpp
      Math/Quaternion.h
      Math/Quaternion.cpp
      Math/detail/Functions.h
      Math/detail/Functions.cpp
  )
endif()

target_link_libraries(RenderProject PRIVATE Qt5::Widgets)
