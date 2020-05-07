#pragma once

namespace Novah
{
    namespace Lua
    {
        namespace Globals
        {
            inline bool Pop(OfType<bool>, LuaState* state, int index);
            inline int Pop(OfType<int>, LuaState* state, int index);
            inline unsigned int Pop(OfType<unsigned int>, LuaState* state, int index);
            inline float Pop(OfType<float>, LuaState* state, int index);
            inline const char* Pop(OfType<const char*>, LuaState* state, int index);
        }
    }
}