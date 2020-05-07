#pragma once

namespace Novah
{
    namespace Lua
    {
        /// <summary>
        ///     A class that represents a single field in a Lua table. The key and value can be any types supported by Lua.
        /// </summary>
        template <typename TKey, typename TValue>
        class LuaTableField
        {
        public:
            /// <summary>
            ///     The key of the field.
            /// </summary>
            TKey Key;

            /// <summary>
            ///     The value of the field.
            /// </summary>
            TValue Value;

            /// <summary>
            ///     Creates a new instance of this object.
            /// </summary>
            /// <param name="key">The key of the field.</param>
            /// <param name="value">The value of the field.</param>
            LuaTableField(TKey key, TValue value)
                : Key(key), Value(value)
            {

            }
        };

        /// <summary>
        ///     Creates an instance of <see cref="LuaTableField" />. This function is used to automatically deduce the template parameters of the class.
        /// </summary>
        /// <param name="key">The key of the field.</param>
        /// <param name="value">The value of the field.</param>
        template <typename TKey, typename TValue>
        LuaTableField<TKey, TValue> MakeLuaTableField(TKey key, TValue value)
        {
            return LuaTableField<TKey, TValue>(key, value);
        }
    }
}