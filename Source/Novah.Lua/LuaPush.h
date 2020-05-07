#pragma once

namespace Novah
{
    namespace Lua
    {
        namespace Globals
        {
            inline void Push(LuaState* state);
            inline void Push(LuaState* state, bool value);
            inline void Push(LuaState* state, int value);
            inline void Push(LuaState* state, unsigned int value);
            inline void Push(LuaState* state, float value);
            inline void Push(LuaState* state, const char* value);
            inline void Push(LuaState* state, LuaNull value);
            inline void Push(LuaState* state, LuaGlobalName value);
            inline void Push(LuaState* state, LuaNewTable value);

            template <typename... Ts, typename... Us>
            void Push(LuaState* state, const LuaTableField<Ts, Us>&... fields);

            template <int ConsecutiveElements, int OtherElements, typename... Ts, typename... Us>
            void Push(LuaState* state, const LuaTableField<Ts, Us>&... fields);

            template <typename... Ts>
            void Push(LuaState* state, const std::tuple<Ts...>& value);
        }
    }
}