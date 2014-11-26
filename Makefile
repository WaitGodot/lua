
CXXFLAGS = -g -Wall
IINCLUDE = -I/usr/local/include
ISRC =
LDINCLUDE = -L/usr/local/lib
LDFLAGS = -llua
CC = g++

vpath %.hpp /usr/local/include
vpath %.h	./

TARGET = test
SRC =	main.cpp \
		lua_class.cpp \
		ClassToLua.cpp \
		lua_imp.cpp	\
		LuaStack.cpp	

$(TARGET) : $(OBJECTS)
	$(CC) $(CXXFLAGS) $(IINCLUDE) -o $(TARGET) $(SRC) $(LDINCLUDE) $(LDFLAGS)


.PHONY : clean
clean:
	-rm -rf $(TARGET) *.o 


