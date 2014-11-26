#include "LuaStack.h"
#include "lua_class.h"
#include "macroConfig.h"



LuaStack* LuaStack::sg_luaStack = 0;

LuaStack::LuaStack( lua_State* lstate)
{
	if(lstate){
		m_state = lstate;
	}else{
		m_state = luaL_newstate();
	}
}

LuaStack::~LuaStack()
{
	lua_close(m_state);
}

void LuaStack::execute(int handler)
{
	int rt = registryIndexToLua(m_state,handler);
	if( rt == LC_OK ){
		int error_no = lua_pcall( m_state ,0,0,0);
		if( error_no != LUA_OK ){
			LOG_ERROR("lua stack execute error no : %d ,string: %s",error_no,lua_tostring(m_state,-1));
		}
	}
}

lua_State* LuaStack::getState()
{
	return m_state;
}

LuaStack* LuaStack::getInstance()
{
	if(!sg_luaStack){
		sg_luaStack = new LuaStack();
	}
	return sg_luaStack;
}

void LuaStack::purgeLuaStack()
{
	if(sg_luaStack){
		delete sg_luaStack;
		sg_luaStack = 0;
	}
}
