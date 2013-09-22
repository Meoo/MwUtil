/**
 * @file   Bounds2.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_BOUNDS2_HPP
#define MW_BOUNDS2_HPP

#include <Mw/Config.hpp>

#include <Mw/Math/Vector2.hpp>

MW_BEGIN_NAMESPACE(math)

/**
 * 2-dimensional bounds in the space.
 *
 * @tparam T Scalar type.
 */
template<typename T>
class Bounds2
{
    typedef Vector2<T> Vector;

    /**
     * Upper limit of the bounds.
     */
    Vector _upper_limit;

    /**
     * Lower limit of the bounds.
     */
    Vector _lower_limit;

public:
    /**
     * Default constructor.
     */
    Bounds2()
    {}

    /**
     * Copy constructor.
     *
     * @param vec Vector to copy.
     */
    template <typename U>
    Bounds2(const Bounds2<U> & bounds)
        : _upper_limit(bounds.getUpperLimit()), _lower_limit(bounds.getLowerLimit())
    {}

    bool isEmpty() const
    {
        return _upper_limit.getX() <= _lower_limit.getX()
            || _upper_limit.getY() <= _lower_limit.getY();
    }

    const Vector & getUpperLimit() const
    {
        return _upper_limit;
    }

    const Vector & getLowerLimit() const
    {
        return _lower_limit;
    }

    void set(const Vector & first, const Vector & second)
    {
        if (first.getX() > second.getX())
        {
            _upper_limit.setX(first.getX());
            _lower_limit.setX(second.getX());
        }
        else
        {
            _upper_limit.setX(second.getX());
            _lower_limit.setX(first.getX());
        }

        if (first.getY() > second.getY())
        {
            _upper_limit.setY(first.getY());
            _lower_limit.setY(second.getY());
        }
        else
        {
            _upper_limit.setY(second.getY());
            _lower_limit.setY(first.getY());
        }
    }

    void setUpperLimit(const Vector & upper_limit)
    {
        _upper_limit = upper_limit;
    }

    void setLowerLimit(const Vector & lower_limit)
    {
        _lower_limit = lower_limit;
    }

    template <typename U>
    void join(const Vector2<U> & vec)
    {
        if (vec.getX() > _upper_limit.getX())
            _upper_limit.setX(vec.getX());

        if (vec.getY() > _upper_limit.getY())
            _upper_limit.setY(vec.getY());

        if (vec.getX() < _lower_limit.getX())
            _lower_limit.setX(vec.getX());

        if (vec.getY() < _lower_limit.getY())
            _lower_limit.setY(vec.getY());
    }

    template <typename U>
    void join(const Bounds2<U> & bounds)
    {
        join(bounds.getUpperLimit());
        join(bounds.getLowerLimit());
    }

    template <typename U>
    void isInside(const Vector2<U> & vec) const
    {
        return vec.getX() <= _upper_limit.getX()
            && vec.getY() <= _upper_limit.getY()
            && vec.getX() >= _lower_limit.getX()
            && vec.getY() >= _lower_limit.getY();
    }

    template <typename U>
    void isInside(const Bounds2<U> & bounds) const
    {
        return bounds.getUpperLimit().getX() <= _upper_limit.getX()
            && bounds.getUpperLimit().getY() <= _upper_limit.getY()
            && bounds.getLowerLimit().getX() >= _lower_limit.getX()
            && bounds.getLowerLimit().getY() >= _lower_limit.getY();
    }

};
// class Bounds2


/**
 * @brief Stream insertion operator overload.
 * @param ostr Output stream.
 * @param bnd Bounds to insert into the stream.
 * @return @c ostr Output stream.
 */
template <typename T>
std::ostream & operator << (std::ostream & ostr, const Bounds2<T> & bnd)
{
    return ostr << "Bounds2[" << bnd.getLowerLimit() << ", " << bnd.getUpperLimit() << "]";
}

MW_END_NAMESPACE(math)

#endif // MW_BOUNDS2_HPP
