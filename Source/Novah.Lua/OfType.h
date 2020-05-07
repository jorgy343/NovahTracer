#pragma once

namespace Novah
{
    namespace Lua
    {
        /// <summary>
        ///     A class used specifically for peaking and popping values off of the Lua stack. This class is used to define what type of object to peak or pop off of the stack and is usually
        ///     included as the first parameter of the function.
        /// </summary>
        template <typename T>
        struct OfType
        {

        };
    }
}