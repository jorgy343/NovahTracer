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
            TEST_CLASS(LuaState_PeakTests)
            {
            public:
                TEST_METHOD(TestBool)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    lua_pushboolean(rawLuaState, true);

                    auto result1 = luaState.Peak(OfType<bool>());
                    auto result2 = luaState.Peak(OfType<bool>(), -1);

                    Assert::AreEqual(1, lua_gettop(rawLuaState));
                    Assert::AreEqual(true, result1);
                    Assert::AreEqual(true, result2);
                }

                TEST_METHOD(TestInt)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    lua_pushinteger(rawLuaState, -123);

                    auto result1 = luaState.Peak(OfType<int>());
                    auto result2 = luaState.Peak(OfType<int>(), -1);

                    Assert::AreEqual(1, lua_gettop(rawLuaState));
                    Assert::AreEqual(-123, result1);
                    Assert::AreEqual(-123, result2);
                }

                TEST_METHOD(TestUnsignedInt)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    lua_pushinteger(rawLuaState, 123);

                    auto result1 = luaState.Peak(OfType<unsigned int>());
                    auto result2 = luaState.Peak(OfType<unsigned int>(), -1);

                    Assert::AreEqual(1, lua_gettop(rawLuaState));
                    Assert::AreEqual((unsigned int)123, result1);
                    Assert::AreEqual((unsigned int)123, result2);
                }

                TEST_METHOD(TestFloat)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    lua_pushnumber(rawLuaState, 3.14f);

                    auto result1 = luaState.Peak(OfType<float>());
                    auto result2 = luaState.Peak(OfType<float>(), -1);

                    Assert::AreEqual(1, lua_gettop(rawLuaState));
                    Assert::AreEqual(3.14f, result1);
                    Assert::AreEqual(3.14f, result2);
                }

                TEST_METHOD(TestString)
                {
                    LuaState luaState;
                    lua_State* rawLuaState = luaState.GetInternalState();

                    lua_pushstring(rawLuaState, "test");

                    auto result1 = luaState.Peak(OfType<const char*>());
                    auto result2 = luaState.Peak(OfType<const char*>(), -1);

                    Assert::AreEqual(1, lua_gettop(rawLuaState));
                    Assert::AreEqual("test", result1);
                    Assert::AreEqual("test", result2);
                }
            };
        }
    }
}