#ifndef _CLASS_TO_LUA_
#define _CLASS_TO_LUA_

class ClassToLua
{
	public:
		void print();
		void registerScriptHandler( int handler );
		
		void setMember(int member);
		int getMember();

		ClassToLua();
		~ClassToLua();
	private:
		int m_member;
		int m_scriptHandler;
};

#endif	
