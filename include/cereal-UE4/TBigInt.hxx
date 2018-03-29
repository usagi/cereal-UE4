#pragma once
#include "Runtime/Core/Public/Math/BigInt.h"
namespace cereal
{
  template < typename A, int32 B, bool S >
  inline void save( A& a, const TBigInt< B, S >& in )
  {
    a( make_nvp( "hex", std::string( TCHAR_TO_UTF8( *in.ToString() ) ) ) );
  }
  
  template < typename A, int32 B, bool S >
  inline void load( A& a, TBigInt< B, S >& out )
  {
    std::string buffer;
    a( make_nvp( "hex", buffer ) );
    out.Parse( FString( UTF8_TO_TCHAR( buffer.data() ) ) );
  }
}