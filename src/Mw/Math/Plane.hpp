/**
 * @file   Plane.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_PLANE_HPP
#define MW_PLANE_HPP

#include <Mw/Config.hpp>

#include <Mw/Math/Vector2.hpp>
#include <Mw/Math/Vector3.hpp>

MW_BEGIN_NAMESPACE(math)

/**
 * Representation of a plane.
 *
 * @tparam T Scalar type.
 * @tparam V Vectorial type.
 */
template<typename T, class V>
class Plane
{
    /**
     * Plane's normal.
     */
    V _normal;

    /**
     * Distance from origin.
     */
    T _origin;

public:

    // Constructors

    /**
     * Constructor.
     *
     * @param normal A vector orthogonal to the plane.
     * @param point A point on the plane.
     */
    Plane(const V & normal, const V & point)
        : _normal(normal.getNormalization()),
          _origin(point.getScalarProjection(_normal))
    {}


    // Getters / setters

    /**
     * Get the plane's normal vector.
     *
     * @return Plane's normal vector.
     */
    V getNormal() const
    {
        return _normal;
    }

    /**
     * Return the shortest distance between this plane and the origin.
     *
     * @return Shortest distance between this plane and the origin.
     */
    T getDistanceFromOrigin() const
    {
        return _origin;
    }

    /**
     * Set the plane's values.
     *
     * @param normal A vector orthogonal to the plane.
     * @param point A point on the plane.
     */
    void set(const V & normal, const V & point)
    {
        _normal = normal.getNormalization();
        _origin = point.getScalarProjection(_normal);
    }

    /**
     * Check if given point is on the plane.
     *
     * @param point A point.
     * @return @c true if the point is on the plane, @c false otherwise.
     */
    bool isOn(const V & point) const
    {
        return point.getScalarProjection(_normal) == _origin;
    }

    /**
     * Check if given point is over the plane.
     *
     * @param point A point.
     * @return @c true if the point is over the plane, @c false otherwise.
     */
    bool isOver(const V & point) const
    {
        return point.getScalarProjection(_normal) > _origin;
    }

    /**
     * Check if given point is under the plane.
     *
     * @param point A point.
     * @return @c true if the point is under the plane, @c false otherwise.
     */
    bool isUnder(const V & point) const
    {
        return point.getScalarProjection(_normal) < _origin;
    }


    // Computations

    /**
     * Get the distance between this plane and given point.
     *
     * Returns 0 if the point is on the plane.
     *
     * @param point A point.
     * @return Distance between this plane and given point.
     */
    T getDistance(const V & point) const
    {
        T d = point.getScalarProjection(_normal);

        if (d > _origin) return d - _origin;
        return _origin - d;
    }

    /**
     * Get the projection of a point on this plane.
     *
     * @param point A point.
     * @return Projection of given point on this plane.
     */
    V getProjection(const V & point) const
    {
        T d = point.getScalarProjection(_normal);

        return point - _normal * d; // TODO d - origin?
    }

};
// class Plane

template<typename T> typedef Plane<T, Vector2<T> > Plane2;
template<typename T> typedef Plane<T, Vector3<T> > Plane3;

MW_END_NAMESPACE(math)

#endif // MW_PLANE_HPP
