#include "lua_class.h"

static int _function_index = 0;
static const char* _function_table = "_FUNCTION_TABLE";


void openRegistryTable( lua_State* lstate)
{
	lua_pushstring( lstate , _function_table );
	lua_newtable( lstate );
	lua_rawset( lstate, LUA_REGISTRYINDEX);
}

int luaToRegistryIndex( lua_State* lstate , int funcIndex)
{
	if( ! lua_isfunction( lstate ,funcIndex)){
		return -1;
	}


	lua_pushstring( lstate,_function_table);
	lua_rawget( lstate, LUA_REGISTRYINDEX);
	
	lua_pushinteger( lstate,_function_index);
	lua_pushvalue( lstate , funcIndex);
	lua_rawset( lstate, -3);

	return _function_index ++ ;
}

int registryIndexToLua( lua_State* lstate , int rid)
{
	lua_pushstring( lstate, _function_table);
	lua_rawget( lstate , LUA_REGISTRYINDEX );

	lua_pushinteger( lstate , rid);
	lua_rawget( lstate , -2);

	if ( lua_isfunction( lstate, -1)){
		return LC_OK;
	}
	return LC_ERRFUNC;
}

