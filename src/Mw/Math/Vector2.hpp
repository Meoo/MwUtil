/**
 * @file   Vector2.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_VECTOR2_HPP
#define MW_VECTOR2_HPP

#include <Mw/Config.hpp>

#include <cmath>
#include <limits>
#include <ostream>

#include <boost/assert.hpp>
#include <boost/operators.hpp>

MW_BEGIN_NAMESPACE(math)

/**
 * @brief 2-dimensional vector.
 * @tparam T Scalar type.
 */
template<typename T>
class Vector2 : boost::additive<Vector2<T> >,
                boost::multiplicative<Vector2<T>, T>,
                boost::equality_comparable<Vector2<T> >
{
    /**
     * @brief Vector's horizontal component.
     */
    T _x;

    /**
     * @brief Vector's vertical component.
     */
    T _y;

public:

    // Constructors

    /**
     * @brief Default constructor.
     * @details Vector components are initialized to 0 (null vector).
     */
    Vector2()
        : _x(static_cast<T>(0)), _y(static_cast<T>(0))
    {}

    /**
     * @brief Constructor.
     * @details Construct a vector with given components.
     * @param x Horizontal component.
     * @param y Vertical component.
     */
    Vector2(T x, T y)
        : _x(x), _y(y)
    {}

    /**
     * @brief Copy constructor.
     * @param vec Vector to copy.
     */
    template <typename U>
    Vector2(const Vector2<U> & vec)
        : _x(vec.getX()), _y(vec.getY())
    {}


    // Getters / setters

    /**
     * @brief Check if the vector is null.
     * @details A vector is null if all it's components are equal to 0.
     */
    bool isNull() const
    {
        return !_x && !_y;
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
     * @brief Set components of this vector to given values.
     * @param x Horizontal component.
     * @param y Vertical component.
     */
    void set(T x, T y)
    {
        _x = x;
        _y = y;
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


    // Operations

    /**
     * @brief Compute the dot product of 2 vectors.
     * @param vec Second vector.
     * @return Dot product between this vector and @c vec.
     */
    T dot(const Vector2 & vec) const
    {
        return _x * vec._x + _y * vec._y;
    }

    Vector2 & operator += (const Vector2 & vec)
    {
        _x += vec._x;
        _y += vec._y;
        return *this;
    }

    Vector2 & operator -= (const Vector2 & vec)
    {
        _x -= vec._x;
        _y -= vec._y;
        return *this;
    }

    /**
     * @brief Get the inverse of this vector.
     * @return Invert of this vector.
     */
    Vector2 operator - () const
    {
        return Vector2(- _x, - _y);
    }

    Vector2 & operator *= (T f)
    {
        _x *= f;
        _y *= f;
        return *this;
    }

    Vector2 & operator /= (T f)
    {
        // TODO DBZ!
        _x /= f;
        _y /= f;
        return *this;
    }

    bool operator == (const Vector2 & vec) const
    {
        return (std::fabs(_x - vec._x) <= std::numeric_limits<T>::epsilon()
             && std::fabs(_y - vec._y) <= std::numeric_limits<T>::epsilon());
    }


    // Computations

    /**
     * @brief Compute the length of this vector.
     * @return Length of this vector.
     */
    T getLength() const
    {
        return std::sqrt(_x * _x + _y * _y);
    }

    /**
     * @brief Get a rotation of this vector by a given angle.
     * @param angle Angle in radians.
     * @return Rotated copy of this vector.
     */
    Vector2 getRotation(float angle) const
    {
        if (!angle) return *this;

        float cos = std::cos(angle);
        float sin = std::sin(angle);

        Vector2 t;
        t._x = cos * _x - sin * _y;
        t._y = sin * _x + cos * _y;

        return t;
    }

    /**
     * @brief Rotate this vector by a given angle.
     * @param angle Angle in radians.
     */
    void rotate(float angle)
    {
        if (!angle) return;

        float cos = std::cos(angle);
        float sin = std::sin(angle);

        T t = cos * _x - sin * _y;
        _y = sin * _x + cos * _y;
        _x = t;
    }

    /**
     * @brief Get a normalization of this vector.
     * @return Normalized copy of this vector.
     */
    Vector2 getNormalization() const
    {
        BOOST_ASSERT(!isNull());

        T l = getLength();
        return Vector2(_x/l, _y/l);
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
    }

    /**
     * @brief Get a projection of this vector on given vector.
     * @param vec Vector to project this vector on.
     * @return Projection of this vector on @c vec.
     */
    Vector2 getProjection(const Vector2 & vec) const
    {
        BOOST_ASSERT(!vec.isNull());

        float prod = vec.getLength();
        prod *= prod;
        prod = dot(vec) / prod;
        // prod = dotProduct / len ^ 2

        return Vector2(prod * vec._x, prod * vec._y);
    }

    /**
     * @brief Project this vector on given vector.
     * @param vec Vector to project this vector on.
     */
    void project(const Vector2 & vec)
    {
        BOOST_ASSERT(!vec.isNull());

        float prod = vec.getLength();
        prod *= prod;
        prod = dot(vec) / prod;
        // prod = dotProduct / len ^ 2

        _x = prod * vec._x;
        _y = prod * vec._y;
    }

    /**
     * @brief Get the scalar projection of this vector on given vector.
     * @param vec Vector to project this vector on.
     * @return Scalar projection of this vector on @c vec.
     */
    T getScalarProjection(const Vector2 & vec) const
    {
        return dot(vec.getNormalization());
    }

    /**
     * @brief Get the left hand normal of this vector.
     * @return Left hand normal of this vector.
     */
    Vector2 getLeftHandNormal() const
    {
        return Vector2(_y, - _x);
    }

    /**
     * @brief Get the right hand normal of this vector.
     * @return Right hand normal of this vector.
     */
    Vector2 getRightHandNormal() const
    {
        return Vector2(- _y, _x);
    }

};
// class Vector2


/**
 * @brief Stream insertion operator overload.
 * @param ostr Output stream.
 * @param vec Vector to insert into the stream.
 * @return @c ostr Output stream.
 */
template <typename T>
std::ostream & operator << (std::ostream & ostr, const Vector2<T> & vec)
{
    return ostr << "Vector2[" << vec.getX() << ", " << vec.getY() << "]";
}

MW_END_NAMESPACE(math)

#endif // MW_VECTOR2_HPP
