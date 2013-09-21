/**
 * @file   StackValue.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_STACKVALUE_HPP
#define MW_STACKVALUE_HPP

#include <Mw/Config.hpp>

#include <Mw/Lua/State.hpp>

#include <string>

#include <lua.hpp>

#include <boost/assert.hpp>

MW_BEGIN_NAMESPACE(lua)

/**
 * @brief
 */
class StackValue
{
    /**
     * @brief Lua state pointer.
     */
    lua_State * _state;

    /**
     * @brief Value's absolute index on the stack.
     */
    int _idx;

public:

    // Constructors

    /**
     * @brief Create a Lua context from a Lua state.
     * @param state Lua state.
     * @param idx Value's index on the stack.
     */
    explicit StackValue(lua_State * state, int idx)
        : _state(state)
    {
        BOOST_ASSERT(state);

        _idx = lua_absindex(_state, idx);
    }

    /**
     * @brief Create a Lua context from a Lua State.
     * @param state Lua State.
     * @param idx Value's index on the stack.
     */
    explicit StackValue(State & state, int idx)
        : _state(state.getState())
    {
        BOOST_ASSERT(state.isOpen());

        _idx = lua_absindex(_state, idx);
    }


    // Getters / Setters

    bool isBoolean()
    {
        return lua_isboolean(_state, _idx);
    }

    bool isCFunction()
    {
        return lua_iscfunction(_state, _idx);
    }

    bool isFunction()
    {
        return lua_isfunction(_state, _idx);
    }

    bool isLightUserData()
    {
        return lua_islightuserdata(_state, _idx);
    }

    bool isNil()
    {
        return lua_isnil(_state, _idx);
    }

    bool isNone()
    {
        return lua_isnone(_state, _idx);
    }

    bool isNoneOrNil()
    {
        return lua_isnoneornil(_state, _idx);
    }

    bool isNumber()
    {
        return lua_isnumber(_state, _idx);
    }

    bool isString()
    {
        return lua_isstring(_state, _idx);
    }

    bool isTable()
    {
        return lua_istable(_state, _idx);
    }

    bool isThread()
    {
        return lua_isthread(_state, _idx);
    }

    bool isUserData()
    {
        return lua_isuserdata(_state, _idx);
    }

};
// class StackValue

MW_END_NAMESPACE(lua)

#endif // MW_STACKVALUE_HPP
