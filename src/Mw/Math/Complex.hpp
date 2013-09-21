/**
 * @file   Complex.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_COMPLEX_HPP
#define MW_COMPLEX_HPP

#include <Mw/Config.hpp>

#include <ostream>
#include <cmath>

#include <boost/operators.hpp>

MW_BEGIN_NAMESPACE(math)

/**
 * @brief Representation of a complex number.
 * @tparam T Scalar type.
 */
template<class T>
class Complex : boost::arithmetic<Complex<T> >,
                boost::equality_comparable<Complex<T> >
{
    /**
     * @brief Real part.
     */
    T _a;

    /**
     * @brief Imaginary part.
     */
    T _b;

public:

    // Constructors

    /**
     * @brief Default constructor.
     */
    Complex()
        : _a(static_cast<T>(0)), _b(static_cast<T>(0))
    {}

    /**
     * @brief Constructor.
     * @param a Real part.
     * @param b Imaginary part.
     */
    Complex(T a, T b)
        : _a(a), _b(b)
    {}

    /**
     * @brief Copy constructor.
     * @param cpx Complex number to copy.
     */
    template <typename U>
    Complex(const Complex<U> & cpx)
        : _a(cpx.getRealPart()), _b(cpx.getImaginaryPart())
    {}


    // Getters / Setters

    T getRealPart() const
    {
        return _a;
    }

    T getImaginaryPart() const
    {
        return _b;
    }

    T getRadialCoord() const
    {
        return std::sqrt(_a * _a + _b * _b);
    }

    T getAngularCoord() const
    {
        return std::atan2(_b, _a);
    }

    void set(T a, T b)
    {
        _a = a;
        _b = b;
    }

    void setRealPart(T a)
    {
        _a = a;
    }

    void setImaginaryPart(T b)
    {
        _b = b;
    }


    // Operators

    Complex & operator += (const Complex & cpx)
    {
        _a += cpx._a;
        _b += cpx._b;
        return *this;
    }

    Complex & operator -= (const Complex & cpx)
    {
        _a -= cpx._a;
        _b -= cpx._b;
        return *this;
    }

    Complex operator - () const
    {
        return Complex(- _a, - _b);
    }

    Complex & operator *= (const Complex & cpx)
    {
        T teta = getAngularCoord() + cpx.getAngularCoord();
        T r = getRadialCoord() * cpx.getRadialCoord();

        _a = r * std::cos(teta);
        _b = r * std::sin(teta);
        return *this;
    }

    Complex & operator /= (const Complex & cpx)
    {
        T teta = getAngularCoord() - cpx.getAngularCoord();
        T r = getRadialCoord() / cpx.getRadialCoord();

        _a = r * std::cos(teta);
        _b = r * std::sin(teta);
        return *this;
    }

    bool operator == (const Complex & cpx) const
    {
        return _a == cpx._a && _b == cpx._b;
    }

};
// class Complex

/**
 * @brief Stream insertion operator overload.
 * @param ostr Output stream.
 * @param vec Complex number to insert into the stream.
 * @return @c ostr Output stream.
 */
template <typename T>
std::ostream & operator << (std::ostream & ostr, const Complex<T> & cpx)
{
    ostr << "Complex[";
    if (cpx.getRealPart())
    {
        ostr << cpx.getRealPart();
        if (cpx.getImaginaryPart())
            ostr << " + " << cpx.getImaginaryPart() << " i";
    }
    else if (cpx.getImaginaryPart())
        ostr << cpx.getImaginaryPart() << " i";
    else
        ostr << cpx.getRealPart();

    return ostr << "]";
}

MW_END_NAMESPACE(math)

#endif // MW_COMPLEX_HPP
