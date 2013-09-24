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
     * Constructor.
     *
     * Create the bounds from two points.
     * If the two points are equals, the resulting bounds will be empty.
     *
     * @param first First point.
     * @param second Second point.
     */
    Bounds2(const Vector & first, const Vector & second)
    {
        set(first, second);
    }

    /**
     * Copy constructor.
     *
     * @param bounds Bounds to copy.
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

    /**
     * Get the upper limit of this bounds.
     *
     * @return Upper limit of this bounds.
     */
    const Vector & getUpperLimit() const
    {
        return _upper_limit;
    }

    /**
     * Get the lower limit of this bounds.
     *
     * @return Lower limit of this bounds.
     */
    const Vector & getLowerLimit() const
    {
        return _lower_limit;
    }

    /**
     * Reset the bounds using two points.
     *
     * If the two points are equals, the resulting bounds will be empty.
     *
     * @param first First point.
     * @param second Second point.
     */
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

    /**
     * Change the upper limit of the bounds.
     *
     * If the value is inferior to the lower limit, the bounds will be empty.
     *
     * @param upper_limit New upper limit of the bounds.
     */
    void setUpperLimit(const Vector & upper_limit)
    {
        _upper_limit = upper_limit;
    }

    /**
     * Change the lower limit of the bounds.
     *
     * If the value is superior to the upper limit, the bounds will be empty.
     *
     * @param lower_limit New lower limit of the bounds.
     */
    void setLowerLimit(const Vector & lower_limit)
    {
        _lower_limit = lower_limit;
    }

    /**
     * Expand the bounds to include a point.
     *
     * @param vec Point to include in this bounds.
     */
    template <typename U>
    void include(const Vector & vec)
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

    /**
     * Expand the bounds to include another bounds.
     *
     * @param bounds Other bounds to include in this bounds.
     */
    template <typename U>
    void include(const Bounds2<U> & bounds)
    {
        join(bounds.getUpperLimit());
        join(bounds.getLowerLimit());
    }

    /**
     * Reduce the size of this bounds to fit into given bounds.
     *
     * If the two bounds does not intersect, this object becomes empty.
     *
     * @param bounds Other bounds for this bounds to be included into.
     */
    template <typename U>
    void intersect(const Bounds2<U> & bounds)
    {
        const Vector2<U> & upper = bounds.getUpperLimit();
        const Vector2<U> & lower = bounds.getLowerLimit();

        if (upper.getX() < _upper_limit.getX())
            _upper_limit.setX(upper.getX());

        if (upper.getY() < _upper_limit.getY())
            _upper_limit.setY(upper.getY());

        if (lower.getX() > _lower_limit.getX())
            _lower_limit.setX(lower.getX());

        if (lower.getY() > _lower_limit.getY())
            _lower_limit.setY(lower.getY());
    }

    /**
     * Check if a point is inside this bounds.
     *
     * @param vec Point to check.
     * @return @c true if the point is inside the bounds.
     */
    template <typename U>
    bool isInside(const Vector & vec) const
    {
        return vec.getX() <= _upper_limit.getX()
            && vec.getY() <= _upper_limit.getY()
            && vec.getX() >= _lower_limit.getX()
            && vec.getY() >= _lower_limit.getY();
    }

    /**
     * Check if another bounds is included inside this bounds.
     *
     * @param bounds Other bounds to check.
     * @return @c true if the bounds are included in this bounds.
     */
    template <typename U>
    bool isInside(const Bounds2<U> & bounds) const
    {
        return bounds.getUpperLimit().getX() <= _upper_limit.getX()
            && bounds.getUpperLimit().getY() <= _upper_limit.getY()
            && bounds.getLowerLimit().getX() >= _lower_limit.getX()
            && bounds.getLowerLimit().getY() >= _lower_limit.getY();
    }

};
// class Bounds2


/**
 * Stream insertion operator overload.
 *
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
