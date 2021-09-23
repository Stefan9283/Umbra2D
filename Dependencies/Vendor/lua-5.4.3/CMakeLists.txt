cmake_minimum_required (VERSION 3.0)
project (lua CXX)


file(GLOB HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/lua.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/lua.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/luaconf.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/lualib.h
        )
file(GLOB SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/lua.c)
add_library (lua
        ${HEADERS}
        ${SOURCE}
        )

target_include_directories(lua PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
