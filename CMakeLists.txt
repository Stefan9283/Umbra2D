cmake_minimum_required(VERSION 3.10)
set(CMAKE_MIN_REQ_VERSION "3.10")
# set the project name
project("Umbra2D")

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Dependencies/Vendor/glfw)
add_subdirectory(Dependencies/Vendor/glad)

set(freetype-gl_BUILD_APIDOC OFF)
# add_subdirectory(Dependencies/Vendor/freetype) #### ADD LATER


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /MDd /std:c++17")
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	set (CMAKE_CXX_STANDARD 20)
else()
	if(UNIX)
		message("Linux")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lfreetype -Wall -Wextra -Wpedantic -std=c++17")
		set(GLAD_LIBRARIES g dl GL GLU glfw X11 Xrandr pthread Xi Xinerama Xcursor )
	endif()
endif()

file(GLOB VENDORS_SOURCES 
		Dependencies/Vendor/glad/src/glad.c
		Dependencies/Vendor/imgui/backends/imgui_impl_opengl3.cpp 
		Dependencies/Vendor/imgui/backends/imgui_impl_glfw.cpp 
		Dependencies/Vendor/imgui/*.cpp
		Dependencies/Vendor/imgui/misc/cpp/*.cpp )
source_group("Vendor Source"            FILES ${VENDORS_SOURCES})

file(GLOB PROJECT_SOURCES 
		Dependencies/Source/*.cpp 
		Dependencies/Source/*.c )
source_group("SOURCE"            FILES ${PROJECT_SOURCES})

file(GLOB  PROJECT_HEADERS
		Dependencies/Include/* )
source_group("INCLUDE"            FILES ${PROJECT_HEADERS})

file(GLOB  PROJECT_SHADERS
		Dependencies/Shader/* )
source_group("SHADERS"            FILES ${PROJECT_SHADERS})

message(STATUS "SHADERS SHADERS SHADERS SHADERS SHADERS SHADERS " ${PROJECT_SHADERS})



include_directories(
					Dependencies/Include
					Dependencies/Vendor/glm
					Dependencies/Vendor/stb
					Dependencies/Vendor/imgui
					Dependencies/Vendor/imgui/backends
					Dependencies/Vendor/glfw/include
					Dependencies/Vendor/glad/include
					#Dependencies/Vendor/freetype/include
					)

add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

add_executable(				${PROJECT_NAME} 
							${VENDORS_SOURCES} 
							${PROJECT_SOURCES} 
							${PROJECT_HEADERS}
							)

target_link_libraries(${PROJECT_NAME}
								${GLFW_LIBRARIES} 
								${GLAD_LIBRARIES} 
								#freetype
								glfw
								)

set_target_properties(${PROJECT_NAME} PROPERTIES 
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
		VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

message(STATUS " $$$$$$$$$$$$$$$$ Cash Money! Everything seems in order $$$$$$$$$$$$$$$$$ " )
