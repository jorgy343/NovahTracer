#pragma once

namespace Novah
{
    namespace Lua
    {
        namespace Globals
        {
            inline bool Peak(OfType<bool>, LuaState* state, int index);
            inline int Peak(OfType<int>, LuaState* state, int index);
            inline unsigned int Peak(OfType<unsigned int>, LuaState* state, int index);
            inline float Peak(OfType<float>, LuaState* state, int index);
            inline const char* Peak(OfType<const char*>, LuaState* state, int index);
        }
    }
}