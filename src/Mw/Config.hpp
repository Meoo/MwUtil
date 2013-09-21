/**
 * @file   Config.hpp
 * @author Bastien Brunnenstein
 */

#ifndef MW_CONFIG_HPP
#define MW_CONFIG_HPP

// Mw library version

/**
 * @def MW_MAJOR
 * Mw library major version number.
 */
/**
 * @def MW_MINOR
 * Mw library minor version number.
 */

#define MW_MAJOR 1
#define MW_MINOR 0


// Generic helper definitions for shared library support
//  See http://gcc.gnu.org/wiki/Visibility

/**
 * @def MW_API
 * Public visibility.
 */
/**
 * @def MW_LOCAL
 * Private visibility.
 */

#if defined _WIN32 || defined __CYGWIN__
#   define MW_HELPER_DLL_IMPORT __declspec(dllimport)
#   define MW_HELPER_DLL_EXPORT __declspec(dllexport)
#   define MW_HELPER_DLL_LOCAL
#else
#   if __GNUC__ >= 4
#       define MW_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#       define MW_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#       define MW_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#   else
#       define MW_HELPER_DLL_IMPORT
#       define MW_HELPER_DLL_EXPORT
#       define MW_HELPER_DLL_LOCAL
#   endif
#endif

#ifdef MW_DLL
#   ifdef MW_DLL_EXPORTS
#       define MW_API MW_HELPER_DLL_EXPORT
#   else
#       define MW_API MW_HELPER_DLL_IMPORT
#   endif
#   define MW_LOCAL MW_HELPER_DLL_LOCAL
#else
#   define MW_API
#   define MW_LOCAL
#endif

#undef MW_HELPER_DLL_IMPORT
#undef MW_HELPER_DLL_EXPORT
#undef MW_HELPER_DLL_LOCAL


// Namespaces utils

#define MW_BEGIN_NAMESPACE(ns) namespace mw { namespace ns {

#define MW_END_NAMESPACE(ns) } }

#define MW_FROM_NAMESPACE(ns, cl) mw::ns::cl


#endif // MW_CONFIG_HPP
