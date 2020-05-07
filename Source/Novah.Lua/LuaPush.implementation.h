#include "LuaPush.h"
#pragma once

namespace Novah
{
    namespace Lua
    {
        namespace Globals
        {
            inline void Push(LuaState* state)
            {

            }

            inline void Push(LuaState* state, bool value)
            {
                lua_pushboolean(state->GetInternalState(), value);
            }

            inline void Push(LuaState* state, int value)
            {
                lua_pushinteger(state->GetInternalState(), value);
            }

            inline void Push(LuaState* state, unsigned int value)
            {
                lua_pushinteger(state->GetInternalState(), value);
            }

            inline void Push(LuaState* state, float value)
            {
                lua_pushnumber(state->GetInternalState(), value);
            }

            inline void Push(LuaState* state, const char* value)
            {
                lua_pushstring(state->GetInternalState(), value);
            }

            inline void Push(LuaState* state, LuaNull value)
            {
                lua_pushnil(state->GetInternalState());
            }

            inline void Push(LuaState* state, LuaGlobalName value)
            {
                lua_getglobal(state->GetInternalState(), value.Name);
            }

            inline void Push(LuaState* state, LuaNewTable value)
            {
                lua_newtable(state->GetInternalState());
            }

            template <typename... Ts, typename... Us>
            void Push(LuaState* state, const LuaTableField<Ts, Us>&... fields)
            {
                PushTable<0, 0>(fields...);
            }

            template <int ConsecutiveElements, int OtherElements, typename... Ts, typename... Us>
            void Push(LuaState* state, const LuaTableField<Ts, Us>&... fields)
            {
                state->PushTable<ConsecutiveElements, OtherElements>(fields...);
            }

            template <typename... Ts>
            void Push(LuaState* state, const std::tuple<Ts...>& value)
            {
                LuaPushTuple<sizeof...(Ts), Ts...>::PushTuple(state, value);
            }
        }
    }
}