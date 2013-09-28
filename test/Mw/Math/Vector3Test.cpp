/**
 * @file   Vector3Test.cpp
 * @author Bastien Brunnenstein
 */

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <Mw/Math/Vector3.hpp>

#include <cmath>

#define EPSILON std::numeric_limits<T>::epsilon() * 100

typedef boost::mpl::list<float, double> test_types;
/* TODO Vector3 unit test
BOOST_AUTO_TEST_SUITE(Math)
BOOST_AUTO_TEST_SUITE(Vector3)

BOOST_AUTO_TEST_CASE_TEMPLATE(Constructor, T, test_types)
{
    using mw::math::Vector3;

}

BOOST_AUTO_TEST_CASE_TEMPLATE(Setters, T, test_types)
{
    using mw::math::Vector3;

}

BOOST_AUTO_TEST_CASE_TEMPLATE(Operations, T, test_types)
{
    using mw::math::Vector3;

}

BOOST_AUTO_TEST_CASE_TEMPLATE(Projections, T, test_types)
{
    using mw::math::Vector3;

}

BOOST_AUTO_TEST_CASE_TEMPLATE(Normals, T, test_types)
{
    using mw::math::Vector3;

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
*/
