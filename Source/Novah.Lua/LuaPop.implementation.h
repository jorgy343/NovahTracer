#pragma once

namespace Novah
{
    namespace Lua
    {
        namespace Globals
        {
            inline bool Pop(OfType<bool>, LuaState* state, int index)
            {
                auto value = state->Peak(OfType<bool>(), index);
                state->Pop();

                return value;
            }

            inline int Pop(OfType<int>, LuaState* state, int index)
            {
                auto value = state->Peak(OfType<int>(), index);
                state->Pop();

                return value;
            }

            inline unsigned int Pop(OfType<unsigned int>, LuaState* state, int index)
            {
                auto value = state->Peak(OfType<unsigned int>(), index);
                state->Pop();

                return value;
            }

            inline float Pop(OfType<float>, LuaState* state, int index)
            {
                auto value = state->Peak(OfType<float>(), index);
                state->Pop();

                return value;
            }

            inline const char* Pop(OfType<const char*>, LuaState* state, int index)
            {
                auto value = state->Peak(OfType<const char*>(), index);
                state->Pop();

                return value;
            }
        }
    }
}