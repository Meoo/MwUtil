/**
 * @file   Interpolation.hpp
 * @author Bastien Brunnenstein
 *
 * @details See http://paulbourke.net/miscellaneous/interpolation/
 */

#ifndef MW_INTERPOLATION_HPP
#define MW_INTERPOLATION_HPP

#include <Mw/Config.hpp>

#include <cmath>

MW_BEGIN_NAMESPACE(math)

// TODO Comments sucks

/**
 * Compute a value between @a p1 and @a p2 using linear interpolation.
 *
 * @param p1 First sample.
 * @param p2 Second sample.
 * @param mu Position of the value in range. Value between 0 and 1.
 * @tparam T Value's type. Must be multipliable by @a U.
 * @tparam U Scalar type.
 */
template<class T, typename U>
T linearInterpolate(T p1, T p2, U mu)
{
    return (p1 * (static_cast<U>(1) - mu) + p2 * mu);
}

/**
 * Compute a value between @a p1 and @a p2 using cosine interpolation.
 *
 * @param p1 First sample.
 * @param p2 Second sample.
 * @param mu Position of the value in range. Value between 0 and 1.
 * @tparam T Value's type. Must be multipliable by @a U.
 * @tparam U Scalar type.
 */
template<class T, typename U>
T cosineInterpolate(T p1, T p2, U mu)
{
    U mu2;

    mu2 = (static_cast<U>(1) - std::cos(mu * M_PI)) / 2;
    return (p1 * (static_cast<U>(1) - mu2) + p2 * mu2);
}

/**
 * Compute a value between @a p1 and @a p2 using cubic interpolation.
 *
 * @param p0 Point before first sample.
 * @param p1 First sample.
 * @param p2 Second sample.
 * @param p3 Point after second sample.
 * @param mu Position of the value in range. Value between 0 and 1.
 * @tparam T Value's type. Must be multipliable by @a U.
 * @tparam U Scalar type.
 */
template<class T, typename U>
T cubicInterpolate(T p0, T p1, T p2, T p3, U mu)
{
    double a0, a1, a2, a3, mu2;

    mu2 = mu * mu;
    a0 = p3 - p2 - p0 + p1;
    a1 = p0 - p1 - a0;
    a2 = p2 - p0;
    a3 = p1;

    return (a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3);
}

/**
 * Compute a value between @a p1 and @a p2 using catmull-rom interpolation.
 *
 * @param p0 Point before first sample.
 * @param p1 First sample.
 * @param p2 Second sample.
 * @param p3 Point after second sample.
 * @param mu Position of the value in range. Value between 0 and 1.
 * @tparam T Value's type. Must be multipliable by @a U.
 * @tparam U Scalar type.
 */
template<class T, typename U>
T catmullRomInterpolate(T p0, T p1, T p2, T p3, U mu)
{
    T a0, a1, a2, a3;
    U mu2;

    mu2 = mu * mu;
    a0 = static_cast<U>(-0.5) * p0 + static_cast<U>(1.5) * p1
            + static_cast<U>(-1.5) * p2 + static_cast<U>(0.5) * p3;
    a1 = p0 + static_cast<U>(-2.5) * p1 + static_cast<U>(2) * p2
            + static_cast<U>(-0.5) * p3;
    a2 = static_cast<U>(-0.5) * p0 + static_cast<U>(0.5) * p2;
    a3 = p1;

    return (a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3);
}

MW_END_NAMESPACE(math)

#endif // MW_INTERPOLATION_HPP
