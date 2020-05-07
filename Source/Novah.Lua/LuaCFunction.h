#pragma once

namespace Novah
{
    namespace Lua
    {
        template <typename Ret, typename... Args>
        class LuaCFunction : LuaCFunctionBase
        {
        private:
            using FunctionType = std::function<Ret(Args...)>;

            LuaState* _state;
            const char* _functionName;
            FunctionType _function;

        public:
            LuaCFunction(LuaState* state, const char* functionName, Ret(*function)(Args...))
                : LuaCFunction(state, functionName, FunctionType(function))
            {

            }

            /// <summary>
            ///     Creates a new instance of this class and registers the provided <paramref name="function" /> with the lua context as a global function with the name provided by
            ///     <paramref name="functionName" />. The function returns a single value and takes zero or more arguments.
            /// </summary>
            /// <param name="state">The lua context.</param>
            /// <param name="functionName">The name that lua scripts will use to call the function.</param>
            /// <param name="function">The function that will be called in C code when the function is called in a lua script.</param>
            LuaCFunction(LuaState* state, const char* functionName, FunctionType function)
                : _state(state), _functionName(functionName), _function(function)
            {
                lua_pushlightuserdata(_state->GetInternalState(), (void*)static_cast<LuaCFunctionBase*>(this));
                lua_pushcclosure(_state->GetInternalState(), &LuaCFunctionDispatcher, 1);

                lua_setglobal(_state->GetInternalState(), _functionName);
            }

            /// <summary>
            ///     Removes the global function from the lua context.
            /// </summary>
            ~LuaCFunction()
            {
                if (_state != nullptr)
                {
                    _state->SetGlobal(_functionName, LuaNull());
                }
            }

            int Call(LuaState* localState) override
            {
                auto arguments = localState->PeakMany<Args...>();
                auto value = Lift(_function, arguments);

                localState->Push(value);
                return 1;
            }
        };

        template <typename... Ret, typename... Args>
        class LuaCFunction<std::tuple<Ret...>, Args...> : LuaCFunctionBase
        {
        private:
            using FunctionType = std::function<std::tuple<Ret...>(Args...)>;

            LuaState* _state;
            const char* _functionName;
            FunctionType _function;

        public:
            LuaCFunction(LuaState* state, const char* functionName, std::tuple<Ret...>(*function)(Args...))
                : LuaCFunction(state, functionName, FunctionType(function))
            {

            }

            /// <summary>
            ///     Creates a new instance of this class and registers the provided <paramref name="function" /> with the lua context as a global function with the name provided by
            ///     <paramref name="functionName" />. The function returns a tuple of zero or more items and takes zero or more arguments.
            /// </summary>
            /// <param name="state">The lua context.</param>
            /// <param name="functionName">The name that lua scripts will use to call the function.</param>
            /// <param name="function">The function that will be called in C code when the function is called in a lua script.</param>
            LuaCFunction(LuaState* state, const char* functionName, FunctionType function)
                : _state(state), _functionName(functionName), _function(function)
            {
                lua_pushlightuserdata(_state->GetInternalState(), (void*)static_cast<LuaCFunctionBase*>(this));
                lua_pushcclosure(_state->GetInternalState(), &LuaCFunctionDispatcher, 1);

                lua_setglobal(_state->GetInternalState(), _functionName);
            }

            /// <summary>
            ///     Removes the global function from the lua context.
            /// </summary>
            ~LuaCFunction()
            {
                if (_state != nullptr)
                {
                    _state->SetGlobal(_functionName, LuaNull());
                }
            }

            int Call(LuaState* localState) override
            {
                auto arguments = localState->PeakMany<Args...>();
                auto value = Lift(_function, arguments);

                localState->Push(value);
                return sizeof...(Ret);
            }
        };

        template <typename... Args>
        class LuaCFunction<void, Args...> : LuaCFunctionBase
        {
        private:
            using FunctionType = std::function<void(Args...)>;

            LuaState* _state;
            const char* _functionName;
            FunctionType _function;

        public:
            LuaCFunction(LuaState* state, const char* functionName, void(*function)(Args...))
                : LuaCFunction(state, functionName, FunctionType(function))
            {

            }

            /// <summary>
            ///     Creates a new instance of this class and registers the provided <paramref name="function" /> with the lua context as a global function with the name provided by
            ///     <paramref name="functionName" />. The function returns void and takes zero or more arguments.
            /// </summary>
            /// <param name="state">The lua context.</param>
            /// <param name="functionName">The name that lua scripts will use to call the function.</param>
            /// <param name="function">The function that will be called in C code when the function is called in a lua script.</param>
            LuaCFunction(LuaState* state, const char* functionName, FunctionType function)
                : _state(state), _functionName(functionName), _function(function)
            {
                lua_pushlightuserdata(_state->GetInternalState(), (void*)static_cast<LuaCFunctionBase*>(this));
                lua_pushcclosure(_state->GetInternalState(), &LuaCFunctionDispatcher, 1);

                lua_setglobal(_state->GetInternalState(), _functionName);
            }

            /// <summary>
            ///     Removes the global function from the lua context.
            /// </summary>
            ~LuaCFunction()
            {
                if (_state != nullptr)
                    _state->SetGlobal(_functionName, LuaNull());
            }

            int Call(LuaState* localState) override
            {
                auto arguments = localState->PeakMany<Args...>();
                Lift(_function, arguments);

                return 0;
            }
        };
    }
}