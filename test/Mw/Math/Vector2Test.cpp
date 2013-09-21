/**
 * @file   Vector2Test.cpp
 * @author Bastien Brunnenstein
 */

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <Mw/Math/Vector2.hpp>

#include <cmath>

#define EPSILON std::numeric_limits<T>::epsilon() * 100

typedef boost::mpl::list<float, double> test_types;

BOOST_AUTO_TEST_SUITE(Math)
BOOST_AUTO_TEST_SUITE(Vector2)

BOOST_AUTO_TEST_CASE_TEMPLATE(Constructor, T, test_types)
{
    using mw::math::Vector2;

    Vector2<T> v;
    BOOST_CHECK_EQUAL(v.getX(), 0.0);
    BOOST_CHECK_EQUAL(v.getY(), 0.0);
    BOOST_CHECK_EQUAL(v.getLength(), 0.0);
    BOOST_CHECK(v.isNull());

    Vector2<T> v2 (3.0, 4.0);
    BOOST_CHECK_EQUAL(v2.getX(), 3.0);
    BOOST_CHECK_EQUAL(v2.getY(), 4.0);
    BOOST_CHECK_CLOSE(v2.getLength(), 5.0, EPSILON);
    BOOST_CHECK(!v2.isNull());

    Vector2<float> copy(v);
    BOOST_CHECK_EQUAL(copy.getX(), 0.0);
    BOOST_CHECK_EQUAL(copy.getY(), 0.0);

    Vector2<double> copy2(v2);
    BOOST_CHECK_EQUAL(copy2.getX(), 3.0);
    BOOST_CHECK_EQUAL(copy2.getY(), 4.0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Setters, T, test_types)
{
    using mw::math::Vector2;

    Vector2<T> v;

    v.setX(2.0);
    BOOST_CHECK_EQUAL(v.getX(), 2.0);

    v.setY(2.0);
    BOOST_CHECK_EQUAL(v.getY(), 2.0);

    v.set(3.0, 3.0);
    BOOST_CHECK_EQUAL(v.getX(), 3.0);
    BOOST_CHECK_EQUAL(v.getY(), 3.0);

    v.normalize();
    BOOST_CHECK_CLOSE(v.getX(), std::sqrt(2.0) / 2.0, EPSILON);
    BOOST_CHECK_CLOSE(v.getY(), std::sqrt(2.0) / 2.0, EPSILON);
    BOOST_CHECK_CLOSE(v.getLength(), 1.0, EPSILON);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Operations, T, test_types)
{
    using mw::math::Vector2;

    Vector2<T> v(1.0, 0.0);
    Vector2<T> v2(0.0, 1.0);
    Vector2<T> v3(0.0, 1.0);

    BOOST_CHECK_EQUAL(v, v);
    BOOST_CHECK_EQUAL(v2, v3);
    BOOST_CHECK_NE(v, v2);

    BOOST_CHECK_EQUAL(v + v2,   Vector2<T>(1.0, 1.0));
    BOOST_CHECK_EQUAL(v - v2,   Vector2<T>(1.0, -1.0));
    BOOST_CHECK_EQUAL(2.0 * v,  Vector2<T>(2.0, 0.0));
    BOOST_CHECK_EQUAL(v / 2.0,  Vector2<T>(0.5, 0.0));
    BOOST_CHECK_EQUAL( - v ,    Vector2<T>(-1.0, 0.0));

    BOOST_CHECK((v - v).isNull());

    BOOST_CHECK_EQUAL(v.dot(v2), 0.0);
    BOOST_CHECK_EQUAL(v.dot(v), 1.0);
    BOOST_CHECK_EQUAL(v2.dot(v3), 1.0);

    BOOST_CHECK_EQUAL(Vector2<T>(2.0, 0.5).dot(Vector2<T>(0.5, 2.0)), 2.0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Projections, T, test_types)
{
    using mw::math::Vector2;

    Vector2<T> v(1.0, 1.0);
    Vector2<T> v2(2.0, 0.0);
    Vector2<T> v3(0.0, -1.0);

    BOOST_CHECK_EQUAL(v.getProjection(v2), Vector2<T>(1.0, 0.0));
    BOOST_CHECK_EQUAL(v2.getProjection(v), Vector2<T>(1.0, 1.0));
    BOOST_CHECK_EQUAL(v.getProjection(v3), Vector2<T>(0.0, 1.0));
    BOOST_CHECK_EQUAL(v3.getProjection(v), Vector2<T>(-0.5, -0.5));
    BOOST_CHECK_EQUAL(v2.getProjection(v3), Vector2<T>(0.0, 0.0));

    BOOST_CHECK_EQUAL(v.getScalarProjection(v2), 1.0);
    BOOST_CHECK_CLOSE(v2.getScalarProjection(v), std::sqrt(2.0), EPSILON);
    BOOST_CHECK_EQUAL(v.getScalarProjection(v3), -1.0);
    BOOST_CHECK_CLOSE(v3.getScalarProjection(v),
                      - std::sqrt(2.0) / 2.0, EPSILON);
    BOOST_CHECK_EQUAL(v2.getScalarProjection(v3), 0.0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Normals, T, test_types)
{
    using mw::math::Vector2;

    Vector2<T> v(1.0, 2.0);
    BOOST_CHECK_EQUAL(v.getRightHandNormal(), Vector2<T>(-2.0, 1.0));
    BOOST_CHECK_EQUAL(v.getLeftHandNormal(), Vector2<T>(2.0, -1.0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rotations, T, test_types)
{
    using mw::math::Vector2;

    Vector2<T> v(1.0, 0.0);
    T PI = std::acos(-1.0);

    BOOST_CHECK_EQUAL(v.getRotation(PI), Vector2<T>(-1.0, 0.0));
    BOOST_CHECK_EQUAL(v.getRotation(PI / 2.0), Vector2<T>(0.0, 1.0));
    BOOST_CHECK_EQUAL(v.getRotation(PI / 4.0),
                      Vector2<T>(std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
