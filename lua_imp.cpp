#include "lua_imp.h"
#include "ClassToLua.h"
#include "lua_class.h"
#include "macroConfig.h"

static const char* class_name = "ClassToLua";

static void* checkudata( lua_State* lstate)
{
	void* rt = luaL_checkudata( lstate,1,class_name);
	return rt;
}

static int lua_ClassToLua_new( lua_State* lstate)
{
	//ClassToLua* rt = (ClassToLua*)lua_newuserdata( lstate , sizeof(ClassToLua));
	ClassToLua* rt = new ClassToLua();
	lua_pushlightuserdata( lstate , rt);
	luaL_setmetatable( lstate,class_name);

	//rt->registerScriptHandler(-1);
	//rt->setMember(123);
	return 1;
}

static int lua_ClassToLua_print( lua_State* lstate)
{
	ClassToLua* rt = (ClassToLua*)checkudata( lstate );
	if(!rt){
		return 0;
	}
	rt->print();
	return 0;
}

static int lua_ClassToLua_getMember( lua_State* lstate)
{
	ClassToLua* rt = (ClassToLua*)checkudata( lstate);
	if(!rt){
		return 0;
	}
	lua_pushinteger( lstate,rt->getMember());
	return 1;
}

static int lua_ClassToLua_setMember( lua_State* lstate)
{
	ClassToLua* rt = (ClassToLua*)checkudata( lstate);
	if(!rt){
		return 0;
	}
	int member = (int)lua_tointeger( lstate,2);
	rt->setMember(member);
	return 0;
}

static int lua_ClassToLua_registerScriptHandler( lua_State* lstate)
{
	ClassToLua* rt = (ClassToLua*)checkudata( lstate);
	if(!rt){
		return 0;
	}
	int handler = luaToRegistryIndex( lstate,2);
	rt->registerScriptHandler(handler);
	return 0;
}


static const char* lua_func_name[5] = {
	"new",
	"print",
	"getMember",
	"setMember",
	"registerScriptHandler"
};

static const lua_CFunction cfunction[5] = {
	lua_ClassToLua_new,
	lua_ClassToLua_print,
	lua_ClassToLua_getMember,
	lua_ClassToLua_setMember,
	lua_ClassToLua_registerScriptHandler
};


void register_to_lua(lua_State* lstate)
{
	luaL_newmetatable( lstate,class_name);
	lua_pushstring( lstate,"__index");
	lua_pushvalue( lstate,-2);
	lua_settable( lstate,-3);
	
	LOG("a %d",lua_gettop( lstate));
	lua_newtable( lstate);
	
	LOG("b %d",lua_gettop( lstate));
	for(int i = 0 ; i < 5 ; i++)
	{
		lua_pushstring( lstate , lua_func_name[i]);
		lua_pushcfunction( lstate , cfunction[i]);
		lua_settable( lstate ,-3);

		LOG("c %d ,%s ,%p",lua_gettop( lstate) ,lua_func_name[i] , cfunction[i]);
	}
	lua_setglobal( lstate,class_name);

	for( int i = 1 ; i < 5 ; i ++)
	{
		lua_pushstring( lstate , lua_func_name[i]);
		lua_pushcfunction( lstate , cfunction[i]);
		lua_settable( lstate, -3);
	}
	lua_pop(lstate,1);
}
