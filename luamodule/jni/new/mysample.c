#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdlib.h>
#include <string.h>

static int lxc_hello(lua_State *L) {
    const char *name = luaL_checkstring(L, 1);
    lua_pushfstring(L, "Hello, %s! Welcome to LXCLuaCore!", name);
    return 1;
}

static int lxc_add(lua_State *L) {
    int a = luaL_checkinteger(L, 1);
    int b = luaL_checkinteger(L, 2);
    lua_pushinteger(L, a + b);
    return 1;
}

static int lxc_mul(lua_State *L) {
    int a = luaL_checkinteger(L, 1);
    int b = luaL_checkinteger(L, 2);
    lua_pushinteger(L, a * b);
    return 1;
}

static int lxc_version(lua_State *L) {
    lua_pushstring(L, "1.0.0");
    return 1;
}

static const luaL_Reg lxc_functions[] = {
    {"hello",     lxc_hello},
    {"add",       lxc_add},
    {"mul",       lxc_mul},
    {"version",   lxc_version},
    {NULL, NULL}
};
__attribute__((visibility("default")))
int luaopen_mysample(lua_State *L) {

    luaL_newlib(L, lxc_functions);

    lua_pushstring(L, "_VERSION");
    lua_pushstring(L, "LXCSample 1.0.0");
    lua_settable(L, -3);
    
    lua_pushstring(L, "_AUTHOR");
    lua_pushstring(L, "LXCLuaCore Team");
    lua_settable(L, -3);
    
    return 1;
}
