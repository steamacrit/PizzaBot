/*
** $Id: lua.c,v 1.230.1.1 2017/04/19 17:29:57 roberto Exp $
** Lua stand-alone interpreter
** See Copyright Notice in lua.h
*/

#include <stdexcept>

#include "lua/lprefix.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua/lua.hpp"

#include "Lua.h"

std::shared_ptr<Lua> g_lua{ nullptr };

std::shared_ptr<Lua> Lua::GetLua()
{
	if (g_lua == nullptr)
		g_lua.reset(new Lua());

	return g_lua;
}

Lua::Lua()
{
	m_lua = luaL_newstate();
	if (m_lua == nullptr)
		throw (std::runtime_error("Could not create Lua State"));

	luaL_checkversion(m_lua);  // check that interpreter has correct version 
	luaL_openlibs(m_lua);  // open standard libraries 
	//AddLibrary(global_funcs);
}

Lua::~Lua()
{

}

//void Lua::SetOutputCB(LuaOutputCallback cb)
//{
//	luaL_SetOutputCallback(cb);
//}

int Lua::GetStackSize()
{
	return lua_gettop(m_lua);
}

void Lua::StackDump()
{
	//LuaStackDump(m_lua);
}

bool Lua::GetvariableBOOL(const char * name, bool & value)
{
	lua_getglobal(m_lua, name);

    if (!lua_isboolean(m_lua, -1))
        return false;

    value = lua_toboolean(m_lua, -1);

    Pop();

    return true;
}

bool Lua::GetVariableI64(const char * name, int64_t & value)
{	
	lua_getglobal(m_lua, name);

	if (!lua_isinteger(m_lua, -1))
		return false;

    value = lua_tointeger(m_lua, -1);

    Pop();

    return true;
}

bool Lua::GetVariableDBL(const char * name, double & value)
{
	lua_getglobal(m_lua, name);

    if (!lua_isnumber(m_lua, -1))
        return false;
    
    value = lua_tonumber(m_lua, -1);

    Pop();

    return true;
}

bool Lua::GetVariableSTR(const char * name, std::string & value)
{
	lua_getglobal(m_lua, name);

    if (!lua_isstring(m_lua, -1))
        return false;

    value = lua_tostring(m_lua, -1);
    
    Pop();

    return true;
}

void Lua::Pop(int n)
{
    lua_pop(m_lua, n);
}

/* void Lua::AddGlobalFunction(lua_CFunction f, const char * name)
{
	if (name == nullptr)
	{
		Log::ERR("AddGlobalFunction(LUA) - Attempt to add a global function with a no name");
		return;
	}

	lua_pushcfunction(m_lua, f);
	lua_setglobal(m_lua, name);
}

void Lua::AddLibrary(const luaL_Reg * lib, const char * lib_name)
{
	if (lib_name == nullptr)
		for (size_t i = 0; lib[i].func != nullptr && lib[i].name != nullptr; i++)
			AddGlobalFunction(lib[i].func, lib[i].name);
	else
	{
		luaL_newlib(m_lua, lib);
		for (size_t i = 0; lib[i].func != nullptr && lib[i].name != nullptr; i++)
		{
			lua_pushstring(m_lua, lib[i].name);
			lua_pushcfunction(m_lua, lib[i].func);
			lua_settable(m_lua, -3);			
		}
		lua_setglobal(m_lua, lib_name);
	}
} */

int Lua::DoString(const char *s, const char *name) {

	return DoChunk(luaL_loadbuffer(m_lua, s, strlen(s), name));
}

void Lua::RunFile(const char * filename)
{
    if (luaL_loadfile(m_lua, filename))
        lua_pcall(m_lua, 0, 0, 0);
//	if (luaL_loadfile(m_lua, filename) || lua_pcall(m_lua, 0, 0, 0))
//		Log::ERR(L"Cannot run script file {0}", converter.from_bytes(lua_tostring(m_lua, -1)));
}

/*
** Interface to 'lua_pcall', which sets appropriate message function
** and C-signal handler. Used to run all chunks.
*/
int Lua::DoCall(int narg, int nres) {
	int status;
	int base = lua_gettop(m_lua) - narg;  /* function index */
//	lua_pushcfunction(m_lua, msghandler);  /* push message handler */
	lua_insert(m_lua, base);  /* put it under function and args */
//	globalL = m_lua;  /* to be available to 'laction' */
//	signal(SIGINT, laction);  /* set C-signal handler */
	status = lua_pcall(m_lua, narg, nres, base);
	signal(SIGINT, SIG_DFL); /* reset C-signal handler */
	lua_remove(m_lua, base);  /* remove message handler from the stack */
	return status;
}

int Lua::DoChunk(int status) {
	if (status == LUA_OK) status = DoCall(0, 0);
	//return report(m_lua, status);
    return 0;
}


int Lua::DoFile(const char *name) {
	return luaL_dofile(m_lua, name);
	return DoChunk(luaL_loadfile(m_lua, name));
}





// LUA Reader Functions

// GetAntennaConfig
