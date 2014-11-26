
local a = ClassToLua:new();
print(a);
ClassToLua.print(a);
ClassToLua.setMember(a,2);
ClassToLua.print(a);

function print_script()
	print("lua print ----->>success!\n");
end

ClassToLua.registerScriptHandler(a, print_script );
ClassToLua.print(a);

local b = ClassToLua.new();
ClassToLua.setMember(b,1314);
ClassToLua.print(b);
ClassToLua.print(a);

local metatable = getmetatable(b);
print(metatable);

b:print();
print(b:getMember());
