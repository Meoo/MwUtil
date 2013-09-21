/**
 * @file   ComplexTest.cpp
 * @author Bastien Brunnenstein
 */

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <Mw/Math/Complex.hpp>

#include <cmath>

#define EPSILON std::numeric_limits<T>::epsilon() * 100

typedef boost::mpl::list<float, double> test_types;

BOOST_AUTO_TEST_SUITE(Math)
BOOST_AUTO_TEST_SUITE(Complex)

BOOST_AUTO_TEST_CASE_TEMPLATE(Constructor, T, test_types)
{
    using mw::math::Complex;

    Complex<T> c;
    BOOST_CHECK_EQUAL(c.getRealPart(), 0.0);
    BOOST_CHECK_EQUAL(c.getImaginaryPart(), 0.0);
    BOOST_CHECK_EQUAL(c.getRadialCoord(), 0.0);
    BOOST_CHECK_EQUAL(c.getAngularCoord(), 0.0);

    Complex<T> c2 (3.0, 4.0);
    BOOST_CHECK_EQUAL(c2.getRealPart(), 3.0);
    BOOST_CHECK_EQUAL(c2.getImaginaryPart(), 4.0);
    BOOST_CHECK_CLOSE(c2.getRadialCoord(), 5.0, EPSILON);
    //BOOST_CHECK_EQUAL(c2.getAngularCoord(), 0.0); // TODO Testing bad value

    Complex<float> copy(c);
    BOOST_CHECK_EQUAL(copy.getRealPart(), 0.0);
    BOOST_CHECK_EQUAL(copy.getImaginaryPart(), 0.0);

    Complex<double> copy2(c2);
    BOOST_CHECK_EQUAL(c2.getRealPart(), 3.0);
    BOOST_CHECK_EQUAL(c2.getImaginaryPart(), 4.0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Setters, T, test_types)
{
    using mw::math::Complex;

    Complex<T> c;

    c.setRealPart(2.0);
    BOOST_CHECK_EQUAL(c.getRealPart(), 2.0);

    c.setImaginaryPart(2.0);
    BOOST_CHECK_EQUAL(c.getImaginaryPart(), 2.0);

    c.set(3.0, 3.0);
    BOOST_CHECK_EQUAL(c.getRealPart(), 3.0);
    BOOST_CHECK_EQUAL(c.getImaginaryPart(), 3.0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Operations, T, test_types)
{
    using mw::math::Complex;

    Complex<T> c(1.0, 0.0);
    Complex<T> c2(0.0, 1.0);
    Complex<T> c3(0.0, 1.0);

    BOOST_CHECK_EQUAL(c, c);
    BOOST_CHECK_EQUAL(c2, c3);
    BOOST_CHECK_NE(c, c2);

    BOOST_CHECK_EQUAL(c + c2,   Complex<T>(1.0, 1.0));
    BOOST_CHECK_EQUAL(c - c2,   Complex<T>(1.0, -1.0));
    //BOOST_CHECK_EQUAL(c2 * c,  Complex<T>(2.0, 0.0)); // TODO Testing bad values
    //BOOST_CHECK_EQUAL(c / c2,  Complex<T>(0.5, 0.0)); // TODO Testing bad values
    BOOST_CHECK_EQUAL( - c ,    Complex<T>(-1.0, 0.0));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
