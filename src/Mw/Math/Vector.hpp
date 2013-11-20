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

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

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
    BOOST_STATIC_ASSERT_MSG(N > 0, "Mw.Math.Vector: Invalid template number of components");

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
        : _components(static_cast<T>(0))
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
            set(i, vec.get(i));
    }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * Initializer list constructor.
     *
     * @param list Initializer list.
     */
    explicit Vector(const std::initializer_list<T> & list)
    {
        BOOST_ASSERT_MSG(list.size() == N, "Mw.Math.Vector: Invalid initializer list size");

        unsigned i = 0;
        for (T v : list)
            set(i++, v);
    }
#endif


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
            if (get(i) != static_cast<T>(0))
                return false;

        return true;
    }

    /**
     * Get a component.
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
            sum += get(i) * vec.get(i);

        return sum;
    }

    /**
     * Compute the cross product of 2 vectors.
     *
     * It can be used to get the right hand normal to two vectors.
     *
     * @note A x B == -B x A
     *
     * @param vec Second vector.
     * @return Cross product of this x vec.
     *
     * @note Only defined on 3-dimensional vectors.
     */
    template<unsigned M>
    typename boost::enable_if_c<((N == 3) && (M == 3)), Vector>::type
    cross(const Vector<T, M> & vec) const
    {
        Vector t;
        t.set(0, get(1) * vec.get(2) - get(2) * vec.get(1));
        t.set(1, get(2) * vec.get(0) - get(0) * vec.get(2));
        t.set(2, get(0) * vec.get(1) - get(1) * vec.get(0));
        return t;
    }

    /**
     * Affectation operator.
     *
     * @param vec
     * @return
     */
    Vector & operator = (const Vector & vec)
    {
        for (unsigned i = 0; i < N; ++i)
            set(i, vec.get(i));

        return *this;
    }

    /**
     * Addition operator.
     *
     * @param vec
     * @return
     */
    Vector & operator += (const Vector & vec)
    {
        for (unsigned i = 0; i < N; ++i)
            set(i, get(i) + vec.get(i));

        return *this;
    }

    /**
     * Substraction operator.
     *
     * @param vec
     * @return
     */
    Vector & operator -= (const Vector & vec)
    {
        for (unsigned i = 0; i < N; ++i)
            set(i, get(i) - vec.get(i));

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
            tmp.set(i, -get(i));

        return tmp;
    }

    /**
     * Multiplication operator.
     *
     * @param factor Scalar factor.
     * @return
     */
    Vector & operator *= (T factor)
    {
        for (unsigned i = 0; i < N; ++i)
            set(i, get(i) * factor);

        return *this;
    }

    /**
     * Division operator.
     *
     * @param divisor Scalar divisor.
     * @return
     * @throw std::runtime_exception Division by zero
     */
    Vector & operator /= (T divisor)
    {
        if (divisor == static_cast<T>(0))
            throw std::domain_error("Mw.Math.Vector: Division by zero");

        for (unsigned i = 0; i < N; ++i)
            set(i, get(i) / divisor);

        return *this;
    }

    /**
     * Equality comparator.
     *
     * @param vec
     * @return
     */
    bool operator == (const Vector & vec) const
    {
        for (unsigned i = 0; i < N; ++i)
            // TODO Should the equal operation be strict?
            if (std::abs(get(i) - vec.get(i)) > std::numeric_limits<T>::epsilon())
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
            len += get(i)^2;

        return std::sqrt(len);
    }

};
// class Vector


/**
 * Compute the projection of the first vector on the second vector.
 *
 * @param first Vector to be projected.
 * @param second
 * @return Projection of first vector on second.
 */
template<typename T, unsigned N>
Vector<T, N> project(const Vector<T, N> & first, const Vector<T, N> & second)
{
    BOOST_ASSERT(!second.isNull());

    if (first.isNull())
        return Vector<T, N>();

    // prod = dot(A, B) / B.length ^ 2
    T prod = static_cast<T>(0);
    for (unsigned i = 0; i < N; ++i)
        prod += second.get(i)^2;

    prod = first.dot(second) / prod;

    Vector<T, N> t;
    for (unsigned i = 0; i < N; ++i)
        t.set(i, second.get(i) * prod);
    return t;
}

/**
 * Compute the scalar projection of this vector on given vector.
 *
 * @param first Vector to be projected.
 * @param second
 * @return Scalar projection of first vector on second.
 */
template<typename T, unsigned N>
T scalarProject(const Vector<T, N> & first, const Vector<T, N> & second)
{
    return first.dot(second.getNormalization());
}

/**
 * Normalize a vector.
 *
 * @param vector Vector to be normalized.
 * @return Normalized vector.
 */
template<typename T, unsigned N>
Vector<T, N> normalize(const Vector<T, N> & vector)
{
    if (vector.isNull())
        throw std::domain_error("Mw.Math.Vector: Normalization not defined for null vectors");

    T len = vector.getLength();

    Vector<T, N> t;
    for (unsigned i = 0; i < N; ++i)
        t.set(i, vector.get(i) / len); // TODO Use fast invert sqrt? Precision loss...
    return t;
}

/**
 * Stream insertion operator overload.
 *
 * @param ostr Output stream.
 * @param vec Vector to insert into the stream.
 * @return @c ostr Output stream.
 */
template <typename T, unsigned N>
std::ostream & operator << (std::ostream & ostr, const Vector<T, N> & vec)
{
    ostr << "Vector<" << N << ">[" << vec.get(0);

    for (unsigned i = 0; i < N; ++i)
        ostr << ", " << vec.get(i);

    return ostr << "]";
}

MW_END_NAMESPACE(math)

#endif // MW_VECTOR_HPP
