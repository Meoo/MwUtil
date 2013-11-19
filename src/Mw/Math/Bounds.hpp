/**
 * @file   Bounds.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_BOUNDS_HPP
#define MW_BOUNDS_HPP

#include <Mw/Config.hpp>

#include <Mw/Math/Vector.hpp>

MW_BEGIN_NAMESPACE(math)

/**
 * Bounds in the space.
 *
 * @tparam T Scalar type.
 * @tparam N Dimension (number of components).
 * @tparam V Vectorial type.
 */
template<typename T, unsigned N, class V = Vector<T, N> >
class Bounds
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
    Bounds()
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
    Bounds(const V & first, const V & second)
    {
        set(first, second);
    }

    /**
     * Copy constructor.
     *
     * @param bounds Bounds to copy.
     */
    template <typename U, class W>
    Bounds(const Bounds<U, N, W> & bounds)
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
        for (unsigned i = 0; i < N; ++i)
            if (getUpperLimit().get(i) <= getLowerLimit().get(i))
                return true;

        return false;
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
        for (unsigned i = 0; i < N; ++i)
        {
            if (first.get(i) > second.get(i))
            {
                _upper_limit.set(i, first.get(i));
                _lower_limit.set(i, second.get(i));
            }
            else
            {
                _upper_limit.set(i, second.get(i));
                _lower_limit.set(i, first.get(i));
            }
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
        for (unsigned i = 0; i < N; ++i)
        {
            if (vec.get(i) > getUpperLimit().get(i))
                _upper_limit.set(i, vec.get(i));

            if (vec.get(i) < getLowerLimit().get(i))
                _lower_limit.set(i, vec.get(i));
        }
    }

    /**
     * Expand the bounds to include another bounds.
     *
     * @param bounds Other bounds to include in this bounds.
     */
    void include(const Bounds & bounds)
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
    void intersect(const Bounds & bounds)
    {
        const V & upper = bounds.getUpperLimit();
        const V & lower = bounds.getLowerLimit();

        for (unsigned i = 0; i < N; ++i)
        {
            if (upper.get(i) < getUpperLimit().get(i))
                _upper_limit.set(i, upper.get(i));

            if (lower.get(i) > getLowerLimit().get(i))
                _lower_limit.set(i, lower.get(i));
        }
    }

    /**
     * Compute the intersection between this bounds and given bounds.
     *
     * @param bounds Other bounds to compute the intersection with.
     * @return
     */
    Bounds getIntersection(const Bounds & bounds)
    {
        Bounds copy(*this);
        copy.intersect(bounds);
        return copy;
    }

    /**
     * Check if a point is inside this bounds.
     *
     * @param vec Point to check.
     * @return @c true if the point is inside the bounds.
     */
    bool hasPointInside(const V & vec) const
    {
        for (unsigned i = 0; i < N; ++i)
        {
            if (vec.get(i) > getUpperLimit().get(i)
             || vec.get(i) < getLowerLimit().get(i))
                return false;
        }

        return true;
    }

    /**
     * Check if another bounds is included inside this bounds.
     *
     * @param bounds Other bounds to check.
     * @return @c true if the bounds are included in this bounds.
     */
    bool hasBoundsInside(const Bounds & bounds) const
    {
        for (unsigned i = 0; i < N; ++i)
        {
            if (bounds.getUpperLimit().get(i) > getUpperLimit().get(i)
             && bounds.getLowerLimit().get(i) < getLowerLimit().get(i))
                return false;
        }

        return true;
    }

    /**
     * Check if another bounds is intersecting with this bounds.
     *
     * @param bounds Other bounds to check the intersection with.
     * @return
     */
    bool isIntersecting(const Bounds & bounds)
    {
        return !getIntersection(bounds).isEmpty();
    }

};
// class Bounds


/**
 * Stream insertion operator overload.
 *
 * @param ostr Output stream.
 * @param bnd Bounds to insert into the stream.
 * @return @c ostr Output stream.
 */
template <typename T, unsigned N, class V>
std::ostream & operator << (std::ostream & ostr, const Bounds<T, N, V> & bnd)
{
    return ostr << "Bounds<" << N << ">[" << bnd.getLowerLimit() << ", " << bnd.getUpperLimit() << "]";
}

MW_END_NAMESPACE(math)

#endif // MW_BOUNDS_HPP
