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
            TEST_CLASS(LuaState_PushTests)
            {
            public:
                TEST_METHOD(TestBool)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    luaState.Push(true);

                    Assert::AreEqual(1, lua_gettop(rawLuaState));
                    Assert::IsTrue(lua_isboolean(rawLuaState, -1));
                    Assert::AreEqual(true, (bool)lua_toboolean(rawLuaState, -1));
                }
                
                TEST_METHOD(TestInt)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    luaState.Push(-123);

                    Assert::AreEqual(1, lua_gettop(rawLuaState));
                    Assert::IsTrue(lua_isnumber(rawLuaState, -1));
                    Assert::AreEqual(-123, (int)lua_tointeger(rawLuaState, -1));
                }

                TEST_METHOD(TestUnsignedInt)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    luaState.Push(123);

                    Assert::AreEqual(1, lua_gettop(rawLuaState));
                    Assert::IsTrue(lua_isnumber(rawLuaState, -1));
                    Assert::AreEqual((unsigned int)123, (unsigned int)lua_tointeger(rawLuaState, -1));
                }

                TEST_METHOD(TestFloat)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    luaState.Push(3.14f);

                    Assert::AreEqual(1, lua_gettop(rawLuaState));
                    Assert::IsTrue(lua_isnumber(rawLuaState, -1));
                    Assert::AreEqual(3.14f, (float)lua_tonumber(rawLuaState, -1));
                }

                TEST_METHOD(TestString)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    luaState.Push("test");

                    Assert::AreEqual(1, lua_gettop(rawLuaState));
                    Assert::IsTrue(lua_isstring(rawLuaState, -1));
                    Assert::AreEqual("test", lua_tostring(rawLuaState, -1));
                }

                TEST_METHOD(TestLuaNull)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    luaState.Push(LuaNull());

                    Assert::AreEqual(1, lua_gettop(rawLuaState));
                    Assert::IsTrue(lua_isnil(rawLuaState, -1));
                }
            };
        }
    }
}