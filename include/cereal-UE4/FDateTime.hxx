#pragma once
namespace cereal
{
  template < typename A >
  inline std::string save_minimal( A& a, const FDateTime& in )
  {
    return std::string( TCHAR_TO_UTF8( *in.ToIso8601() ) );
  }
  
  template < typename A >
  inline void load_minimal( A& a, FDateTime& out, const std::string& v )
  {
    FDateTime::ParseIso8601( UTF8_TO_TCHAR( v.data() ), out );
  }
}