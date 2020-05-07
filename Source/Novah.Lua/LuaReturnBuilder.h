#pragma once

namespace Novah
{
    namespace Lua
    {
        // Two or more return parameters, return type is a tuple.
        template <size_t S, typename... Ts>
        struct LuaReturnBuilder
        {
            using Type = std::tuple<Ts...>;

            template <size_t... N>
            static Type Worker(LuaState* state, std::index_sequence<N...>)
            {
                return std::make_tuple(Peak(OfType<Ts>(), state, -S + N)...);
            }

            static Type Apply(LuaState* state)
            {
                auto ret = Worker(state, std::index_sequence_for<Ts...>());
                state->Pop(S);

                return ret;
            }
        };

        // One return parameter, return type is unboxed.
        template <typename T>
        struct LuaReturnBuilder<1, T>
        {
            using Type = T;

            static Type Apply(LuaState* state)
            {
                T ret = Peak(OfType<T>(), state, -1);
                state->Pop();

                return ret;
            }
        };

        // No return parameters, return type is void.
        template <typename... Ts>
        struct LuaReturnBuilder<0, Ts...>
        {
            using Type = void;

            static Type Apply(LuaState* state)
            {

            }
        };
    }
}