// Special functions -*- C++ -*-

// Copyright (C) 2006-2007
// Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
// USA.
//
// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

/** @file tr1/beta_function.tcc
 *  This is an internal header file, included by other library headers.
 *  You should not attempt to use it directly.
 */

//
// ISO C++ 14882 TR1: 5.2  Special functions
//

// Written by Edward Smith-Rowland based on:
//   (1) Handbook of Mathematical Functions,
//       ed. Milton Abramowitz and Irene A. Stegun,
//       Dover Publications,
//       Section 6, pp. 253-266
//   (2) The Gnu Scientific Library, http://www.gnu.org/software/gsl
//   (3) Numerical Recipes in C, by W. H. Press, S. A. Teukolsky,
//       W. T. Vetterling, B. P. Flannery, Cambridge University Press (1992),
//       2nd ed, pp. 213-216
//   (4) Gamma, Exploring Euler's Constant, Julian Havil,
//       Princeton, 2003.

#ifndef _GLIBCXX_TR1_BETA_FUNCTION_TCC
#define _GLIBCXX_TR1_BETA_FUNCTION_TCC 1

namespace std
{
namespace tr1
{

  // [5.2] Special functions

  /**
   * @ingroup tr1_math_spec_func
   * @{
   */

  //
  // Implementation-space details.
  //
  namespace __detail
  {

    /**
     *   @brief  Return the beta function: \f$B(x,y)\f$.
     * 
     *   The beta function is defined by
     *   @f[
     *     B(x,y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}
     *   @f]
     *
     *   @param __x The first argument of the beta function.
     *   @param __y The second argument of the beta function.
     *   @return  The beta function.
     */
    template<typename _Tp>
    _Tp
    __beta_gamma(_Tp __x, _Tp __y)
    {

      _Tp __bet;
#if _GLIBCXX_USE_C99_MATH_TR1
      if (__x > __y)
        {
          __bet = std::tr1::tgamma(__x)
                / std::tr1::tgamma(__x + __y);
          __bet *= std::tr1::tgamma(__y);
        }
      else
        {
          __bet = std::tr1::tgamma(__y)
                / std::tr1::tgamma(__x + __y);
          __bet *= std::tr1::tgamma(__x);
        }
#else
      if (__x > __y)
        {
          __bet = __gamma(__x) / __gamma(__x + __y);
          __bet *= __gamma(__y);
        }
      else
        {
          __bet = __gamma(__y) / __gamma(__x + __y);
          __bet *= __gamma(__x);
        }
#endif

      return __bet;
    }

    /**
     *   @brief  Return the beta function \f$B(x,y)\f$ using
     *           the log gamma functions.
     * 
     *   The beta function is defined by
     *   @f[
     *     B(x,y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}
     *   @f]
     *
     *   @param __x The first argument of the beta function.
     *   @param __y The second argument of the beta function.
     *   @return  The beta function.
     */
    template<typename _Tp>
    _Tp
    __beta_lgamma(_Tp __x, _Tp __y)
    {
#if _GLIBCXX_USE_C99_MATH_TR1
      _Tp __bet = std::tr1::lgamma(__x)
                + std::tr1::lgamma(__y)
                - std::tr1::lgamma(__x + __y);
#else
      _Tp __bet = __log_gamma(__x)
                + __log_gamma(__y)
                - __log_gamma(__x + __y);
#endif
      __bet = std::exp(__bet);
      return __bet;
    }


    /**
     *   @brief  Return the beta function \f$B(x,y)\f$ using
     *           the product form.
     * 
     *   The beta function is defined by
     *   @f[
     *     B(x,y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}
     *   @f]
     *
     *   @param __x The first argument of the beta function.
     *   @param __y The second argument of the beta function.
     *   @return  The beta function.
     */
    template<typename _Tp>
    _Tp
    __beta_product(_Tp __x, _Tp __y)
    {

      _Tp __bet = (__x + __y) / (__x * __y);

      unsigned int __max_iter = 1000000;
      for (unsigned int __k = 1; __k < __max_iter; ++__k)
        {
          _Tp __term = (_Tp(1) + (__x + __y) / __k)
                     / ((_Tp(1) + __x / __k) * (_Tp(1) + __y / __k));
          __bet *= __term;
        }

      return __bet;
    }


    /**
     *   @brief  Return the beta function \f$ B(x,y) \f$.
     * 
     *   The beta function is defined by
     *   @f[
     *     B(x,y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}
     *   @f]
     *
     *   @param __x The first argument of the beta function.
     *   @param __y The second argument of the beta function.
     *   @return  The beta function.
     */
    template<typename _Tp>
    inline _Tp
    __beta(_Tp __x, _Tp __y)
    {
      if (__isnan(__x) || __isnan(__y))
        return std::numeric_limits<_Tp>::quiet_NaN();
      else
        return __beta_lgamma(__x, __y);
    }

  } // namespace std::tr1::__detail

  /* @} */ // group tr1_math_spec_func

}
}

#endif // __GLIBCXX_TR1_BETA_FUNCTION_TCC
