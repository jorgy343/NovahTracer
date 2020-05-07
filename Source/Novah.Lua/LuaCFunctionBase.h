#pragma once

namespace Novah
{
    namespace Lua
    {
        class LuaState;

        class LuaCFunctionBase
        {
        public:
            virtual ~LuaCFunctionBase()
            {

            }

            virtual int Call(LuaState* localState) = 0;

        private:
            template <typename Ret, typename... Args, size_t... N>
            Ret Lift(std::function<Ret(Args...)> function, std::tuple<Args...> arguments, std::index_sequence<N...>)
            {
                return function(std::get<N>(arguments)...);
            }

        protected:
            template <typename Ret, typename... Args>
            Ret Lift(std::function<Ret(Args...)> function, std::tuple<Args...> arguments)
            {
                return Lift(function, arguments, std::index_sequence_for<Args...>());
            }
        };
    }
}