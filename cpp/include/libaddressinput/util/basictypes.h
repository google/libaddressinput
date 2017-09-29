// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// The original source code is from:
// https://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/base/basictypes.h?r=621

#if I18N_ADDRESSINPUT_USE_BASICTYPES_OVERRIDE

// If building libaddressinput in an environment where there already is another
// implementation of the basictypes.h header file (like in Chromium), then pass
// the command line flag -DI18N_ADDRESSINPUT_USE_BASICTYPES_OVERRIDE=1 to the
// compiler and provide a file named basictypes_override.h, in a location where
// the compiler will look for it, which provides the desired implementation.

#include "basictypes_override.h"

#else

#ifndef I18N_ADDRESSINPUT_UTIL_BASICTYPES_H_
#define I18N_ADDRESSINPUT_UTIL_BASICTYPES_H_

#include <cstddef>         // For size_t

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#if !defined(DISALLOW_COPY_AND_ASSIGN)
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  TypeName& operator=(const TypeName&) = delete
#endif

// The arraysize(arr) macro returns the # of elements in an array arr.
// The expression is a compile-time constant, and therefore can be
// used in defining new arrays, for example.  If you use arraysize on
// a pointer by mistake, you will get a compile-time error.
//
// One caveat is that arraysize() doesn't accept any array of an
// anonymous type or a type defined inside a function.

// This template function declaration is used in defining arraysize.
// Note that the function doesn't need an implementation, as we only
// use its type.
template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];

// That gcc wants both of these prototypes seems mysterious. VC, for
// its part, can't decide which to use (another mystery). Matching of
// template overloads: the final frontier.
#ifndef _MSC_VER
template <typename T, size_t N>
char (&ArraySizeHelper(const T (&array)[N]))[N];
#endif

#if !defined(arraysize)
#define arraysize(array) (sizeof(ArraySizeHelper(array)))
#endif

#endif  // I18N_ADDRESSINPUT_UTIL_BASICTYPES_H_
#endif  // I18N_ADDRESSINPUT_USE_BASICTYPES_OVERRIDE
