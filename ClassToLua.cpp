#include "ClassToLua.h"
#include <iostream>
#include "LuaStack.h"

ClassToLua::ClassToLua()
{
	m_member = 0;
	m_scriptHandler = -1;
}

ClassToLua::~ClassToLua()
{

}

void ClassToLua::print(){
	if( m_scriptHandler != -1){
		LuaStack::getInstance()->execute(m_scriptHandler);
	}else{
		std::cout<< "Class: member->" << m_member<< "\n";
	}
}

void ClassToLua::registerScriptHandler( int handler )
{
	m_scriptHandler = handler;
}

void ClassToLua::setMember( int member)
{
	m_member = member;
}

int ClassToLua::getMember()
{
	return m_member;
}

