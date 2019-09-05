#pragma once

#include <memory>

struct lua_State;

class Lua
{
public:
	~Lua();
	
	static std::shared_ptr<Lua> GetLua();

	//void SetOutputCB(LuaOutputCallback cb);

	void RunFile(const char * filename);
	int DoString(const char *s, const char *name = nullptr);


	int GetStackSize();
	void StackDump();
	
	bool GetvariableBOOL(const char * name, bool & value);
	bool GetVariableI64(const char * name, int64_t & value);
	bool GetVariableDBL(const char * name, double & value);
	bool GetVariableSTR(const char * name, std::string & value);

	void Pop(int n = 1);

	//void AddGlobalFunction(lua_CFunction f, const char * name);
	//void AddLibrary(const luaL_Reg * lib, const char * lib_name = nullptr);

private:
	Lua();
	lua_State * m_lua;

private:
	int DoChunk(int status);
	int DoCall(int narg, int nres);
	int DoFile(const char *name);
};