#include "stdafx.h"
#include "CppUnitTest.h"

#include "LuaState.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Novah
{
    namespace Lua
    {
        namespace Tests
        {
            void Function_NoReturn()
            {

            }

            int Function_OneReturn(int x)
            {
                return x;
            }

            std::tuple<bool, int, unsigned int, float, const char*> Function_MultipleReturns(bool a, int b, unsigned int c, float d, const char* e)
            {
                return std::make_tuple(a, b, c, d, e);
            }

            TEST_CLASS(CFuncionTests)
            {
            public:
                TEST_METHOD(NormalFunction_NoReturn)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    LuaCFunction<void> cFunction(&luaState, "CFunction", Function_NoReturn);
                    luaL_loadstring(rawLuaState,
                        "\
                        CFunction()\
                        ");

                    lua_pcall(rawLuaState, 0, 0, 0);
                }

                TEST_METHOD(NormalFunction_OneReturn)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    LuaCFunction<int, int> cFunction(&luaState, "CFunction", Function_OneReturn);
                    luaL_loadstring(rawLuaState,
                        "\
                        x = CFunction(5)\
                        ");

                    lua_pcall(rawLuaState, 0, 0, 0);

                    lua_getglobal(rawLuaState, "x");
                    int x = lua_tointeger(rawLuaState, -1);
                    Assert::AreEqual(5, x);
                }
                
                TEST_METHOD(NormalFunction_MultipleReturns)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    LuaCFunction<std::tuple<bool, int, unsigned int, float, const char*>, bool, int, unsigned int, float, const char*> cFunction(&luaState, "CFunction", Function_MultipleReturns);
                    luaL_loadstring(rawLuaState,
                        "\
                        a, b, c, d, e = CFunction(true, -123, 123, 3.14, \"test\")\
                        ");

                    lua_pcall(rawLuaState, 0, 0, 0);

                    lua_getglobal(rawLuaState, "a");
                    Assert::AreEqual(true, (bool)lua_toboolean(rawLuaState, -1));
                    lua_pop(rawLuaState, 1);

                    lua_getglobal(rawLuaState, "b");
                    Assert::AreEqual(-123, (int)lua_tointeger(rawLuaState, -1));
                    lua_pop(rawLuaState, 1);

                    lua_getglobal(rawLuaState, "c");
                    Assert::AreEqual((unsigned int)123, (unsigned int)lua_tointeger(rawLuaState, -1));
                    lua_pop(rawLuaState, 1);

                    lua_getglobal(rawLuaState, "d");
                    Assert::AreEqual(3.14f, (float)lua_tonumber(rawLuaState, -1));
                    lua_pop(rawLuaState, 1);

                    lua_getglobal(rawLuaState, "e");
                    Assert::AreEqual("test", lua_tostring(rawLuaState, -1));
                    lua_pop(rawLuaState, 1);
                }
            };
        }
    }
}