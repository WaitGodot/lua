#include <stdio.h>
#include <lua.hpp>
#include <string.h>
#include "macroConfig.h"
#include "lua_class.h"
#include "LuaStack.h"
#include "lua_imp.h"

#define lua_open luaL_newstate

static void lua_global_func( lua_State* lstate )
{
	LOG("AAAA %d",lua_gettop( lstate ));
	lua_getglobal( lstate , "ftest");
	if ( lua_isfunction(  lstate, -1))
	{
		lua_pushnumber( lstate ,23);
		lua_pushnumber( lstate ,30);
		if (lua_pcall( lstate ,2,1,0)){
			LOG_ERROR("lua global function test error %s",lua_tostring( lstate,-1));
			lua_pop( lstate , 1);
		}
		LOG("ftest result %d -> %d",(int)lua_gettop( lstate),(int)lua_tonumber( lstate,-1));
	}
}



int main(void)
{
	lua_State* lstate = LuaStack::getInstance()->getState();
	luaopen_base(lstate);
	luaopen_table(lstate);
	luaopen_io(lstate);
	luaopen_string(lstate);
	luaopen_math(lstate);
	LOG("%d\nbegin lua test\n",lua_gettop(lstate));

	lua_newtable(lstate);
	lua_pushstring(lstate,"width");
	lua_pushnumber(lstate,500);
	lua_settable(lstate,-3);
	lua_pushstring(lstate,"height");
	lua_pushnumber(lstate,600);
	lua_settable(lstate,-3);
	lua_setglobal(lstate,"ctable");

	if (luaL_loadfile(lstate,"lua_test.lua")|| lua_pcall(lstate,0,0,0)){
		LOG_ERROR("cannot run the lua script : %s",lua_tostring(lstate,-1));
	}
	//
	LOG("%d",lua_gettop(lstate));
	lua_getglobal(lstate,"table");
	
	lua_pushstring(lstate,"width");
	lua_gettable(lstate,-2);
	LOG("width = %d",(int)lua_tonumber(lstate,-1));
	lua_pop(lstate,1);

	lua_pushstring(lstate,"height");
	lua_gettable(lstate,-2);
	LOG("height = %d",(int)lua_tonumber(lstate,-1));
	lua_pop(lstate,1);

	//
	lua_pushstring(lstate,"register");
	lua_pushnumber(lstate,9876);
	lua_settable(lstate,LUA_REGISTRYINDEX);

	lua_pushstring(lstate,"register");
	lua_gettable(lstate,LUA_REGISTRYINDEX);
	LOG("lua register table rigister : %d",(int)lua_tonumber(lstate,-1))

	int ref = luaL_ref(lstate , LUA_REGISTRYINDEX);
	lua_pushstring( lstate , "ref test" );
	lua_rawseti(lstate , LUA_REGISTRYINDEX,ref);

	lua_rawgeti( lstate,LUA_REGISTRYINDEX,ref);
	LOG("lua ref: %s",lua_tostring( lstate,-1));

	
	lua_global_func( lstate);
	register_to_lua( lstate );

	LuaStack::getInstance()->purgeLuaStack();
	return 0;
}
