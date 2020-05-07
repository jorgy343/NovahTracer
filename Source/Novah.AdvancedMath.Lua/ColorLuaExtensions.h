#pragma once

#include "NovahAdvancedMath.h"
#include "LuaState.h"

using namespace Novah::Lua;
using namespace Novah::AdvancedMath;

namespace Novah
{
    namespace Lua
    {
        namespace Globals
        {
            // Color3
            inline void Push(LuaState* state, const Color3& value)
            {
                Push<3, 0>(state, MakeLuaTableField("Red", value.Red), MakeLuaTableField("Green", value.Green), MakeLuaTableField("Blue", value.Blue));
            }

            inline Color3 Peak(OfType<Color3>, LuaState* state, int index)
            {
                float x = state->GetTableField<const char*, float>(index, "Red");
                float y = state->GetTableField<const char*, float>(index, "Green");
                float z = state->GetTableField<const char*, float>(index, "Blue");

                return Color3(x, y, z);
            }

            inline Color3 Pop(OfType<Color3>, LuaState* state, int index)
            {
                auto value = state->Peak(OfType<Color3>(), index);
                state->Pop();

                return value;
            }

            // Color4
            inline void Push(LuaState* state, const Color4& value)
            {
                Push<4, 0>(state, MakeLuaTableField("Red", value.Red), MakeLuaTableField("Green", value.Green), MakeLuaTableField("Blue", value.Blue), MakeLuaTableField("Alpha", value.Alpha));
            }

            inline Color4 Peak(OfType<Color4>, LuaState* state, int index)
            {
                float r = state->GetTableField<const char*, float>(index, "Red");
                float g = state->GetTableField<const char*, float>(index, "Green");
                float b = state->GetTableField<const char*, float>(index, "Blue");
                float a = state->GetTableField<const char*, float>(index, "Alpha");

                return Color4(r, g, b, a);
            }

            inline Color4 Pop(OfType<Color4>, LuaState* state, int index)
            {
                auto value = state->Peak(OfType<Color4>(), index);
                state->Pop();

                return value;
            }
        }
    }
}