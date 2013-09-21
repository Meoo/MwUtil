/**
 * @file   Rational.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_RATIONAL_HPP
#define MW_RATIONAL_HPP

#include <Mw/Config.hpp>

#include <stdexcept>
#include <ostream>

#include <boost/assert.hpp>
#include <boost/operators.hpp>

MW_BEGIN_NAMESPACE(math)

/**
 * Rational number.
 *
 * @tparam T Integer type.
 */
template<typename T>
class Rational : boost::arithmetic<Rational<T> >,
                 boost::totally_ordered<Rational<T> >
{
    /**
     * Fraction's numerator.
     */
    T _numerator;

    /**
     * Fraction's denominator.
     */
    T _denominator;

    /**
     * Compute gcd of 2 numbers.
     *
     * @param a First number.
     * @param b Second number.
     */
    static T computeGcd(T a, T b)
    {
        a = (a >= static_cast<T>(0) ? a : - a);
        b = (b >= static_cast<T>(0) ? b : - b);
        T tmp;

        while(a)
        {
            if (!b) return a;
            tmp = b;
            b = a % b;
            a = tmp;
        }
        return b;
    }

    /**
     * Normalize the fraction.
     */
    void normalize()
    {
        // No negative denominator
        if (_denominator < static_cast<T>(0))
        {
            _numerator = -_numerator;
            _denominator = -_denominator;
        }

        // Reduce fraction
        T gcd = computeGcd(_numerator, _denominator);
        _numerator /= gcd;
        _denominator /= gcd;
    }

public:

    // Constructors

    /**
     * Default constructor.
     *
     * The rational number is initialized to 0 (0/1).
     */
    Rational()
        : _numerator(static_cast<T>(0)), _denominator(static_cast<T>(1))
    {}

    /**
     * Constructor.
     *
     * @param numerator Numerator.
     * @param denominator Denominator.
     */
    explicit Rational(T numerator, T denominator = static_cast<T>(1))
        : _numerator(numerator), _denominator(denominator)
    {
        BOOST_ASSERT(denominator);

        normalize();
    }


    // Getters / setters

    /**
     * Cast rational number to any scalar type.
     *
     * @tparam U Scalar type.
     */
    template<typename U>
    operator U () const
    {
        return static_cast<U>(_numerator) / static_cast<U>(_denominator);
    }

    /**
     * Get fraction's numerator.
     *
     * @return Fraction's numerator.
     */
    T getNumerator() const
    {
        return _numerator;
    }

    /**
     * Get fraction's denominator.
     *
     * @return Fraction's denominator.
     */
    T getDenominator() const
    {
        return _denominator;
    }

    /**
     * Set fraction's values.
     *
     * @param numerator Fraction's numerator.
     * @param denominator Fraction's denominator.
     */
    void set(T numerator, T denominator)
    {
        BOOST_ASSERT(denominator);

        _numerator = numerator;
        _denominator = denominator;
        normalize();
    }

    /**
     * Set fraction's numerator.
     *
     * @param numerator Fraction's numerator.
     * @warning Using this function may lead to unexpected results as the
     *          fraction is normalized every time a value is changed.
     */
    void setNumerator(T numerator)
    {
        _numerator = numerator;
        normalize();
    }

    /**
     * Set fraction's denominator.
     *
     * @param denominator Fraction's denominator.
     * @warning Using this function may lead to unexpected results as the
     *          fraction is normalized every time a value is changed.
     */
    void setDenominator(T denominator)
    {
        BOOST_ASSERT(denominator);

        _denominator = denominator;
        normalize();
    }


    // Operations

    Rational & operator += (const Rational & rat)
    {
        T g1 = computeGcd(_denominator, rat._denominator);
        if (g1 == static_cast<T>(1))
        {
            _numerator = _numerator * rat._denominator
                       + _denominator * rat._numerator;
            _denominator = _denominator * rat._denominator;
        }
        else
        {
            T t = _numerator * (rat._denominator / g1)
                + (_denominator/g1) * rat._numerator;

            T g2 = computeGcd(t, g1);
            _numerator = t / g2;
            _denominator = (_denominator / g1) * (rat._denominator / g2);
        }
        return *this;
    }

    Rational & operator -= (const Rational & rat)
    {
        T g1 = computeGcd(_denominator, rat._denominator);
        if (g1 == static_cast<T>(1))
        {
            _numerator = _numerator * rat._denominator
                       - _denominator * rat._numerator;
            _denominator = _denominator * rat._denominator;
        }
        else
        {
            T t = _numerator * (rat._denominator / g1)
                - (_denominator/g1) * rat._numerator;

            T g2 = computeGcd(t, g1);
            _numerator = t / g2;
            _denominator = (_denominator / g1) * (rat._denominator / g2);
        }
        return *this;
    }

    Rational & operator *= (const Rational & rat)
    {
        T g1 = computeGcd(_numerator, rat._denominator);
        T g2 = computeGcd(_denominator, rat._numerator);
        _numerator = (_numerator / g1) * (rat._numerator / g2);
        _denominator = (_denominator / g2) * (rat._denominator / g1);
        return *this;
    }

    /**
     * @throw std::runtime_exception Division by zero
     */
    Rational & operator /= (const Rational & rat)
    {
        if(!rat.getNumerator())
            throw std::invalid_argument("Mw.Math.Rational: Division by zero");

        long g1 = computeGcd(_numerator, rat._numerator);
        long g2 = computeGcd(_denominator, rat._denominator);
        _numerator = (_numerator / g1) * (rat._denominator / g2);
        _denominator = (_denominator / g2) * (rat._numerator / g1);

        if (_denominator < static_cast<T>(0))
        {
            _numerator = -_numerator;
            _denominator = -_denominator;
        }
        return *this;
    }

    bool operator == (const Rational & rat) const
    {
        return (_numerator == rat._numerator)
            && (_denominator == rat._denominator);
    }

    bool operator < (const Rational & rat) const
    {
        return (_numerator * rat._denominator < _denominator * rat._numerator);
    }

};
// class Rational


/**
 * @brief Stream insertion operator overload.
 * @param ostr Output stream.
 * @param vec Rational to insert into the stream.
 * @return @c ostr Output stream.
 */
template <typename T>
std::ostream & operator << (std::ostream & ostr, const Rational<T> & rat)
{
    return ostr << rat.getNumerator() << '/' << rat.getDenominator();
}

MW_END_NAMESPACE(math)

#endif // MW_RATIONAL_HPP
