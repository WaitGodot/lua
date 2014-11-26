#include <stdio.h>
#include <lua.hpp>
#include <string.h>
#include "macroConfig.h"
#include "lua_class.h"
#include "LuaStack.h"
#include "lua_imp.h"

#define lua_open luaL_newstate


int main( int argc , char** argv)
{
	if(argc != 2){
		LOG_ERROR("usage : ./exe xx.lua");
		return 1;
	}

	lua_State* lstate = LuaStack::getInstance()->getState();
	luaopen_base(lstate);
	luaopen_table(lstate);
	luaopen_io(lstate);
	luaopen_string(lstate);
	luaopen_math(lstate);
	LOG("%d\nbegin lua test\n",lua_gettop(lstate));
	
	openRegistryTable( lstate );
	register_to_lua( lstate );
	if (luaL_loadfile(lstate,argv[1])|| lua_pcall(lstate,0,0,0)){
		LOG_ERROR("cannot run the lua script : %s",lua_tostring(lstate,-1));
	}
	

	LuaStack::getInstance()->purgeLuaStack();
	return 0;
}
