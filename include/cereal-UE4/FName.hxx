#pragma once
namespace cereal
{
  template < typename A >
  inline std::string save_minimal( A& a, const FName& in )
  {
    return std::string( TCHAR_TO_UTF8( *in.ToString() ) );
  }
  
  template < typename A >
  inline void load_minimal( A& a, FName& out, const std::string& v )
  {
    out = FName( UTF8_TO_TCHAR( v.data() ) );
  }
}