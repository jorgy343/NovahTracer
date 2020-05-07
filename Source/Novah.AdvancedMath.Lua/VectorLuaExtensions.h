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
            // Vector2
            inline void Push(LuaState* state, const Vector2& value)
            {
                Push<2, 0>(state, MakeLuaTableField("X", value.X), MakeLuaTableField("Y", value.Y));
            }

            inline Vector2 Peak(OfType<Vector2>, LuaState* state, int index)
            {
                float x = state->GetTableField<const char*, float>(index, "X");
                float y = state->GetTableField<const char*, float>(index, "Y");

                return Vector2(x, y);
            }

            inline Vector2 Pop(OfType<Vector2>, LuaState* state, int index)
            {
                auto value = state->Peak(OfType<Vector2>(), index);
                state->Pop();

                return value;
            }

            // Vector3
            inline void Push(LuaState* state, const Vector3& value)
            {
                Push<3, 0>(state, MakeLuaTableField("X", value.X), MakeLuaTableField("Y", value.Y), MakeLuaTableField("Z", value.Z));
            }
            
            inline Vector3 Peak(OfType<Vector3>, LuaState* state, int index)
            {
                float x = state->GetTableField<const char*, float>(index, "X");
                float y = state->GetTableField<const char*, float>(index, "Y");
                float z = state->GetTableField<const char*, float>(index, "Z");

                return Vector3(x, y, z);
            }

            inline Vector3 Pop(OfType<Vector3>, LuaState* state, int index)
            {
                auto value = state->Peak(OfType<Vector3>(), index);
                state->Pop();

                return value;
            }

            // Vector4
            inline void Push(LuaState* state, const Vector4& value)
            {
                Push<4, 0>(state, MakeLuaTableField("X", value.X), MakeLuaTableField("Y", value.Y), MakeLuaTableField("Z", value.Z), MakeLuaTableField("W", value.W));
            }

            inline Vector4 Peak(OfType<Vector4>, LuaState* state, int index)
            {
                float x = state->GetTableField<const char*, float>(index, "X");
                float y = state->GetTableField<const char*, float>(index, "Y");
                float z = state->GetTableField<const char*, float>(index, "Z");
                float w = state->GetTableField<const char*, float>(index, "W");

                return Vector4(x, y, z, w);
            }

            inline Vector4 Pop(OfType<Vector4>, LuaState* state, int index)
            {
                auto value = state->Peak(OfType<Vector4>(), index);
                state->Pop();

                return value;
            }
        }
    }
}