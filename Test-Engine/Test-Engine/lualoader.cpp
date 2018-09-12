#include "lualoader.h"

void LuaLoader::load(std::string pFileName) {
	pFileName = "res/scripts/" + pFileName;
	L = luaL_newstate();
	luaL_openlibs(L);
	commitFunctions();
	s = luaL_loadfile(L, pFileName.c_str());
}

void LuaLoader::run() {
	if (!s)
		s = lua_pcall(L, 0, LUA_MULTRET, 0);

	if (s) {
		std::cout << "Error : " << lua_tostring(L, -1);
		lua_pop(L, 1);
	}
}

void LuaLoader::stop() {
	lua_close(L);
}
