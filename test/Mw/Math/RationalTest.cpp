/**
 * @file   RationalTest.cpp
 * @author Bastien Brunnenstein
 */

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <Mw/Math/Rational.hpp>

typedef boost::mpl::list<int> test_types;

BOOST_AUTO_TEST_SUITE(Math)
BOOST_AUTO_TEST_SUITE(Rational)

BOOST_AUTO_TEST_CASE_TEMPLATE(Constructor, T, test_types)
{
    using mw::math::Rational;

    Rational<T> a;
    BOOST_CHECK_EQUAL(a.getNumerator(), 0);
    BOOST_CHECK_EQUAL(a.getDenominator(), 1);
    BOOST_CHECK_EQUAL((float) a, 0.0f);

    Rational<T> b(4, -3);
    BOOST_CHECK_EQUAL(b.getNumerator(), -4);
    BOOST_CHECK_EQUAL(b.getDenominator(), 3);
    BOOST_CHECK_EQUAL((float) b, - 4.0f / 3.0f);

    Rational<T> c(-8, -2);
    BOOST_CHECK_EQUAL(c.getNumerator(), 4);
    BOOST_CHECK_EQUAL(c.getDenominator(), 1);
    BOOST_CHECK_EQUAL((float) c, 4.0f);

    Rational<T> d(5);
    BOOST_CHECK_EQUAL(d.getNumerator(), 5);
    BOOST_CHECK_EQUAL(d.getDenominator(), 1);
    BOOST_CHECK_EQUAL((float) d, 5.0f);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Setters, T, test_types)
{
    using mw::math::Rational;

    Rational<T> a;
    BOOST_CHECK_EQUAL(a.getNumerator(), 0);
    BOOST_CHECK_EQUAL(a.getDenominator(), 1);
    BOOST_CHECK_EQUAL((float) a, 0.0f);

    a.set(4, 8);
    BOOST_CHECK_EQUAL(a.getNumerator(), 1);
    BOOST_CHECK_EQUAL(a.getDenominator(), 2);
    BOOST_CHECK_EQUAL((float) a, 0.5f);

    a.setNumerator(4);
    BOOST_CHECK_EQUAL(a.getNumerator(), 2);
    BOOST_CHECK_EQUAL(a.getDenominator(), 1);
    BOOST_CHECK_EQUAL((float) a, 2.0f);

    a.setDenominator(2);
    BOOST_CHECK_EQUAL(a.getNumerator(), 1);
    BOOST_CHECK_EQUAL(a.getDenominator(), 1);
    BOOST_CHECK_EQUAL((float) a, 1.0f);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Operations, T, test_types)
{
    using mw::math::Rational;

    Rational<T> a(4, 3);
    Rational<T> b(3, 4);

    BOOST_CHECK_NE(a, b);
    BOOST_CHECK_EQUAL(a, Rational<T>(4, 3));
    BOOST_CHECK_EQUAL(b, Rational<T>(3, 4));

    BOOST_CHECK(b < a);
    BOOST_CHECK(b <= a);
    BOOST_CHECK(! (a < b));

    BOOST_CHECK(a <= a);
    BOOST_CHECK(b >= b);

    BOOST_CHECK_EQUAL(a + b, Rational<T>(25, 12));
    BOOST_CHECK_EQUAL(a - b, Rational<T>(7, 12));
    BOOST_CHECK_EQUAL(a * b, Rational<T>(1));
    BOOST_CHECK_EQUAL(a / b, Rational<T>(16, 9));

    BOOST_CHECK_EQUAL(a * Rational<T>(1, 2), Rational<T>(2, 3));

    BOOST_CHECK_EQUAL(a - a, Rational<T>());
    BOOST_CHECK_EQUAL(a * Rational<T>(), Rational<T>());
    BOOST_CHECK_EQUAL(a * Rational<T>(1), a);

    BOOST_CHECK_THROW(a / Rational<T>(0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
