/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#ifndef _FC_COMMON_H_
#define _FC_COMMON_H_

#include <functional>
#include <type_traits>

#if !defined(FC_OPERATORS)
#define FC_OPERATORS 1
#endif

#if FC_OPERATORS

#if !defined(FC_PLUS_OPERATOR)
#define FC_PLUS_OPERATOR 1
#endif

#if !defined(FC_DOT_OPERATOR)
#define FC_DOT_OPERATOR 1
#endif

#if !defined(FC_AND_OPERATOR)
#define FC_AND_OPERATOR 0
#endif

#else

#if !defined(FC_PLUS_OPERATOR)
#define FC_PLUS_OPERATOR 0
#endif

#if !defined(FC_DOT_OPERATOR)
#define FC_DOT_OPERATOR 0
#endif

#if !defined(FC_DOT_OPERATOR)
#define FC_AND_OPERATOR 0
#endif

#endif

#endif /* _FC_COMMON_H_ */
