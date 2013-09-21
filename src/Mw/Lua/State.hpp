/**
 * @file   State.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_STATE_HPP
#define MW_STATE_HPP

#include <Mw/Config.hpp>

#include <stdexcept>

#include <lua.hpp>

#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>

MW_BEGIN_NAMESPACE(lua)

/**
 * @brief
 */
class State : boost::noncopyable
{
    /**
     * @brief Lua state pointer.
     */
    lua_State * _state;

public:

    // Constructors

    State()
        : _state(NULL)
    {}

    /**
     * @brief Close the Lua state on destruction.
     */
    ~State()
    {
        if (isOpen()) close();
    }


    // Functions

    /**
     * @brief Open a new Lua state.
     * @param f
     * @param ud
     * @pre The state must be closed.
     * @throw runtime_error Memory allocation failed.
     */
    void open(lua_Alloc f = NULL, void *ud = NULL)
    {
        BOOST_ASSERT(isClosed());

        _state = lua_newstate(f, ud);

        if (!_state)
            throw std::runtime_error("Mw.Lua.State: Allocation failed");
    }

    /**
     * @brief Close the Lua state.
     * @pre The state must be open.
     */
    void close()
    {
        BOOST_ASSERT(isOpen());

        lua_close(_state);
        _state = NULL;
    }


    // Getters / setters

    /**
     * @brief Check if the Lua state is open.
     * @return @c true if the state is open, @c false otherwise.
     */
    bool isOpen()
    {
        return _state;
    }

    /**
     * @brief Check if the Lua state is closed.
     * @return @c true if the state is closed, @c false otherwise.
     */
    bool isClosed()
    {
        return !_state;
    }

    /**
     * @brief Get a pointer to the underlying @c lua_State.
     * @return A pointer to the @c lua_State, or @c NULL.
     */
    lua_State * getState()
    {
        return _state;
    }

    /**
     * @brief Get the status of the state.
     * @return Either @c LUA_OK, @c LUA_YIELD or an error code.
     */
    int getStatus()
    {
        BOOST_ASSERT(isOpen());

        return lua_status(_state);
    }

    /**
     * @brief Get the allocator function.
     * @param ud
     * @return
     * @pre The state must be open.
     */
    lua_Alloc getAlloc(void ** ud = NULL)
    {
        BOOST_ASSERT(isOpen());

        return lua_getallocf(_state, ud);
    }

    /**
     * @brief Set the allocator function.
     * @param f
     * @param ud
     * @pre The state must be open.
     */
    void setAlloc(lua_Alloc f, void * ud = NULL)
    {
        BOOST_ASSERT(isOpen());

        lua_setallocf(_state, f, ud);
    }

};
// class State

MW_END_NAMESPACE(lua)

#endif // MW_STATE_HPP
