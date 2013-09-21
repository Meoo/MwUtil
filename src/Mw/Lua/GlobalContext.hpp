/**
 * @file   GlobalContext.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_GLOBALCONTEXT_HPP
#define MW_GLOBALCONTEXT_HPP

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
class GlobalContext : boost::noncopyable
{
    /**
     * @brief Lua state pointer.
     */
    lua_State * _state;

public:

    // Constructors

    /**
     * @brief Create a Lua context from a Lua state.
     * @param state Lua state.
     */
    explicit GlobalContext(lua_State * state)
        : _state(state)
    {
        BOOST_ASSERT(state);
    }

    /**
     * @brief Create a Lua context from a Lua State.
     * @param state Lua State.
     */
    explicit GlobalContext(State & state)
        : _state(state.getState())
    {
        BOOST_ASSERT(state.isOpen());
    }


    // Functions

    /**
     * @brief Push @c nil onto the stack.
     */
    void push()
    {
        lua_pushnil(_state);
    }

    /**
     * @brief Push an integer @a i onto the stack.
     * @param i Integer value.
     */
    void push(lua_Integer i)
    {
        lua_pushinteger(_state, i);
    }

    /**
     * @brief Push a number @a n onto the stack.
     * @param n Number (floating point).
     */
    void push(lua_Number n)
    {
        lua_pushnumber(_state, n);
    }

    /**
     * @brief Push a boolean @a b onto the stack.
     * @param b Boolean.
     */
    void push(bool b)
    {
        lua_pushboolean(_state, b);
    }

    /**
     * @brief Push a string @a str onto the stack.
     * @param str String.
     */
    void push(const std::string & str)
    {
        lua_pushlstring(_state, str.c_str(), str.size());
    }

    /**
     * @brief Push a string @a str onto the stack.
     * @param str Null terminated string.
     */
    void push(const char * str)
    {
        lua_pushstring(_state, str);
    }

    /**
     * @brief Push a string @a str of length @a len.
     * @param str String.
     * @param len Length of the string.
     */
    void push(const char * str, size_t len)
    {
        lua_pushlstring(_state, str, len);
    }

    /**
     * @brief Push a character @a ch onto the stack.
     * @param ch Character.
     */
    void push(char ch)
    {
        lua_pushlstring(_state, &ch, 1u);
    }

    /**
     * @brief Push a pointer @a ptr onto the stack.
     * @param ptr Pointer.
     */
    void push(void * ptr)
    {
        lua_pushlightuserdata(_state, ptr);
    }

    /**
     * @brief Pop @a n elements from the stack.
     * @param n Number of elements to pop from the stack.
     */
    void pop(int n = 1)
    {
        lua_pop(_state, n);
    }

    /**
     * @brief Ensures that there are at least @a extra free stack slots
     *        in the stack.
     * @param extra Number of free slots.
     */
    void checkStack(int extra)
    {
        if (!lua_checkstack(_state, extra))
            throw std::runtime_error("Mw.Lua.GlobalContext: Unable to extend the stack");
    }

    /**
     * @brief Concat @a n values at the top of the stack.
     * @param n Number of values to concat.
     */
    void concat(int n)
    {
        lua_concat(_state, n);
    }

    /**
     * @brief Create a new table and push it onto the stack.
     * @param narr Hint for how many elements the table will have as a
     *             sequence.
     * @param nrec Hint for how many other elements the table will have.
     */
    void newTable(int narr = 0, int nrec = 0)
    {
        lua_createtable(_state, narr, nrec);
    }

};
// class GlobalContext

MW_END_NAMESPACE(lua)

#endif // MW_GLOBALCONTEXT_HPP
