#pragma once

namespace Novah
{
    namespace Lua
    {
        namespace Globals
        {
            inline int LuaCFunctionDispatcher(lua_State* localState)
            {
                LuaCFunctionBase* baseFunction = (LuaCFunctionBase*)lua_touserdata(localState, lua_upvalueindex(1));

                // Theoretically, Lua could give us a different state than the one the base function is using. I'm not convinced that
                // this is true since initial tests show both are the same pointer. Furthermore, interchanging them also works.
                LuaState localStateWrapper(localState);
                return baseFunction->Call(&localStateWrapper);
            }
        }
    }
}