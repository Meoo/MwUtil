/**
 * @file   Bounds2Test.cpp
 * @author Bastien Brunnenstein
 */

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <Mw/Math/Bounds2.hpp>

#include <cmath>

#define EPSILON std::numeric_limits<T>::epsilon() * 100

typedef boost::mpl::list<float, double> test_types;

BOOST_AUTO_TEST_SUITE(Math)
BOOST_AUTO_TEST_SUITE(Bounds2)

BOOST_AUTO_TEST_CASE_TEMPLATE(Constructor, T, test_types)
{
    using mw::math::Bounds2;
    using mw::math::Vector2;

    Bounds2<T> b;
    BOOST_CHECK(b.isEmpty());
    BOOST_CHECK_EQUAL(b.getUpperLimit(), Vector2<T>(0, 0));
    BOOST_CHECK_EQUAL(b.getLowerLimit(), Vector2<T>(0, 0));

    Bounds2<T> copy(b);
    BOOST_CHECK(copy.isEmpty());
    BOOST_CHECK_EQUAL(copy.getUpperLimit(), Vector2<T>(0, 0));
    BOOST_CHECK_EQUAL(copy.getLowerLimit(), Vector2<T>(0, 0));

    Bounds2<T> b2(Vector2<T>(-1.0, -1.0), Vector2<T>(1.0, 1.0));
    BOOST_CHECK(!b2.isEmpty());
    BOOST_CHECK_EQUAL(b2.getUpperLimit(), Vector2<T>(1.0, 1.0));
    BOOST_CHECK_EQUAL(b2.getLowerLimit(), Vector2<T>(-1.0, -1.0));

    Bounds2<T> copy2(b2);
    BOOST_CHECK(!copy2.isEmpty());
    BOOST_CHECK_EQUAL(copy2.getUpperLimit(), Vector2<T>(1.0, 1.0));
    BOOST_CHECK_EQUAL(copy2.getLowerLimit(), Vector2<T>(-1.0, -1.0));

    Bounds2<T> b3(Vector2<T>(2.0, 2.0), Vector2<T>(-2.0, -2.0));
    BOOST_CHECK(!b3.isEmpty());
    BOOST_CHECK_EQUAL(b3.getUpperLimit(), Vector2<T>(2.0, 2.0));
    BOOST_CHECK_EQUAL(b3.getLowerLimit(), Vector2<T>(-2.0, -2.0));

    Bounds2<T> copy3(b3);
    BOOST_CHECK(!copy3.isEmpty());
    BOOST_CHECK_EQUAL(copy3.getUpperLimit(), Vector2<T>(2.0, 2.0));
    BOOST_CHECK_EQUAL(copy3.getLowerLimit(), Vector2<T>(-2.0, -2.0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Setters, T, test_types)
{
    using mw::math::Bounds2;
    using mw::math::Vector2;

    Bounds2<T> b;

    b.setUpperLimit(Vector2<T>(1.0, 1.0));
    BOOST_CHECK(!b.isEmpty());
    BOOST_CHECK_EQUAL(b.getUpperLimit(), Vector2<T>(1.0, 1.0));
    BOOST_CHECK_EQUAL(b.getLowerLimit(), Vector2<T>(0, 0));

    b.setUpperLimit(Vector2<T>(-1.0, -1.0));
    BOOST_CHECK(b.isEmpty());
    BOOST_CHECK_EQUAL(b.getUpperLimit(), Vector2<T>(-1.0, -1.0));
    BOOST_CHECK_EQUAL(b.getLowerLimit(), Vector2<T>(0, 0));

    b.setLowerLimit(Vector2<T>(-2, -2));
    BOOST_CHECK(!b.isEmpty());
    BOOST_CHECK_EQUAL(b.getUpperLimit(), Vector2<T>(-1.0, -1.0));
    BOOST_CHECK_EQUAL(b.getLowerLimit(), Vector2<T>(-2.0, -2.0));

    b.set(Vector2<T>(1.0, -2.0), Vector2<T>(3.0, -4.0));
    BOOST_CHECK(!b.isEmpty());
    BOOST_CHECK_EQUAL(b.getUpperLimit(), Vector2<T>(3.0, -2.0));
    BOOST_CHECK_EQUAL(b.getLowerLimit(), Vector2<T>(1.0, -4.0));

    b.set(Vector2<T>(-1.0, 2.0), Vector2<T>(-3.0, 4.0));
    BOOST_CHECK(!b.isEmpty());
    BOOST_CHECK_EQUAL(b.getUpperLimit(), Vector2<T>(-1.0, 4.0));
    BOOST_CHECK_EQUAL(b.getLowerLimit(), Vector2<T>(-3.0, 2.0));

    b.set(Vector2<T>(5.0, -2.0), Vector2<T>(5.0, -2.0));
    BOOST_CHECK(b.isEmpty());
    BOOST_CHECK_EQUAL(b.getUpperLimit(), Vector2<T>(5.0, -2.0));
    BOOST_CHECK_EQUAL(b.getLowerLimit(), Vector2<T>(5.0, -2.0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Unions, T, test_types)
{
    using mw::math::Bounds2;

    // TODO Bounds2Test Unions stub
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Intersections, T, test_types)
{
    using mw::math::Bounds2;

    // TODO Bounds2Test Intersections stub
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
