// Copyright (c) 2013, Richard Eakin and the Dart project authors.
// Use of this source code (and the Dart itself) is governed by a
// BSD-style license that can be found in the LICENSE.txt file.

#pragma once

#include "dart_api.h"

#include "cinder/Color.h"

namespace cidart {

struct DartScope {
	DartScope() { Dart_EnterScope(); }
	~DartScope() { Dart_ExitScope(); }
};

// TODO: move
void console( Dart_NativeArguments arguments );

Dart_Handle newString( const char* str );

Dart_Handle newInt( int i );

std::string getString( Dart_Handle handle );

bool isMap( Dart_Handle handle );
bool isColor( Dart_Handle handle );

int			getInt( Dart_Handle handle );
float		getFloat( Dart_Handle handle );
ci::ColorA	getColor( Dart_Handle handle );

void getValue( Dart_Handle handle, int *value );
void getValue( Dart_Handle handle, size_t *value );
void getValue( Dart_Handle handle, float *value );
void getValue( Dart_Handle handle, ci::ColorA *value );

bool hasFunction( Dart_Handle handle, const std::string &name );
Dart_Handle callFunction( Dart_Handle target, const std::string &name, int numArgs = 0, Dart_Handle *args = nullptr );
Dart_Handle getField( Dart_Handle container, const std::string &name );
std::string getTypeName( Dart_Handle handle );

} // namespace cidart