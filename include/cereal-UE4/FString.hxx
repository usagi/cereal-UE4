#pragma once
namespace cereal
{
  template < typename A >
  inline std::string save_minimal( A& a, const FString& in )
  {
    return std::string( TCHAR_TO_UTF8( *in ) );
  }
  
  template < typename A >
  inline void load_minimal( A& a, FString& out, const std::string& v )
  {
    out = FString( UTF8_TO_TCHAR( v.data() ) );
  }
}