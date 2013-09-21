/**
 * @file   Vector3.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_VECTOR3_HPP
#define MW_VECTOR3_HPP

#include <Mw/Config.hpp>

#include <cmath>
#include <limits>
#include <ostream>

#include <boost/assert.hpp>
#include <boost/operators.hpp>

MW_BEGIN_NAMESPACE(math)

/**
 * @brief 3-dimensional vector
 * @tparam T Scalar type
 */
template<typename T>
class Vector3 : boost::additive<Vector3<T> >,
                boost::multiplicative<Vector3<T>, T>,
                boost::equality_comparable<Vector3<T> >
{
    /**
     * @brief Vector's horizontal component.
     */
    T _x;

    /**
     * @brief Vector's vertical component.
     */
    T _y;

    /**
     * @brief Vector's Z-component.
     */
    T _z;

public:

    // Constructors

    /**
     * @brief Default constructor.
     * @details Vector components are initialized to 0 (null vector).
     */
    Vector3()
        : _x(static_cast<T>(0)), _y(static_cast<T>(0)), _z(static_cast<T>(0))
    {}

    /**
     * @brief Constructor.
     * @details Construct a vector with given components.
     * @param x Horizontal component.
     * @param y Vertical component.
     * @param z Z-component.
     */
    Vector3(T x, T y, T z)
        : _x(x), _y(y), _z(z)
    {}

    /**
     * @brief Copy constructor.
     * @param vec Vector to copy.
     */
    template <typename U>
    Vector3(const Vector3<U> & vec)
        : _x(vec.getX()), _y(vec.getY()), _z(vec.getZ())
    {}


    // Getters / setters

    /**
     * @brief Check if the vector is null.
     * @details A vector is null if all it's components are equal to 0.
     */
    bool isNull() const
    {
        return !_x && !_y && !_z;
    }

    /**
     * @brief Get horizontal component of this vector.
     * @return Horizontal component.
     */
    T getX() const
    {
        return _x;
    }

    /**
     * @brief Get vertical component of this vector.
     * @return Vertical component.
     */
    T getY() const
    {
        return _y;
    }

    /**
     * @brief Get Z-component of this vector.
     * @return Z-component.
     */
    T getZ() const
    {
        return _z;
    }

    /**
     * @brief Set components of this vector to given values.
     * @param x Horizontal component.
     * @param y Vertical component.
     * @param z Z-component.
     */
    void set(T x, T y, T z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    /**
     * @brief Set vertical component of this vector to given value.
     * @param x Horizontal component.
     */
    void setX(T x)
    {
        _x = x;
    }

    /**
     * @brief Set horizontal component of this vector to given value.
     * @param y Vertical component.
     */
    void setY(T y)
    {
        _y = y;
    }

    /**
     * @brief Set Z-component of this vector to given value.
     * @param z Z-component.
     */
    void setZ(T z)
    {
        _z = z;
    }


    // Operations

    /**
     * @brief Compute the dot product of 2 vectors.
     * @param vec Second vector.
     * @return Dot product between this vector and @c vec.
     */
    T dot(const Vector3 & vec) const
    {
        return _x * vec._x + _y * vec._y + _z * vec._z;
    }

    Vector3 & operator += (const Vector3 & vec)
    {
        _x += vec._x;
        _y += vec._y;
        _z += vec._z;
        return *this;
    }

    Vector3 & operator -= (const Vector3 & vec)
    {
        _x -= vec._x;
        _y -= vec._y;
        _z -= vec._z;
        return *this;
    }

    /**
     * @brief Get the inverse of this vector.
     * @return Invert of this vector.
     */
    Vector3 operator - () const
    {
        return Vector3(- _x, - _y, - _z);
    }

    Vector3 & operator *= (T f)
    {
        _x *= f;
        _y *= f;
        _z *= f;
        return *this;
    }

    Vector3 & operator /= (T f)
    {
        BOOST_ASSERT(f);

        _x /= f;
        _y /= f;
        _z /= f;
        return *this;
    }

    bool operator == (const Vector3 & vec) const
    {
        return (std::fabs(_x - vec._x) <= std::numeric_limits<T>::epsilon()
             && std::fabs(_y - vec._y) <= std::numeric_limits<T>::epsilon()
             && std::fabs(_z - vec._z) <= std::numeric_limits<T>::epsilon());
    }


    // Computations

    /**
     * @brief Compute the length of this vector.
     * @return Length of this vector.
     */
    T getLength() const
    {
        return std::sqrt(_x * _x + _y * _y + _z * _z);
    }

    /**
     * @brief Get a normalization of this vector.
     * @return Normalized copy of this vector.
     */
    Vector3 getNormalization() const
    {
        BOOST_ASSERT(!isNull());

        T l = getLength();
        return Vector3(_x/l, _y/l, _z/l);
    }

    /**
     * @brief Normalize this vector.
     */
    void normalize()
    {
        BOOST_ASSERT(!isNull());

        T l = getLength();
        _x /= l;
        _y /= l;
        _z /= l;
    }

    /**
     * @brief Get a projection of this vector on given vector.
     * @param vec Vector to project this vector on.
     * @return Projection of this vector on @c vec.
     */
    Vector3 getProjection(const Vector3 & vec) const
    {
        BOOST_ASSERT(!vec.isNull());

        float prod = vec.getLength();
        prod *= prod;
        prod = dot(vec) / prod;
        // prod = dotProduct / len ^ 2

        return Vector3(prod * vec._x, prod * vec._y, prod * vec._z); // TODO check
    }

    /**
     * @brief Project this vector on given vector.
     * @param vec Vector to project this vector on.
     */
    void project(const Vector3 & vec)
    {
        BOOST_ASSERT(!vec.isNull());

        float prod = vec.getLength();
        prod *= prod;
        prod = dot(vec) / prod;
        // prod = dotProduct / len ^ 2

        _x = prod * vec._x;
        _y = prod * vec._y; // TODO check
        _z = prod * vec._z;
    }

    /**
     * @brief Get the scalar projection of this vector on given vector.
     * @param vec Vector to project this vector on.
     * @return Scalar projection of this vector on @c vec.
     */
    T getScalarProjection(const Vector3 & vec) const
    {
        return dot(vec.getNormalization());
    }

};
// class Vector3


/**
 * @brief Stream insertion operator overload.
 * @param ostr Output stream.
 * @param vec Vector to insert into the stream.
 * @return @c ostr Output stream.
 */
template <typename T>
std::ostream & operator << (std::ostream & ostr, const Vector3<T> & vec)
{
    return ostr << "Vector3[" << vec.getX() << ", " << vec.getY() << ", "
                << vec.getZ() << "]";
}

MW_END_NAMESPACE(math)

#endif // MW_VECTOR3_HPP
