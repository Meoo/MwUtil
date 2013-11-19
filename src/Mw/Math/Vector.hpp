/**
 * @file   Vector.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_VECTOR_HPP
#define MW_VECTOR_HPP

#include <Mw/Config.hpp>

#include <cmath>
#include <limits>
#include <ostream>
#include <stdexcept>

#include <boost/utility/enable_if.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>
#include <boost/operators.hpp>

MW_BEGIN_NAMESPACE(math)

/**
 * Generic vector.
 *
 * @tparam T Scalar type.
 * @tparam N Dimension (number of components).
 */
template<typename T, unsigned N>
class Vector : boost::additive<Vector<T, N> >,
               boost::multiplicative<Vector<T, N>, T>,
               boost::equality_comparable<Vector<T, N> >
{
    BOOST_STATIC_ASSERT_MSG(N == 0, "Invalid number of components in mw::math::Vector");

    /**
     * Vector's components.
     */
    T _components[N];

public:

    // Constructors

    /**
     * Default constructor.
     *
     * Vector components are initialized to 0 (null vector).
     */
    Vector()
        : _components({static_cast<T>(0)})
    {}

    /**
     * Copy constructor.
     *
     * @param vec Vector to copy.
     */
    template <typename U>
    Vector(const Vector<U, N> & vec)
    {
        for (unsigned i = 0; i < N; ++i)
            set<i>(vec.get<i>());
    }


    // Getters / setters

    /**
     * Check if the vector is null.
     *
     * A vector is null if all it's components are equal to 0.
     *
     * @return @c true if the vector is null.
     */
    bool isNull() const
    {
        for (unsigned i = 0; i < N; ++i)
            if (get<i>() != static_cast<T>(0))
                return false;

        return true;
    }

    /**
     * Get a component (template version).
     *
     * @tparam I Component's index.
     * @return Component at position I.
     */
    template<unsigned I>
    typename boost::enable_if<(I < N), T>::type
    get() const
    {
        return _components[I];
    }

    /**
     * Get a component (template version).
     *
     * @param index Component's index.
     * @return Component at position I.
     */
    T get(unsigned index) const
    {
        if (index >= N)
            throw std::out_of_range("Mw.Math.Vector: Out of range");

        return _components[index];
    }

    /**
     * Set a component of this vector to given value (template version).
     *
     * @tparam I Component's index.
     * @param value New value.
     */
    template<unsigned I>
    typename boost::enable_if<(I < N), void>::type
    set(T value)
    {
        _components[I] = value;
    }

    /**
     * Set a component of this vector to given value.
     *
     * @param index Component's index.
     * @param value New value.
     */
    void set(unsigned index, T value)
    {
        if (index >= N)
            throw std::out_of_range("Mw.Math.Vector: Out of range");

        _components[index] = value;
    }


    // Simple getters / setters for 2, 3 and 4 components

    /**
     * Get horizontal component of this vector.
     *
     * @return Horizontal component.
     *
     * @note Avaiable on vectors of dimension 2, 3 and 4.
     */
    typename boost::enable_if<(N >= 2 && N <= 4), T>::type
    getX() const
    {
        return get<0>;
    }

    /**
     * Set vertical component of this vector to given value.
     *
     * @param x Horizontal component.
     *
     * @note Avaiable on vectors of dimension 2, 3 and 4.
     */
    typename boost::enable_if<(N >= 2 && N <= 4), void>::type
    setX(T x)
    {
        set<0>(x);
    }

    /**
     * Get vertical component of this vector.
     *
     * @return Vertical component.
     *
     * @note Avaiable on vectors of dimension 2, 3 and 4.
     */
    typename boost::enable_if<(N >= 2 && N <= 4), T>::type
    getY() const
    {
        return get<1>;
    }

    /**
     * Set horizontal component of this vector to given value.
     *
     * @param y Vertical component.
     *
     * @note Avaiable on vectors of dimension 2, 3 and 4.
     */
    typename boost::enable_if<(N >= 2 && N <= 4), void>::type
    setY(T y)
    {
        set<1>(y);
    }

    /**
     * Get depth component of this vector.
     *
     * @return Depth component.
     *
     * @note Avaiable on vectors of dimension 3 and 4.
     */
    typename boost::enable_if<(N >= 3 && N <= 4), T>::type
    getZ() const
    {
        return get<2>;
    }

    /**
     * Set depth component of this vector to given value.
     *
     * @param z Depth component.
     *
     * @note Avaiable on vectors of dimension 3 and 4.
     */
    typename boost::enable_if<(N >= 3 && N <= 4), void>::type
    setZ(T z)
    {
        set<2>(z);
    }

    /**
     * Get w component of this vector.
     *
     * @return W component.
     *
     * @note Avaiable on vectors of dimension 4.
     */
    typename boost::enable_if<(N == 4), T>::type
    getW() const
    {
        return get<3>;
    }

    /**
     * Set w component of this vector to given value.
     *
     * @param w W component.
     *
     * @note Avaiable on vectors of dimension 4.
     */
    typename boost::enable_if<(N == 4), void>::type
    setW(T w)
    {
        set<3>(w);
    }


    // Operations

    /**
     * Compute the dot product of 2 vectors.
     *
     * @param vec Second vector.
     * @return Dot product between this vector and @c vec.
     */
    T dot(const Vector & vec) const
    {
        T sum = static_cast<T>(0);

        for (unsigned i = 0; i < N; ++i)
            sum += get<i>() * vec.get<i>();

        return sum;
    }

    Vector & operator += (const Vector & vec)
    {
        for (unsigned i = 0; i < N; ++i)
            set<i>(get<i>() + vec.get<i>());

        return *this;
    }

    Vector & operator -= (const Vector & vec)
    {
        for (unsigned i = 0; i < N; ++i)
            set<i>(get<i>() - vec.get<i>());

        return *this;
    }

    /**
     * Get the inverse of this vector.
     *
     * @return Invert of this vector.
     */
    Vector operator - () const
    {
        Vector tmp (*this);

        for (unsigned i = 0; i < N; ++i)
            tmp.set<i>(-get<i>());

        return tmp;
    }

    Vector & operator *= (T f)
    {
        for (unsigned i = 0; i < N; ++i)
            set<i>(get<i>() * f);

        return *this;
    }

    /**
     * @param f
     * @return
     * @throw std::runtime_exception Division by zero
     */
    Vector & operator /= (T f)
    {
        if (f == static_cast<T>(0))
            throw std::domain_error("Mw.Math.Vector: Division by zero");

        for (unsigned i = 0; i < N; ++i)
            set<i>(get<i>() / f);

        return *this;
    }

    // TODO Should the equal operation be strict?
    bool operator == (const Vector & vec) const
    {
        for (unsigned i = 0; i < N; ++i)
            if (std::abs(get<i>() - vec.get<i>()) > std::numeric_limits<T>::epsilon())
                return false;

        return true;
    }


    // Computations

    /**
     * Compute the length of this vector.
     *
     * @return Length of this vector.
     */
    T getLength() const
    {
        T len = static_cast<T>(0);

        for (unsigned i = 0; i < N; ++i)
            len += get<i>()^2;

        return std::sqrt(len);
    }

    /**
     * Normalize this vector.
     */
    void normalize()
    {
        if (isNull())
            throw std::domain_error("Mw.Math.Vector: Normalization not defined for null vectors");

        T len = getLength();

        for (unsigned i = 0; i < N; ++i)
            set<i>(get<i>() / len);
    }

    /**
     * Get a normalization of this vector.
     *
     * @return Normalized copy of this vector.
     */
    Vector getNormalization() const
    {
        Vector copy(*this);
        copy.normalize();
        return copy;
    }

    /**
     * Project this vector onto given vector.
     *
     * @param vec Vector to project this vector on.
     */
    void project(const Vector & vec)
    {
        BOOST_ASSERT(!vec.isNull());

        // prod = dot(A, B) / B.length ^ 2
        T prod = static_cast<T>(0);
        for (unsigned i = 0; i < N; ++i)
            prod += vec.get<i>()^2;

        prod = dot(vec) / prod;

        for (unsigned i = 0; i < N; ++i)
            set<i>(vec.get<i>() * prod);
    }

    /**
     * Get a projection of this vector on given vector.
     *
     * @param vec Vector to project this vector on.
     * @return Projection of this vector on @c vec.
     */
    Vector getProjection(const Vector & vec) const
    {
        Vector copy(*this);
        copy.project(vec);
        return copy;
    }

    /**
     * Get the scalar projection of this vector on given vector.
     *
     * @param vec Vector to project this vector on.
     * @return Scalar projection of this vector on @c vec.
     */
    T getScalarProjection(const Vector & vec) const
    {
        return dot(vec.getNormalization());
    }

};
// class Vector

template<typename T> typedef Vector<T, 2> Vector2;
template<typename T> typedef Vector<T, 3> Vector3;
template<typename T> typedef Vector<T, 4> Vector4;


/**
 * Stream insertion operator overload.
 *
 * @param ostr Output stream.
 * @param vec Vector to insert into the stream.
 * @return @c ostr Output stream.
 */
template <typename T, typename N>
std::ostream & operator << (std::ostream & ostr, const Vector<T, N> & vec)
{
    ostr << "Vector<" << N << ">[" << vec.get<0>();

    for (unsigned i = 0; i < N; ++i)
        ostr << ", " << vec.get<i>();

    return ostr << "]";
}

MW_END_NAMESPACE(math)

#endif // MW_VECTOR_HPP
