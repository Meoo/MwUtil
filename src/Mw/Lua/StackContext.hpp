/**
 * @file   StackContext.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_STACKCONTEXT_HPP
#define MW_STACKCONTEXT_HPP

#include <Mw/Config.hpp>

#include <Mw/Lua/State.hpp>

#include <string>

#include <lua.hpp>

#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>

MW_BEGIN_NAMESPACE(lua)

/**
 * @brief
 */
class StackContext
{
    /**
     * @brief Lua state pointer.
     */
    lua_State * _state;

    /**
     * @brief Initial stack size.
     */
    int _top;

public:

    // Constructors

    /**
     * @brief Create a Lua context from a Lua state.
     * @param state Lua state.
     */
    explicit StackContext(lua_State * state)
        : _state(state)
    {
        BOOST_ASSERT(state);

        _top = lua_gettop(_state);
    }

    /**
     * @brief Create a Lua context from a Lua State.
     * @param state Lua State.
     */
    explicit StackContext(State & state)
        : _state(state.getState())
    {
        BOOST_ASSERT(state.isOpen());

        _top = lua_gettop(_state);
    }


    /**
     * @brief Clean the stack on destruction.
     */
    ~StackContext()
    {
        clean();
    }


    // Functions

    /**
     * @brief Restore the stack to its initial size.
     */
    void clean()
    {
        lua_settop(_state, _top);
    }

};
// class StackContext

MW_END_NAMESPACE(lua)

#endif // MW_STACKCONTEXT_HPP
