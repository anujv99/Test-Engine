#pragma once

#include <iostream>
#include <string>

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

class LuaLoader {
public:
	void load(std::string pFileName);
	~LuaLoader() {}
	void run();
	void stop();
protected:
	virtual void commitFunctions() = 0;
	lua_State * L;
private:
	int s;
};
