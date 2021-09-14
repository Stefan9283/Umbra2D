cmake_minimum_required(VERSION 3.10)
set(CMAKE_MIN_REQ_VERSION "3.10")
# set the project name
project("Umbra2D")

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

add_subdirectory(Dependencies/Vendor/glfw)
add_subdirectory(Dependencies/Vendor/glad)
add_subdirectory(Dependencies/Vendor/ChaiScript)
add_subdirectory(Dependencies/Vendor/freetype)

option(ENABLE_EXTERNAL_LIBS ON)
option(ENABLE_MPEG ON)

add_subdirectory(Dependencies/Vendor/libsndfile)
add_subdirectory(Dependencies/Vendor/portaudio)
add_subdirectory(Dependencies/Vendor/entt)

message(STATUS " .............. Setting fancy compilation flags ...............")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /W4 /MDd /std:c++latest")
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	set (CMAKE_CXX_STANDARD 20)
	set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")

else()
	if(UNIX)
		message("Linux")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lfreetype -Wall -Wextra -Wpedantic -std=c++20")
		set(GLAD_LIBRARIES g dl GL GLU glfw X11 Xrandr pthread Xi Xinerama Xcursor )
	endif()
endif()

message(STATUS " ............. Grabbing external libs source code .............")

file(GLOB VENDORS_SOURCES 
		Dependencies/Vendor/glad/src/glad.c
		Dependencies/Vendor/imgui/backends/imgui_impl_opengl3.cpp 
		Dependencies/Vendor/imgui/backends/imgui_impl_glfw.cpp 
		Dependencies/Vendor/imgui/*.cpp
		Dependencies/Vendor/imgui/misc/cpp/*.cpp
		Dependencies/Vendor/imgui-node-editor/*.cpp)

message(STATUS " ............... Grabbing all your source code ................")

file(GLOB_RECURSE PROJECT_SOURCES Dependencies/Source/*.cpp Dependencies/Source/*.c)
file(GLOB_RECURSE PROJECT_HEADERS Dependencies/Include/*.h Dependencies/Include/*.hpp)
file(GLOB_RECURSE PROJECT_SHADERS Dependencies/Shader/*.glsl)

source_group(TREE 
	${CMAKE_CURRENT_SOURCE_DIR}/Dependencies FILES 
		${VENDORS_SOURCES}
		${PROJECT_SOURCES}
		${PROJECT_HEADERS}
		${PROJECT_SHADERS})

message(STATUS " ................. Setting the include paths ..................")

include_directories(
		Dependencies/Include
		Dependencies/Vendor/glm
		Dependencies/Vendor/stb
		Dependencies/Vendor/imgui
		Dependencies/Vendor/imgui/backends
		Dependencies/Vendor/imgui-node-editor
		Dependencies/Vendor/glfw/include
		Dependencies/Vendor/glad/include
		Dependencies/Vendor/freetype/include
		Dependencies/Vendor/ChaiScript/include
		Dependencies/Vendor/portaudio/include
		Dependencies/Vendor/entt/single_include
)

add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

add_executable(				
			${PROJECT_NAME} 
			${VENDORS_SOURCES} 
			${PROJECT_SOURCES} 
			${PROJECT_HEADERS}
			${PROJECT_SHADERS}
			${APP_ICON_RESOURCE_WINDOWS})

message(STATUS " ..................... Linking everything .....................")

target_link_libraries(
	${PROJECT_NAME}
		${GLFW_LIBRARIES} 
		${GLAD_LIBRARIES}
		sndfile
		PortAudio
		freetype
		EnTT
		glfw)

set_target_properties(${PROJECT_NAME} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
		VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# message(STATUS " $$$$$$$$$$$$$$$$ Cash Money! Everything seems in order $$$$$$$$$$$$$$$$$ " )
message(STATUS " ??? Everything seems in order... Is this really happening? ???" )
