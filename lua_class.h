#ifndef __LUA_CLASS_H__
#define __LUA_CLASS_H__

#include <lua.hpp>

#define LC_OK		0
#define LC_ERRFUNC	1

#ifdef __cplusplus
extern "C" {
#endif

void openRegistryTable( lua_State* lstate);
int  luaToRegistryIndex	( lua_State* lstate , int funcIndex);
int  registryIndexToLua	( lua_State* lstate , int rid);

#ifdef __cplusplus
}
#endif

#endif
