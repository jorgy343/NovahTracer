#pragma once

namespace Novah
{
    namespace Lua
    {
        class LuaGlobalName
        {
        public:
            const char* Name;

            LuaGlobalName(const char* name)
                : Name(name)
            {

            }
        };
    }
}