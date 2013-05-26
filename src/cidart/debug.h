// Copyright (c) 2013, Richard Eakin and the Dart project authors.
// Use of this source code (and the Dart itself) is governed by a
// BSD-style license that can be found in the LICENSE.txt file.

#pragma once

#include "cinder/app/App.h"

#define LOG_V ci::app::console() << __func__ << " | "
#define LOG_E LOG_V << __LINE__ << " | " << " *** ERROR *** : "


#include <boost/assert.hpp>

#define CI_ASSERT(expr) BOOST_ASSERT(expr)

#include "dart_api.h"

// FIXME: this macro is not safe - syntax errors in the script will bring it down
#define CHECK_DART(result)							\
if (Dart_IsError(result)) {							\
	LOG_E << Dart_GetError(result) << std::endl;	\
	CI_ASSERT( 0 );									\
}

#define CHECK_DART_RETURN(result)					\
if (Dart_IsError(result)) {							\
	LOG_E << Dart_GetError(result) << std::endl;	\
	return;											\
}