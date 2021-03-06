#pragma once

// tests for relevant C++11 features
//
// Qt 5 provides all of the compiler feature detection we need
// in qcompilerdetection.h via Q_COMPILER_XXX macros.
// 
// Qt 4 is missing defines for
// certain compilers (eg. new versions of Clang and VC++) and
// features.

// Visual C++
// See http://blogs.msdn.com/b/vcblog/archive/2011/09/12/10209291.aspx
#if (_MSC_VER >= 1600)
#define QST_COMPILER_SUPPORTS_LAMBDAS
#define QST_COMPILER_SUPPORTS_DECLTYPE
#endif

// GCC
// See http://gcc.gnu.org/projects/cxx0x.html
#if (__GNUC__ >= 4) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#if (__GNUC_MINOR__ >= 3)
#define QST_COMPILER_SUPPORTS_DECLTYPE
#define QST_COMPILER_SUPPORTS_VARIADIC_TEMPLATES
#endif
#if (__GNUC_MINOR__ >= 5)
#define QST_COMPILER_SUPPORTS_LAMBDAS
#endif
#endif

// Clang
// See http://clang.llvm.org/docs/LanguageExtensions.html
#if __clang__
#if __has_feature(cxx_lambdas)
#define QST_COMPILER_SUPPORTS_LAMBDAS
#define QST_COMPILER_SUPPORTS_DECLTYPE
#endif
#if __has_feature(cxx_variadic_templates)
#define QST_COMPILER_SUPPORTS_VARIADIC_TEMPLATES
#endif
#endif

#ifdef QST_COMPILER_SUPPORTS_LAMBDAS
// sets whether the C++11 standard libraries should
// be used.  If not, we fall back to the TR1 versions.
// A similar define could also be used to use Boost instead.
#define QST_USE_CPP11_LIBS
#endif

// include headers that provide function<> and bind()
#if defined(_MSC_VER) || defined(QST_USE_CPP11_LIBS)
#include <functional>
#include <memory>
#include <type_traits>

#ifndef _MSC_VER
// even under C++11, we are still using the TR1 version
// of result_of<>
#include <tr1/functional>
#endif

#else
#include <tr1/functional>
#include <tr1/memory>
#include <tr1/type_traits>
#endif

#define QST_COMMA ,

namespace QtSignalTools
{

// enable_if is actually provided by all
// supported compilers, but is under an extension
// namespace under GCC
template <bool, class T>
struct enable_if;

template <class T>
struct enable_if<true,T>
{
	typedef T type;
};

#if defined(QST_USE_CPP11_LIBS)
namespace qst_functional = std;
#else
namespace qst_functional = std::tr1;
#endif

using qst_functional::is_base_of;
using qst_functional::mem_fn;
using qst_functional::shared_ptr;

}

