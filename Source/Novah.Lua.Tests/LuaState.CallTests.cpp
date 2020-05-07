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
            TEST_CLASS(LuaState_CallTests)
            {
            public:
                TEST_METHOD(NoArguments_NoReturn)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    luaL_loadstring(rawLuaState,
                        "\
                        function LuaFunction()\
                            x = 5 \
                        end\
                        ");

                    lua_pcall(rawLuaState, 0, 0, 0);
                    luaState.Call("LuaFunction");

                    lua_getglobal(rawLuaState, "x");
                    int x = lua_tointeger(rawLuaState, -1);

                    Assert::AreEqual(5, x);
                }

                TEST_METHOD(MultipleArguments_NoReturn)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    luaL_loadstring(rawLuaState,
                        "\
                        function LuaFunction(a1, b1, c1, d1, e1)\
                            a2 = a1 \
                            b2 = b1 \
                            c2 = c1 \
                            d2 = d1 \
                            e2 = e1 \
                        end\
                        ");

                    lua_pcall(rawLuaState, 0, 0, 0);
                    luaState.Call("LuaFunction", true, -123, (unsigned int)123, 3.14f, "test");

                    lua_getglobal(rawLuaState, "a2");
                    Assert::AreEqual(true, (bool)lua_toboolean(rawLuaState, -1));
                    lua_pop(rawLuaState, 1);

                    lua_getglobal(rawLuaState, "b2");
                    Assert::AreEqual(-123, (int)lua_tointeger(rawLuaState, -1));
                    lua_pop(rawLuaState, 1);

                    lua_getglobal(rawLuaState, "c2");
                    Assert::AreEqual((unsigned int)123, (unsigned int)lua_tointeger(rawLuaState, -1));
                    lua_pop(rawLuaState, 1);

                    lua_getglobal(rawLuaState, "d2");
                    Assert::AreEqual(3.14f, (float)lua_tonumber(rawLuaState, -1));
                    lua_pop(rawLuaState, 1);

                    lua_getglobal(rawLuaState, "e2");
                    Assert::AreEqual("test", lua_tostring(rawLuaState, -1));
                    lua_pop(rawLuaState, 1);
                }

                TEST_METHOD(NoArguments_SingleReturn)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    luaL_loadstring(rawLuaState,
                        "\
                        function LuaFunction()\
                            return 5 \
                        end\
                        ");

                    lua_pcall(rawLuaState, 0, 0, 0);
                    int result = luaState.Call<int>("LuaFunction");

                    Assert::AreEqual(5, result);
                }

                TEST_METHOD(NoArguments_MultipleReturns)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    luaL_loadstring(rawLuaState,
                        "\
                        function LuaFunction()\
                            return true, -123, 123, 3.14, \"test\" \
                        end\
                        ");

                    lua_pcall(rawLuaState, 0, 0, 0);
                    auto result = luaState.Call<bool, int, unsigned int, float, const char*>("LuaFunction");

                    Assert::AreEqual(true, std::get<0>(result));
                    Assert::AreEqual(-123, std::get<1>(result));
                    Assert::AreEqual((unsigned int)123, std::get<2>(result));
                    Assert::AreEqual(3.14f, std::get<3>(result));
                    Assert::AreEqual("test", std::get<4>(result));
                }
            };
        }
    }
}