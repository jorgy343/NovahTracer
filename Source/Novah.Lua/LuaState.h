#pragma once

#include <utility>
#include <tuple>
#include <functional>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

namespace Novah
{
    namespace Lua
    {
        class LuaState;
    }
}

#include "OfType.h"
#include "LuaNull.h"
#include "LuaGlobalName.h"
#include "LuaNewTable.h"

#include "LuaTableField.h"

#include "LuaPush.h"
#include "LuaPushTuple.h"
#include "LuaPeak.h"
#include "LuaPop.h"

#include "LuaReturnBuilder.h"

#include "LuaCFunctionBase.h"
#include "LuaCFunction.h"

using namespace Novah::Lua::Globals;

namespace Novah
{
    namespace Lua
    {
        class LuaState
        {
        private:
            lua_State* _state;
            bool _keepAlive;

        public:
            LuaState(bool keepAlive = false)
                : _state(luaL_newstate()), _keepAlive(keepAlive)
            {

            }

            LuaState(lua_State* state, bool keepAlive = true)
                : _state(state), _keepAlive(keepAlive)
            {

            }

            ~LuaState()
            {
                if (!_keepAlive)
                    lua_close(_state);
            }

            lua_State* GetInternalState()
            {
                return _state;
            }

            void LoadFile(const char* filename)
            {
                luaL_loadfile(_state, filename);
            }

            void LoadFileAndExecute(const char* filename)
            {
                luaL_dofile(_state, filename);
            }

            void LoadString(const char* string)
            {
                luaL_loadstring(_state, string);
            }

            void LoadStringAndExecute(const char* string)
            {
                luaL_loadstring(_state, string);
                Execute();
            }

            void Execute()
            {
                lua_pcall(_state, 0, 0, 0);
            }

            template <typename T>
            void SetGlobal(const char* globalName, T value)
            {
                Push(value);
                lua_setglobal(_state, globalName);
            }

            template <typename T>
            void SetGlobal(LuaGlobalName globalName, T value)
            {
                Push(value);
                lua_setglobal(_state, globalName.Name);
            }

            // GC
            void GcStop()
            {
                lua_gc(_state, LUA_GCSTOP, 0);
            }

            void GcStart()
            {
                lua_gc(_state, LUA_GCRESTART, 0);
            }

            void GcCollect()
            {
                lua_gc(_state, LUA_GCCOLLECT, 0);
            }

            int GcGetMemoryUsedInKb()
            {
                return lua_gc(_state, LUA_GCCOUNT, 0);
            }

            int GcGetMemoryUsedInBytes()
            {
                return lua_gc(_state, LUA_GCCOUNT, 0) * 1024 + lua_gc(_state, LUA_GCCOUNTB, 0);
            }

            bool GcStep(int stepSize)
            {
                return lua_gc(_state, LUA_GCSTEP, stepSize);
            }

            void GcSetPause(int pause)
            {
                lua_gc(_state, LUA_GCSETPAUSE, pause);
            }

            void GcSetStepMultiplier(int stepMultiplier)
            {
                lua_gc(_state, LUA_GCSETSTEPMUL, stepMultiplier);
            }

            bool GcIsRunning()
            {
                return lua_gc(_state, LUA_GCISRUNNING, 0);
            }

            // Tables
            void PushTableFields()
            {

            }

            template <typename T, typename U, typename... Ts, typename... Us>
            void PushTableFields(LuaTableField<T, U> field, LuaTableField<Ts, Us>... fields)
            {
                Push(field.Key);
                Push(field.Value);

                lua_settable(_state, -3);
                PushTableFields(fields...);
            }

            template <typename... Ts, typename... Us>
            void PushTable(LuaTableField<Ts, Us>... fields)
            {
                PushTable<0, 0>(fields...);
            }

            template <int ConsecutiveElements, int OtherElements, typename... Ts, typename... Us>
            void PushTable(LuaTableField<Ts, Us>... fields)
            {
                lua_createtable(_state, ConsecutiveElements, OtherElements);
                PushTableFields(fields...);
            }

            template <typename T, typename U>
            U GetTableField(int tableIndex, T key)
            {
                // Adjust the index to account for our push if the index is top relative.
                if (tableIndex < 0)
                    tableIndex--;

                Push(std::forward<T>(key));
                lua_gettable(_state, tableIndex);

                return PopForReturn<U>();
            }

            // Call
            template <typename... Ret, typename... Args>
            typename LuaReturnBuilder<sizeof...(Ret), Ret...>::Type Call(const char* functionName, Args&&... arguments)
            {
                Push((LuaGlobalName)functionName, std::forward<Args>(arguments)...);
                lua_call(_state, sizeof...(Args), sizeof...(Ret));

                return PopForReturn<Ret...>();
            }

            // Push
            void Push()
            {

            }

            template <typename T, typename... Ts>
            void Push(T&& value, Ts&&... values)
            {
                ::Push(this, std::forward<T>(value));
                Push(std::forward<Ts>(values)...);
            }

            // Peak
            template <typename T>
            T Peak(OfType<T>)
            {
                return Peak(OfType<T>(), -1);
            }

            template <typename T>
            T Peak(OfType<T>, int index)
            {
                return ::Peak(OfType<T>(), this, index);
            }

        private:
            template <typename... Ts, size_t... N>
            std::tuple<Ts...> PeakMany(std::index_sequence<N...>)
            {
                return std::make_tuple(Peak(OfType<Ts>(), -sizeof...(Ts)+N)...);
            }

        public:
            template <typename... Ts>
            std::tuple<Ts...> PeakMany()
            {
                return PeakMany<Ts...>(std::index_sequence_for<Ts...>());
            }

            // Pop
            template <typename T>
            T Pop(OfType<T>)
            {
                auto value = Peak(OfType<T>());
                Pop();

                return std::forward<T>(value);
            }

            template <typename... Ts>
            std::tuple<Ts...> PopMany()
            {
                auto value = PeakMany<Ts...>(std::index_sequence_for<Ts...>());
                Pop(sizeof...(Ts));

                return value;
            }

            void Pop()
            {
                lua_pop(_state, 1);
            }

            void Pop(int count)
            {
                lua_pop(_state, count);
            }

            template <typename... Ts>
            typename LuaReturnBuilder<sizeof...(Ts), Ts...>::Type PopForReturn()
            {
                return LuaReturnBuilder<sizeof...(Ts), Ts...>::Apply(this);
            }

        public:
            void StackDump()
            {
                int i;
                int top = lua_gettop(_state);

                printf("total in stack %d\n", top);
                for (i = 1; i <= top; i++)
                {
                    int t = lua_type(_state, i);
                    switch (t)
                    {
                    case LUA_TSTRING:
                        printf("string: '%s'\n", lua_tostring(_state, i));
                        break;

                    case LUA_TBOOLEAN:
                        printf("boolean %s\n", lua_toboolean(_state, i) ? "true" : "false");
                        break;

                    case LUA_TNUMBER:
                        printf("number: %g\n", lua_tonumber(_state, i));
                        break;

                    default:
                        printf("%s\n", lua_typename(_state, t));
                        break;
                    }

                    printf("  ");
                }

                printf("\n");
            }
        };
    }
}

#include "LuaPush.implementation.h"
#include "LuaPeak.implementation.h"
#include "LuaPop.implementation.h"

#include "LuaCFunctionDispatcher.h"