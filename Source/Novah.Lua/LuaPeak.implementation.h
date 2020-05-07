#pragma once

namespace Novah
{
    namespace Lua
    {
        namespace Globals
        {
            inline bool Peak(OfType<bool>, LuaState* state, int index)
            {
                return lua_toboolean(state->GetInternalState(), index);
            }

            inline int Peak(OfType<int>, LuaState* state, int index)
            {
                return luaL_checkinteger(state->GetInternalState(), index);
            }

            inline unsigned int Peak(OfType<unsigned int>, LuaState* state, int index)
            {
                return (unsigned int)luaL_checkinteger(state->GetInternalState(), index);
            }

            inline float Peak(OfType<float>, LuaState* state, int index)
            {
                return (float)luaL_checknumber(state->GetInternalState(), index);
            }

            inline const char* Peak(OfType<const char*>, LuaState* state, int index)
            {
                return luaL_checkstring(state->GetInternalState(), index);
            }
        }
    }
}