#pragma once

namespace Novah
{
    namespace Lua
    {
        template <size_t S, typename... Ts>
        struct LuaPushTuple
        {
            static void PushTuple(LuaState* state, const std::tuple<Ts...>& value)
            {
                state->Push(std::get<sizeof...(Ts) - S>(value));
                LuaPushTuple<S - 1, Ts...>::PushTuple(state, value);
            }
        };

        template <typename... Ts>
        struct LuaPushTuple<1, Ts...>
        {
            static void PushTuple(LuaState* state, const std::tuple<Ts...>& value)
            {
                state->Push(std::get<sizeof...(Ts) - 1>(value));
            }
        };

        template <typename... Ts>
        struct LuaPushTuple<0, Ts...>
        {
            static void PushTuple(LuaState* state, const std::tuple<Ts...>& value)
            {

            }
        };
    }
}