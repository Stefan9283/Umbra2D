cmake_minimum_required (VERSION 3.0)
project (lua CXX)


file(GLOB HEADERS
        include/lua.h
        include/lua.hpp
        include/luaconf.h
        include/lualib.h
        )
file(GLOB SOURCE 
        src/lua.c
        src/lstate.c
        src/lapi.c
        src/ltm.c
        src/lgc.c
        src/lvm.c
        src/lobject.c
        src/ldo.c
        src/lfunc.c
        src/ltable.c
        src/lstring.c
        src/lmem.c
        src/llex.c
        src/ldump.c
        src/lundump.c
        src/ldebug.c
        src/lzio.c
        src/lcode.c
        src/lopcodes.c
        src/lparser.c
        src/lctype.c
        src/liolib.c
        src/ltablib.c
        src/ldblib.c
        src/lauxlib.c
        src/loadlib.c
        src/lutf8lib.c
        src/lmathlib.c
        src/lbaselib.c
        src/lstrlib.c
        src/lcorolib.c
        src/loslib.c
)
add_library (lua
        ${HEADERS}
        ${SOURCE}
        )

target_include_directories(lua PUBLIC
        include
        )
