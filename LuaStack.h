#ifndef __LUA_STATCK_H__
#define __LUA_STATCK_H__

#include <lua.hpp>


class LuaStack
{
	public:
		LuaStack( lua_State* lstate = 0);
		~LuaStack();

		void execute( int handle);
		lua_State* getState();

		static LuaStack* getInstance();
		static void purgeLuaStack();
	private:
		lua_State* m_state;
		static LuaStack* sg_luaStack;

};

#endif
