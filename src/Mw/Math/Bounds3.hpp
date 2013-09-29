/**
 * @file   Bounds3.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_BOUNDS3_HPP
#define MW_BOUNDS3_HPP

#include <Mw/Config.hpp>

#include <Mw/Math/Vector3.hpp>

MW_BEGIN_NAMESPACE(math)

/**
 * 3-dimensional bounds in the space.
 *
 * @tparam T Scalar type.
 */
template<typename T, class V = Vector3<T> >
class Bounds3
{
    /**
     * Upper limit of the bounds.
     */
    V _upper_limit;

    /**
     * Lower limit of the bounds.
     */
    V _lower_limit;

public:

    // Constructors

    /**
     * Default constructor.
     */
    Bounds3()
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
    Bounds3(const V & first, const V & second)
    {
        set(first, second);
    }

    /**
     * Copy constructor.
     *
     * @param bounds Bounds to copy.
     */
    template <typename U, class W>
    Bounds3(const Bounds3<U, W> & bounds)
        : _upper_limit(bounds.getUpperLimit()), _lower_limit(bounds.getLowerLimit())
    {}


    // Getters / setters

    /**
     * Check if the bounds are empty.
     *
     * @return @c true if the bounds are empty.
     */
    bool isEmpty() const
    {
        return _upper_limit.getX() <= _lower_limit.getX()
            || _upper_limit.getY() <= _lower_limit.getY()
            || _upper_limit.getZ() <= _lower_limit.getZ();
    }

    /**
     * Get the upper limit of this bounds.
     *
     * @return Upper limit of this bounds.
     */
    const V & getUpperLimit() const
    {
        return _upper_limit;
    }

    /**
     * Get the lower limit of this bounds.
     *
     * @return Lower limit of this bounds.
     */
    const V & getLowerLimit() const
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
    void set(const V & first, const V & second)
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

        if (first.getZ() > second.getZ())
        {
            _upper_limit.setZ(first.getZ());
            _lower_limit.setZ(second.getZ());
        }
        else
        {
            _upper_limit.setZ(second.getZ());
            _lower_limit.setZ(first.getZ());
        }
    }

    /**
     * Change the upper limit of the bounds.
     *
     * If the value is inferior to the lower limit, the bounds will be empty.
     *
     * @param upper_limit New upper limit of the bounds.
     */
    void setUpperLimit(const V & upper_limit)
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
    void setLowerLimit(const V & lower_limit)
    {
        _lower_limit = lower_limit;
    }


    // Functions

    /**
     * Expand the bounds to include a point.
     *
     * @param vec Point to include in this bounds.
     */
    void include(const V & vec)
    {
        if (vec.getX() > _upper_limit.getX())
            _upper_limit.setX(vec.getX());

        if (vec.getY() > _upper_limit.getY())
            _upper_limit.setY(vec.getY());

        if (vec.getZ() > _upper_limit.getZ())
            _upper_limit.setZ(vec.getZ());

        if (vec.getX() < _lower_limit.getX())
            _lower_limit.setX(vec.getX());

        if (vec.getY() < _lower_limit.getY())
            _lower_limit.setY(vec.getY());

        if (vec.getZ() < _lower_limit.getZ())
            _lower_limit.setZ(vec.getZ());
    }

    /**
     * Expand the bounds to include another bounds.
     *
     * @param bounds Other bounds to include in this bounds.
     */
    void include(const Bounds3 & bounds)
    {
        include(bounds.getUpperLimit());
        include(bounds.getLowerLimit());
    }

    /**
     * Reduce the size of this bounds to fit into given bounds.
     *
     * If the two bounds does not intersect, this object becomes empty.
     *
     * @param bounds Other bounds for this bounds to be included into.
     */
    void intersect(const Bounds3 & bounds)
    {
        const V & upper = bounds.getUpperLimit();
        const V & lower = bounds.getLowerLimit();

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
     * Compute the intersection between this bounds and given bounds.
     *
     * @param bounds Other bounds to compute the intersection with.
     * @return
     */
    Bounds3 getIntersection(const Bounds3 & bounds)
    {
        Bounds3 copy(*this);
        copy.intersect(bounds);
        return copy;
    }

    /**
     * Check if a point is inside this bounds.
     *
     * @param vec Point to check.
     * @return @c true if the point is inside the bounds.
     */
    bool isInside(const V & vec) const
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
    bool isInside(const Bounds3 & bounds) const
    {
        return bounds.getUpperLimit().getX() <= _upper_limit.getX()
            && bounds.getUpperLimit().getY() <= _upper_limit.getY()
            && bounds.getUpperLimit().getZ() <= _upper_limit.getZ()
            && bounds.getLowerLimit().getX() >= _lower_limit.getX()
            && bounds.getLowerLimit().getY() >= _lower_limit.getY()
            && bounds.getLowerLimit().getZ() >= _lower_limit.getZ();
    }

};
// class Bounds3


/**
 * Stream insertion operator overload.
 *
 * @param ostr Output stream.
 * @param bnd Bounds to insert into the stream.
 * @return @c ostr Output stream.
 */
template <typename T>
std::ostream & operator << (std::ostream & ostr, const Bounds3<T> & bnd)
{
    return ostr << "Bounds3[" << bnd.getLowerLimit() << ", " << bnd.getUpperLimit() << "]";
}

MW_END_NAMESPACE(math)

#endif // MW_BOUNDS3_HPP
